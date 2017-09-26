# Project Springboard

## About

Springboard is a framework that provides common services to low-level hardware using any type
of communications interface.

This project is in its infancy, but the goal in the end is to provide a powerful framework for
rapid prototyping with the end goal of reducing implementation effort.

## Features

* Real-time OS under the hood (ChibiOS/RT)
* Extendable infrastructure
* Thread-safe access to hardware

## What's Supported
* Only supports the following microcontrollers
    * STMicro STM32F407 and its siblings (405/415/417)

* Communications interface
    * Communications using a UART/USART interface
    * Access to resources (controllers, drivers, etc) using a common messaging format
    * Property get/set interface to all resources
    * Python library to support development efforts
    * **\[TODO\]** - Recovery of requests from unreliable interfaces
    * **\[TODO\]** - Support TCP/IP using lwIP
        * Subtended boards
    * **\[TODO\]** - Concurrent resource access (on embedded and Python)
    * **\[TODO\]** - Command interfaces to resources
    * **\[TODO\]** - Logging, metrics, alerts, etc...

* I2C bus arbitrator
    * Access to I2C bus is synchronised
    * On-the-fly speed configuration
    * Added drivers for following IC's
        * TI PCF8574 GPIO expander
        * Microchip MCP23017 GPIO expander
    * **\[TODO\]** - 10-bit and extended addressing support

* RTC support
    * Calendar get/set support through the communications interface

* USART interface
    * Implements IStream interface for common stream routines
    * **\[TODO\]** - Use DMA subsystem for transmitting data, currently relying on IRQ

* **\[TODO\]** SPI bus arbitrator
    * Access to I2C bus is synchronised
    * On-the-fly speed and clock phase/polarity configuration

* **\[TODO\]** CAN bus arbitrator
    * Access to CAN bus is synchronised

* **\[TODO\]** PWM/ICU/GPT controller
    * Common configuration interface for all timer-based peripherals

* **\[TODO\]** Event dispatcher
    * Event queueing for dispatching tasks in its own thread

* **\[TODO\]** So much more!!!

## Prerequisites

* [GNU Tools for ARM Embedded](http://launchpad.net/gcc-arm-embedded) - the version that I've
  been using is __6-2017-q2-update__, which is based on the following tools:
    * GNU GCC 6.3.1
    * GNU Binutils 2.28
    * GNU GDB 7.12
* cpplint - for static code analysis
* openocd - to act as a debug server

### Recommended Tools

* [Qt Creator](http://www.qt.io/download-open-source) - great C/C++ IDE for development
  and debugging
* [PyCharm](http://www.jetbrains.com/pycharm/download) - great Python IDE
* [Linux Mint](http://www.linuxmint.com) - most of the packages mentioned above can be downloaded
  either via the Ubuntu package repository, or a third-party PPA

## License

This project is subject to the MIT License.
