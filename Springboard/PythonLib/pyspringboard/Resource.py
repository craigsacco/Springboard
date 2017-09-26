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

class Resource(object):

    def __init__(self, handler, resource_id):
        self.__handler = handler
        self.__resource_id = resource_id

    def _get_property_bool(self, property_id):
        return self.__handler.get_property_bool(self.__resource_id, property_id)

    def _get_property_uint8(self, property_id):
        return self.__handler.get_property_uint8(self.__resource_id, property_id)

    def _get_property_uint16(self, property_id):
        return self.__handler.get_property_uint16(self.__resource_id, property_id)

    def _get_property_uint32(self, property_id):
        return self.__handler.get_property_uint32(self.__resource_id, property_id)

    def _get_property_uint64(self, property_id):
        return self.__handler.get_property_uint64(self.__resource_id, property_id)

    def _get_property_int8(self, property_id):
        return self.__handler.get_property_int8(self.__resource_id, property_id)

    def _get_property_int16(self, property_id):
        return self.__handler.get_property_int16(self.__resource_id, property_id)

    def _get_property_int32(self, property_id):
        return self.__handler.get_property_int32(self.__resource_id, property_id)

    def _get_property_int64(self, property_id):
        return self.__handler.get_property_int64(self.__resource_id, property_id)

    def _get_property_float(self, property_id):
        return self.__handler.get_property_float(self.__resource_id, property_id)

    def _get_property_double(self, property_id):
        return self.__handler.get_property_double(self.__resource_id, property_id)

    def _get_property_string(self, property_id):
        return self.__handler.get_property_string(self.__resource_id, property_id)

    def _get_property_bytes(self, property_id):
        return self.__handler.get_property_bytes(self.__resource_id, property_id)

    def get_resource_type(self):
        return self._get_property_uint16(1)

    def get_resource_name(self):
        return self._get_property_string(2)
