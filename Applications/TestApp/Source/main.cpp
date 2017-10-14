/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/DigitalInput.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>
#include <Springboard/Infrastructure/Controller.hpp>
#include <Springboard/Kernel/Kernel.hpp>
#include <Springboard/Kernel/Thread.hpp>
#include <Springboard/Comms/MessageStreamHandler.hpp>
#include <Springboard/ExternalHAL/MCP23017.hpp>
#include <Springboard/Drivers/MCP23017Driver.hpp>
#include <Springboard/ExternalHAL/NMEA0183GPSDevice.hpp>
#include <Springboard/Drivers/NMEA0183GPSDriver.hpp>
#include <Springboard/ExternalHAL/AT45DB041E.hpp>
#include <Springboard/Drivers/AT45DB041EDriver.hpp>

using Springboard::Kernel::Thread;
using Springboard::InternalHAL::GPIOPinMode;
using Springboard::InternalHAL::GPIOPullConfiguration;
using Springboard::InternalHAL::GPIOOutputConfiguration;
using Springboard::InternalHAL::GPIOOutputSpeed;
using Springboard::InternalHAL::InternalGPIOPin;
using Springboard::InternalHAL::DigitalInput;
using Springboard::InternalHAL::DigitalOutput;
using Springboard::Infrastructure::Controller;
using Springboard::Comms::MessageStreamHandler;
using Springboard::ExternalHAL::MCP23017;
using Springboard::Drivers::MCP23017Driver;
using Springboard::ExternalHAL::NMEA0183GPSDevice;
using Springboard::Drivers::NMEA0183GPSDriver;
using Springboard::ExternalHAL::AT45DB041E;
using Springboard::Drivers::AT45DB041EDriver;


class TestController : public Controller
{
public:
    TestController() :
        Controller(1, "TestController"),
        mSerialMessaging(this, mPeripheralFactory.GetUARTBus(1),
                         "SerialMessaging", NORMALPRIO),
        mExpander(mPeripheralFactory.GetI2CBus(1), 0x20, 400000),
        mExpanderDriver(this, 2, "MCP23017", &mExpander),
        mGPS(mPeripheralFactory.GetUARTBus(3), "GPSDeviceComms", NORMALPRIO-1),
        mGPSDriver(this, 3, "GPSDevice", &mGPS),
        mExternalFlash_nCS(GPIOA, 4, GPIOPullConfiguration::Floating,
                           GPIOOutputConfiguration::PushPull,
                           GPIOOutputSpeed::Low_2MHz),
        mExternalFlash_nWP(GPIOH, 11, GPIOPullConfiguration::Floating,
                           GPIOOutputConfiguration::PushPull,
                           GPIOOutputSpeed::Low_2MHz),
        mExternalFlash_nRST(GPIOH, 10, GPIOPullConfiguration::Floating,
                            GPIOOutputConfiguration::PushPull,
                            GPIOOutputSpeed::Low_2MHz),
        mExternalFlash(mPeripheralFactory.GetSPIBus(1), &mExternalFlash_nCS,
                       25000000, &mExternalFlash_nWP, &mExternalFlash_nRST),
        mExternalFlashDriver(this, 4, "FlashDevice", &mExternalFlash)
    {
    }

    void Start() final
    {
        // setup I2C1_SDA on PB6, and I2C1_SCL on PB7
        InternalGPIOPin::SetPinConfiguration(
            GPIOB, 6,
            GPIOPinMode::AlternateFunction_I2C1,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::OpenDrain,
            GPIOOutputSpeed::Low_2MHz);
        InternalGPIOPin::SetPinConfiguration(
            GPIOB, 7,
            GPIOPinMode::AlternateFunction_I2C1,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::OpenDrain,
            GPIOOutputSpeed::Low_2MHz);

        // setup USART3_TX on PD8, and USART3_RX on PD9
        InternalGPIOPin::SetPinConfiguration(
            GPIOD, 8,
            GPIOPinMode::AlternateFunction_USART3,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);
        InternalGPIOPin::SetPinConfiguration(
            GPIOD, 9,
            GPIOPinMode::AlternateFunction_USART3,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);

        // setup USART1_TX on PA9, and USART1_RX on PA10
        InternalGPIOPin::SetPinConfiguration(
            GPIOA, 9,
            GPIOPinMode::AlternateFunction_USART1,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);
        InternalGPIOPin::SetPinConfiguration(
            GPIOA, 10,
            GPIOPinMode::AlternateFunction_USART1,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);

        // setup SPI1_CLK on PA5, SPI1_MISO on PA6 and SPI1_MOSI on PA7
        InternalGPIOPin::SetPinConfiguration(
            GPIOA, 5,
            GPIOPinMode::AlternateFunction_SPI1,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::VeryHigh_100MHz);
        InternalGPIOPin::SetPinConfiguration(
            GPIOA, 6,
            GPIOPinMode::AlternateFunction_SPI1,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::VeryHigh_100MHz);
        InternalGPIOPin::SetPinConfiguration(
            GPIOA, 7,
            GPIOPinMode::AlternateFunction_SPI1,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::VeryHigh_100MHz);

        mPeripheralFactory.GetUARTBus(3)->SetConfig(9600);  // GPS
        mPeripheralFactory.GetUARTBus(1)->SetConfig(57600);  // serial client
        mPeripheralFactory.GetWatchdog(1)->SetTimeout(100000U);

        Controller::Start();

        mSerialMessaging.Start();
        mGPS.Start();
    }

private:
    MessageStreamHandler mSerialMessaging;
    MCP23017 mExpander;
    MCP23017Driver mExpanderDriver;
    NMEA0183GPSDevice mGPS;
    NMEA0183GPSDriver mGPSDriver;
    DigitalOutput mExternalFlash_nCS;
    DigitalOutput mExternalFlash_nWP;
    DigitalOutput mExternalFlash_nRST;
    AT45DB041E mExternalFlash;
    AT45DB041EDriver mExternalFlashDriver;
};

int main(void)
{
    TestController testController;
    testController.Start();

    DigitalOutput led1(GPIOF, 6, GPIOPullConfiguration::Floating,
                       GPIOOutputConfiguration::PushPull,
                       GPIOOutputSpeed::Low_2MHz);
    DigitalOutput led2(GPIOF, 7, GPIOPullConfiguration::Floating,
                       GPIOOutputConfiguration::PushPull,
                       GPIOOutputSpeed::Low_2MHz);
    DigitalOutput led3(GPIOF, 8, GPIOPullConfiguration::Floating,
                       GPIOOutputConfiguration::PushPull,
                       GPIOOutputSpeed::Low_2MHz);
    DigitalOutput led4(GPIOF, 9, GPIOPullConfiguration::Floating,
                       GPIOOutputConfiguration::PushPull,
                       GPIOOutputSpeed::Low_2MHz);

    while (true) {
        led1.Set();
        Thread::Sleep_ms(800);
        led2.Set();
        Thread::Sleep_ms(100);
        led1.Clear();
        Thread::Sleep_ms(20);
        led3.Set();
        Thread::Sleep_ms(20);
        led2.Clear();
        Thread::Sleep_ms(20);
        led4.Set();
        Thread::Sleep_ms(100);
        led3.Clear();
        Thread::Sleep_ms(800);
        led3.Set();
        Thread::Sleep_ms(100);
        led4.Clear();
        Thread::Sleep_ms(20);
        led2.Set();
        Thread::Sleep_ms(20);
        led3.Clear();
        Thread::Sleep_ms(20);
        led1.Set();
        Thread::Sleep_ms(100);
        led2.Clear();
    }

    return 0;
}
