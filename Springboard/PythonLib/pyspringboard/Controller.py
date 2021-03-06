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

from pyspringboard.Resource import Resource


class Controller(Resource):

    def __init__(self, handler):
        super(Controller, self).__init__(handler, 1)

    def get_rtos(self):
        return self._get_property_string(10)

    def get_rtos_version(self):
        return self._get_property_string(11)

    def get_rtos_port_info(self):
        return self._get_property_string(12)

    def get_mcu_architecture(self):
        return self._get_property_string(13)

    def get_mcu_architecture_revision(self):
        return self._get_property_string(14)

    def get_mcu_core_variant(self):
        return self._get_property_string(15)

    def get_mcu_device_id(self):
        return self._get_property_uint32(16)

    def get_mcu_unique_id(self):
        return self._get_property_bytes(17)

    def get_system_time(self):
        return self._get_property_uint32(18)

    def get_rtc_time(self):
        return self._get_property_uint64(19)

    def set_rtc_time(self, value):
        return self._set_property_uint64(19, value)

    def get_rtc_time_string(self):
        return self._get_property_string(20)

    def get_mcu_family(self):
        return self._get_property_string(21)

    def get_mcu_line(self):
        return self._get_property_string(22)

    def get_mcu_variant(self):
        return self._get_property_string(23)
