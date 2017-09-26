'''
 ******************************************************************************
 * MIT License
 * 
 * PROJECT SPRINGBOARD
 * -------------------
 * Copyright (c) 2017 <craig.sacco@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************
'''

import struct


class MessageHandler:

    MSG_TYPE_GET_PROPERTY_REQUEST = 0
    MSG_TYPE_GET_PROPERTY_RESPONSE = 1
    MSG_TYPE_SET_PROPERTY_REQUEST = 2
    MSG_TYPE_SET_PROPERTY_RESPONSE = 3

    def __init__(self, client):
        self.__client = client
        self.__seqno = 1

    def __get_next_seqno(self):
        seqno = self.__seqno
        self.__seqno = 1 if self.__seqno == 255 else self.__seqno + 1
        return seqno

    def __send_message(self, payload):
        msg = struct.pack("<BBB", 0xfd, 0x02, len(payload) + 1)
        msg += payload
        msg += struct.pack("<BB", 0x03, 0xfc)
        checksum = 0
        for x in msg:
            checksum ^= ord(x)
        msg += struct.pack("<B", checksum)
        self.__client.write(msg)

    def __get_message(self):
        msg = self.__client.read(3)
        msg += self.__client.read((ord(msg[2]) - 1) + 3)
        sof, length = struct.unpack("<HB", msg[0:3])
        data = msg[3:(3 + length) - 1]
        eof, checksum = struct.unpack("<HB", msg[(3 + length) - 1:])
        expected = 0
        for x in msg[:-1]:
            expected ^= ord(x)
        if checksum != expected:
            raise Exception("checksum mismatch: {0} != {1}".format(checksum, expected))
        return data

    def __get_property_raw(self, resource_id, property_id):
        seqno = self.__get_next_seqno()
        msg = struct.pack("<BBHH", seqno, MessageHandler.MSG_TYPE_GET_PROPERTY_REQUEST, resource_id, property_id)
        self.__send_message(msg)
        rsp_data = self.__get_message()
        rsp__seqno, rsp_type, rsp_resource_id, rsp_property_id, rsp_resultcode = struct.unpack("<BBHHI", rsp_data[0:10])
        if rsp_type != MessageHandler.MSG_TYPE_GET_PROPERTY_RESPONSE:
            raise Exception("unexpected type: {0} != {1}".format(MessageHandler.MSG_TYPE_GET_PROPERTY_RESPONSE,
                                                                 rsp_type))
        if seqno != rsp__seqno:
            raise Exception("unexpected seqno: {0} != {1}".format(seqno, rsp__seqno))
        if resource_id != rsp_resource_id:
            raise Exception("unexpected resid: {0} != {1}".format(resource_id, rsp_resource_id))
        if property_id != rsp_property_id:
            raise Exception("unexpected propid: {0} != {1}".format(property_id, rsp_property_id))
        if rsp_resultcode != 0:
            raise Exception("get property request returned result code 0x{0:08x}".format(rsp_resultcode))
        return rsp_data[10:]

    def __set_property_raw(self, resource_id, property_id, data):
        seqno = self.__get_next_seqno()
        msg = struct.pack("<BBHH", seqno, MessageHandler.MSG_TYPE_SET_PROPERTY_REQUEST, resource_id, property_id) + \
              data
        self.__send_message(msg)
        rsp_data = self.__get_message()
        rsp__seqno, rsp_type, rsp_resource_id, rsp_property_id, rsp_resultcode = struct.unpack("<BBHHI", rsp_data)
        if rsp_type != MessageHandler.MSG_TYPE_SET_PROPERTY_RESPONSE:
            raise Exception("unexpected type: {0} != {1}".format(MessageHandler.MSG_TYPE_SET_PROPERTY_RESPONSE,
                                                                 rsp_type))
        if seqno != rsp__seqno:
            raise Exception("unexpected seqno: {0} != {1}".format(seqno, rsp__seqno))
        if resource_id != rsp_resource_id:
            raise Exception("unexpected resid: {0} != {1}".format(resource_id, rsp_resource_id))
        if property_id != rsp_property_id:
            raise Exception("unexpected propid: {0} != {1}".format(property_id, rsp_property_id))
        if rsp_resultcode != 0:
            raise Exception("set property request returned result code 0x{0:08x}".format(rsp_resultcode))

    def get_property_bool(self, resource_id, property_id):
        return struct.unpack("<B", self.__get_property_raw(resource_id, property_id))[0] != 0

    def get_property_uint8(self, resource_id, property_id):
        return struct.unpack("<B", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_uint16(self, resource_id, property_id):
        return struct.unpack("<H", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_uint32(self, resource_id, property_id):
        return struct.unpack("<I", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_uint64(self, resource_id, property_id):
        return struct.unpack("<Q", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_int8(self, resource_id, property_id):
        return struct.unpack("<b", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_int16(self, resource_id, property_id):
        return struct.unpack("<h", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_int32(self, resource_id, property_id):
        return struct.unpack("<i", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_int64(self, resource_id, property_id):
        return struct.unpack("<q", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_float(self, resource_id, property_id):
        return struct.unpack("<f", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_double(self, resource_id, property_id):
        return struct.unpack("<d", self.__get_property_raw(resource_id, property_id))[0]

    def get_property_string(self, resource_id, property_id):
        return str(self.__get_property_raw(resource_id, property_id))

    def get_property_bytes(self, resource_id, property_id):
        return [ord(x) for x in self.__get_property_raw(resource_id, property_id)]