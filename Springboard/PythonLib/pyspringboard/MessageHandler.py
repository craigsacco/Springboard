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
        self._client = client
        self._seqno = 1

    def get_next_seqno(self):
        seqno = self._seqno
        self._seqno = 1 if self._seqno == 255 else self._seqno + 1
        return seqno

    def send_message(self, payload):
        msg = struct.pack("<BBB", 0xfd, 0x02, len(payload) + 1)
        msg += payload
        msg += struct.pack("<BB", 0x03, 0xfc)
        checksum = 0
        for x in msg:
            checksum ^= ord(x)
        msg += struct.pack("<B", checksum)
        self._client.write(msg)

    def get_message(self):
        msg = self._client.read(3)
        msg += self._client.read((ord(msg[2]) - 1) + 3)
        sof, length = struct.unpack("<HB", msg[0:3])
        data = msg[3:(3 + length) - 1]
        eof, checksum = struct.unpack("<HB", msg[(3 + length) - 1:])
        expected = 0
        for x in msg[:-1]:
            expected ^= ord(x)
        if checksum != expected:
            raise Exception("checksum mismatch: {0} != {1}".format(checksum, expected))
        return data

    def get_property_raw(self, resource_id, property_id):
        seqno = self.get_next_seqno()
        msg = struct.pack("<BBHH", self.get_next_seqno(), MessageHandler.MSG_TYPE_GET_PROPERTY_REQUEST, resource_id,
                          property_id)
        self.send_message(msg)
        rsp_data = self.get_message()
        rsp_seqno, rsp_type, rsp_resource_id, rsp_property_id, rsp_resultcode = struct.unpack("<BBHHI", rsp_data[0:10])
        if rsp_type != MessageHandler.MSG_TYPE_GET_PROPERTY_RESPONSE:
            raise Exception("unexpected type: {0} != {1}".format(MessageHandler.MSG_TYPE_GET_PROPERTY_RESPONSE,
                                                                 rsp_type))
        if seqno != rsp_seqno:
            raise Exception("unexpected seqno: {0} != {1}".format(seqno, rsp_seqno))
        if resource_id != rsp_resource_id:
            raise Exception("unexpected resid: {0} != {1}".format(resource_id, rsp_resource_id))
        if property_id != rsp_property_id:
            raise Exception("unexpected propid: {0} != {1}".format(property_id, rsp_property_id))
        if rsp_resultcode != 0:
            raise Exception("get property request returned result code 0x{0:08x}".format(rsp_resultcode))
        return rsp_data[10:]

    def get_property_bool(self, resource_id, property_id):
        return struct.unpack("<B", self.get_property_raw(resource_id, property_id))[0] != 0

    def get_property_uint8(self, resource_id, property_id):
        return struct.unpack("<B", self.get_property_raw(resource_id, property_id))[0]

    def get_property_uint16(self, resource_id, property_id):
        return struct.unpack("<H", self.get_property_raw(resource_id, property_id))[0]

    def get_property_uint32(self, resource_id, property_id):
        return struct.unpack("<I", self.get_property_raw(resource_id, property_id))[0]

    def get_property_uint64(self, resource_id, property_id):
        return struct.unpack("<Q", self.get_property_raw(resource_id, property_id))[0]

    def get_property_int8(self, resource_id, property_id):
        return struct.unpack("<b", self.get_property_raw(resource_id, property_id))[0]

    def get_property_int16(self, resource_id, property_id):
        return struct.unpack("<h", self.get_property_raw(resource_id, property_id))[0]

    def get_property_int32(self, resource_id, property_id):
        return struct.unpack("<i", self.get_property_raw(resource_id, property_id))[0]

    def get_property_int64(self, resource_id, property_id):
        return struct.unpack("<q", self.get_property_raw(resource_id, property_id))[0]

    def get_property_float(self, resource_id, property_id):
        return struct.unpack("<f", self.get_property_raw(resource_id, property_id))[0]

    def get_property_double(self, resource_id, property_id):
        return struct.unpack("<d", self.get_property_raw(resource_id, property_id))[0]

    def get_property_string(self, resource_id, property_id):
        return str(self.get_property_raw(resource_id, property_id))

    def get_property_bytes(self, resource_id, property_id):
        return [ord(x) for x in self.get_property_raw(resource_id, property_id)]

    def set_property_raw(self, resource_id, property_id, data):
        seqno = self.get_next_seqno()
        msg = struct.pack("<BBHH", seqno, MessageHandler.MSG_TYPE_SET_PROPERTY_REQUEST, resource_id, property_id) + \
              data
        self.send_message(msg)
        rsp_data = self.get_message()
        rsp_seqno, rsp_type, rsp_resource_id, rsp_property_id, rsp_resultcode = struct.unpack("<BBHHI", rsp_data)
        if rsp_type != MessageHandler.MSG_TYPE_SET_PROPERTY_RESPONSE:
            raise Exception("unexpected type: {0} != {1}".format(MessageHandler.MSG_TYPE_SET_PROPERTY_RESPONSE,
                                                                 rsp_type))
        if seqno != rsp_seqno:
            raise Exception("unexpected seqno: {0} != {1}".format(seqno, rsp_seqno))
        if resource_id != rsp_resource_id:
            raise Exception("unexpected resid: {0} != {1}".format(resource_id, rsp_resource_id))
        if property_id != rsp_property_id:
            raise Exception("unexpected propid: {0} != {1}".format(property_id, rsp_property_id))
        if rsp_resultcode != 0:
            raise Exception("set property request returned result code 0x{0:08x}".format(rsp_resultcode))