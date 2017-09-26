

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
