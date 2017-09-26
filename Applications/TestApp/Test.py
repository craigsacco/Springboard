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

    client = SerialClient("/dev/ttyUSB0", baudrate=57600)
    client.connect()
    handler = MessageHandler(client)
    controller = TestController(handler)

    try:
        print "controller resource type: {0}".format(controller.get_resource_type())
        print "controller resource name: {0}".format(controller.get_resource_name())
        print "controller RTOS: {0}".format(controller.get_rtos())
        print "controller RTOS version: {0}".format(controller.get_rtos_version())
        print "controller RTOS port info: {0}".format(controller.get_rtos_port_info())
        print "controller MCU architecture: {0}".format(controller.get_mcu_architecture())
        print "controller MCU architecture rev: {0}".format(controller.get_mcu_architecture_revision())
        print "controller MCU core: {0}".format(controller.get_mcu_core_variant())
        print "controller MCU device id: 0x{0:08x}".format(controller.get_mcu_device_id())
        print "controller MCU unique id: {0}".format(controller.get_mcu_unique_id())
        print "expander resource type: {0}".format(controller.expander.get_resource_type())
        print "expander resource name: {0}".format(controller.expander.get_resource_name())
    finally:
        client.close()


if __name__ == "__main__":
    main()
