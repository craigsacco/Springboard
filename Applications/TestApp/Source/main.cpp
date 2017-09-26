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


class TestController : public Controller
{
public:
    TestController() :
        Controller(1, "TestController"),
        mSerialMessaging(this, mPeripheralFactory.GetUARTBus(2),
                         "SerialMessaging", NORMALPRIO-3),
        mExpander(mPeripheralFactory.GetI2CBus(3), 0x20, 400000),
        mExpanderDriver(this, 2, "MCP23017", &mExpander)
    {
    }

    void Start() final
    {
        // setup I2C3_SDA on PC9, and I2C3_SCL on PH7
        InternalGPIOPin::SetPinConfiguration(
            GPIOC, 9,
            GPIOPinMode::AlternateFunction_I2C3,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::OpenDrain,
            GPIOOutputSpeed::Low_2MHz);
        InternalGPIOPin::SetPinConfiguration(
            GPIOH, 7,
            GPIOPinMode::AlternateFunction_I2C3,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::OpenDrain,
            GPIOOutputSpeed::Low_2MHz);

        // setup USART2_TX on PA2, and USART2_RX on PA3
        InternalGPIOPin::SetPinConfiguration(
            GPIOA, 2,
            GPIOPinMode::AlternateFunction_USART2,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);
        InternalGPIOPin::SetPinConfiguration(
            GPIOA, 3,
            GPIOPinMode::AlternateFunction_USART2,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);

        mPeripheralFactory.GetUARTBus(2)->SetConfig(57600);

        Controller::Start();

        mSerialMessaging.Start();
    }

private:
    MessageStreamHandler mSerialMessaging;
    MCP23017 mExpander;
    MCP23017Driver mExpanderDriver;
};

int main(void)
{
    Springboard::InternalHAL::Initialise();
    Springboard::Kernel::Initialise();

    TestController testController;
    testController.Start();

    DigitalOutput led(GPIOI, 10, GPIOPullConfiguration::Floating,
                      GPIOOutputConfiguration::PushPull,
                      GPIOOutputSpeed::Low_2MHz);
    led.Configure();

    while (true) {
        led.Toggle();
        Thread::Sleep_ms(250);
    }

    return 0;
}
