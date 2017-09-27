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


class NMEA0183GPS(Resource):

    def __init__(self, handler, resource_id):
        super(NMEA0183GPS, self).__init__(handler, resource_id)

    def get_last_fix_time_utc(self):
        return self._get_property_uint32(100)

    def get_last_fix_latitude(self):
        return self._get_property_float(101)

    def get_last_fix_longitude(self):
        return self._get_property_float(102)

    def get_last_fix_quality(self):
        return self._get_property_uint32(103)

    def get_last_fix_satellites_tracked(self):
        return self._get_property_uint32(104)

    def get_last_fix_horizontal_dilution(self):
        return self._get_property_float(105)

    def get_last_fix_altitude(self):
        return self._get_property_float(106)

    def get_last_fix_height_of_geoid(self):
        return self._get_property_float(107)
