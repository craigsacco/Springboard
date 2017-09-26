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


import serial

class Client(object):

    def __init__(self):
        pass

    def connect(self):
        pass

    def close(self):
        pass

    def read(self, len):
        pass

    def write(self, data):
        pass


class SerialClient(Client):

    def __init__(self, port, baudrate=9600, timeout=1, debug=False):
        super(SerialClient).__init__()
        self._url = port
        self._baudrate = baudrate
        self._timeout = timeout
        if debug:
            self._url = "spy://" + self._url
        self._client = None

    def connect(self):
        self._client = serial.serial_for_url(self._url, timeout=self._timeout)
        self._client.baudrate = self._baudrate

    def close(self):
        self._client.close()
        self._client = None

    def read(self, len):
        return self._client.read(len)

    def write(self, data):
        self._client.write(serial.to_bytes(data))
