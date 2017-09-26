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


class MCP23017(Resource):

    def __init__(self, handler, resource_id):
        super(MCP23017, self).__init__(handler, resource_id)

    def get_reg_iodir(self):
        return self._get_property_uint16(100)

    def get_reg_ipol(self):
        return self._get_property_uint16(101)

    def get_reg_gpinten(self):
        return self._get_property_uint16(102)

    def get_reg_defval(self):
        return self._get_property_uint16(103)

    def get_reg_intcon(self):
        return self._get_property_uint16(104)

    def get_reg_iocon(self):
        return self._get_property_uint8(105)

    def get_reg_gppu(self):
        return self._get_property_uint16(106)

    def get_reg_intf(self):
        return self._get_property_uint16(107)

    def get_reg_intcap(self):
        return self._get_property_uint16(108)

    def get_reg_port(self):
        return self._get_property_uint16(109)

    def get_reg_olat(self):
        return self._get_property_uint16(110)
