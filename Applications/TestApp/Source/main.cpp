/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/DigitalInput.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>
#include <Springboard/InternalHAL/PeripheralFactory.hpp>
#include <Springboard/ExternalHAL/PCF8574.hpp>
#include <Springboard/ExternalHAL/PCF8574DigitalInput.hpp>
#include <Springboard/Drivers/PCF8574Driver.hpp>
#include <Springboard/Kernel/Kernel.hpp>

using Springboard::Kernel::Thread;
using Springboard::InternalHAL::GPIOPinMode;
using Springboard::InternalHAL::GPIOPullConfiguration;
using Springboard::InternalHAL::GPIOOutputConfiguration;
using Springboard::InternalHAL::GPIOOutputSpeed;
using Springboard::InternalHAL::InternalGPIOPin;
using Springboard::InternalHAL::DigitalInput;
using Springboard::InternalHAL::DigitalOutput;
using Springboard::InternalHAL::PeripheralFactory;
using Springboard::ExternalHAL::PCF8574;
using Springboard::ExternalHAL::PCF8574DigitalInput;
using Springboard::Drivers::PCF8574Driver;

class ButtonThread : public Thread
{
public:
    ButtonThread()
        : Thread("ButtonThread", 256, NORMALPRIO-3),
          mButton(GPIOE, 6, GPIOPullConfiguration::PullDown),
          mLED(GPIOH, 2, GPIOPullConfiguration::Floating,
               GPIOOutputConfiguration::PushPull,
               GPIOOutputSpeed::Low_2MHz)
    {
    }

private:
    void Run() final
    {
        while (!ShouldTerminate()) {
            mLED.Set(mButton.Get());
            Sleep_ms(10);
        }
    }

    DigitalInput mButton;
    DigitalOutput mLED;
};

class ToggleThread : public Thread
{
public:
    ToggleThread()
        : Thread("ToggleThread", 256, NORMALPRIO-2),
          mLED(GPIOI, 10, GPIOPullConfiguration::Floating,
               GPIOOutputConfiguration::PushPull,
               GPIOOutputSpeed::Low_2MHz)
    {
    }

private:
    void Run() final
    {
        while (!ShouldTerminate()) {
            mLED.Toggle();
            Sleep_ms(100);
        }
    }

    DigitalOutput mLED;
};

class ExpanderThread : public Thread
{
public:
    explicit ExpanderThread(PCF8574Driver* driver)
        : Thread("ExpanderThread", 1024, NORMALPRIO-1),
          mDriver(driver),
          mLED(GPIOH, 3, GPIOPullConfiguration::Floating,
               GPIOOutputConfiguration::PushPull,
               GPIOOutputSpeed::Low_2MHz)
    {
    }

private:
    void Run() final
    {
        while (!ShouldTerminate()) {
            uint8_t value = 0;
            size_t len = 0;
            ResultCode result = mDriver->GetProperty(100, &value, &len);
            ASSERT(result == RC_OK && len == 1);
            mLED.Set(value & 0x01);
            Sleep_ms(500);
        }
    }

    PCF8574Driver* mDriver;
    DigitalOutput mLED;
};

int main(void)
{
    Springboard::InternalHAL::Initialise();
    Springboard::Kernel::Initialise();

    static ToggleThread toggleThread;
    toggleThread.Start();

    static ButtonThread buttonThread;
    buttonThread.Start();

    // setup I2C3_SDA on PC9, and I2C3_SCL on PH7
    InternalGPIOPin::SetPinConfiguration(GPIOC, 9,
                                         GPIOPinMode::AlternateFunction_I2C3,
                                         GPIOPullConfiguration::Floating,
                                         GPIOOutputConfiguration::OpenDrain,
                                         GPIOOutputSpeed::Low_2MHz);
    InternalGPIOPin::SetPinConfiguration(GPIOH, 7,
                                         GPIOPinMode::AlternateFunction_I2C3,
                                         GPIOPullConfiguration::Floating,
                                         GPIOOutputConfiguration::OpenDrain,
                                         GPIOOutputSpeed::Low_2MHz);

    // start peripheral factory
    static PeripheralFactory peripheralFactory;
    peripheralFactory.Start();

    PCF8574 expander(peripheralFactory.GetI2CBus(3), 0x20, 100000);
    PCF8574Driver expanderDriver(1, &expander);
    static ExpanderThread expanderThread(&expanderDriver);
    expanderThread.Start();

    while (true) {
        Thread::Sleep_ms(500);
    }

    return 0;
}
