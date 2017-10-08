#!/usr/bin/python

import sys, time
sys.path.append("../../Springboard/PythonLib")

from pyspringboard.Client import SerialClient
from pyspringboard.MessageHandler import MessageHandler
from pyspringboard.Controller import Controller
from pyspringboard.drivers.MCP23017 import MCP23017
from pyspringboard.drivers.NMEA0183GPS import NMEA0183GPS
from pyspringboard.drivers.AT45DB041E import AT45DB041E


class TestController(Controller):

    def __init__(self, handler):
        super(TestController, self).__init__(handler)
        self.__expander = MCP23017(handler, 2)
        self.__gps = NMEA0183GPS(handler, 3)
        self.__flash = AT45DB041E(handler, 4)

    @property
    def expander(self):
        return self.__expander

    @property
    def gps(self):
        return self.__gps

    @property
    def flash(self):
        return self.__flash


def main():

    client = SerialClient("/dev/ttyUSB0", baudrate=57600)
    client.connect()
    handler = MessageHandler(client)
    controller = TestController(handler)

    try:
        print "setting RTC time..."
        controller.set_rtc_time(int(time.time() * 1000))

        print "controller resource type: {0}".format(controller.get_resource_type())
        print "controller resource name: {0}".format(controller.get_resource_name())
        print "controller RTOS: {0}".format(controller.get_rtos())
        print "controller RTOS version: {0}".format(controller.get_rtos_version())
        print "controller RTOS port info: {0}".format(controller.get_rtos_port_info())
        print "controller MCU architecture: {0}".format(controller.get_mcu_architecture())
        print "controller MCU architecture rev: {0}".format(controller.get_mcu_architecture_revision())
        print "controller MCU core: {0}".format(controller.get_mcu_core_variant())
        print "controller MCU device id: 0x{0:08x}".format(controller.get_mcu_device_id())
        print "controller MCU unique id: {0}".format(list(controller.get_mcu_unique_id()))
        print "controller system time: {0}".format(controller.get_system_time())
        print "controller RTC time: {0}".format(controller.get_rtc_time())
        print "controller RTC time string: {0}".format(controller.get_rtc_time_string())
        print "controller MCU family: {0}".format(controller.get_mcu_family())
        print "controller MCU line: {0}".format(controller.get_mcu_line())
        print "controller MCU variant: {0}".format(controller.get_mcu_variant())
        print "expander resource type: {0}".format(controller.expander.get_resource_type())
        print "expander resource name: {0}".format(controller.expander.get_resource_name())
        print "GPS resource type: {0}".format(controller.gps.get_resource_type())
        print "GPS resource name: {0}".format(controller.gps.get_resource_name())
        print "GPS last fix time UTC: {0}".format(controller.gps.get_last_fix_time_utc())
        print "GPS last fix latitude: {0}".format(controller.gps.get_last_fix_latitude())
        print "GPS last fix longitude: {0}".format(controller.gps.get_last_fix_longitude())
        print "GPS last fix altitude: {0}".format(controller.gps.get_last_fix_altitude())
        print "GPS last fix satellites tracked: {0}".format(controller.gps.get_last_fix_satellites_tracked())
        print "GPS last fix quality: {0}".format(controller.gps.get_last_fix_quality())
        print "GPS last fix horizontal dilution: {0}".format(controller.gps.get_last_fix_horizontal_dilution())
        print "GPS last fix height of geoid: {0}".format(controller.gps.get_last_fix_height_of_geoid())
        print "Flash resource type: {0}".format(controller.flash.get_resource_type())
        print "Flash resource name: {0}".format(controller.flash.get_resource_name())
        controller.flash.set_reset_state(False)
        print "Flash reset state: {0}".format(controller.flash.get_reset_state())
        print "Flash JEDEC info: {0}".format(list(controller.flash.read_jedec_info()))


    finally:
        client.close()


if __name__ == "__main__":
    main()
