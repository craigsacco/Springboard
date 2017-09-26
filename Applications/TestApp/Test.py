#!/usr/bin/python

import sys
sys.path.append("../../Springboard/PythonLib")

from pyspringboard.Client import SerialClient
from pyspringboard.MessageHandler import MessageHandler
from pyspringboard.Controller import Controller
from pyspringboard.drivers.MCP23017 import MCP23017


class TestController(Controller):

    def __init__(self, handler):
        super(TestController, self).__init__(handler)
        self.__expander = MCP23017(handler, 2)

    @property
    def expander(self):
        return self.__expander


def main():

    client = SerialClient("/dev/ttyUSB0")
    client.connect()
    handler = MessageHandler(client)
    controller = TestController(handler)

    try:
        print "controller resource type: {0}".format(controller.get_resource_type())
        print "controller resource name: {0}".format(controller.get_resource_name())
        print "controller RTOS type: {0}".format(controller.get_rtos_type())
        print "controller RTOS version: {0}".format(controller.get_rtos_version())
        print "expander resource type: {0}".format(controller.expander.get_resource_type())
        print "expander resource name: {0}".format(controller.expander.get_resource_name())
    finally:
        client.close()


if __name__ == "__main__":
    main()
