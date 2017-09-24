/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#include <Springboard/InternalHAL/DigitalInput.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>
#include <Springboard/Infrastructure/Controller.hpp>
#include <Springboard/Kernel/Thread.hpp>

using Springboard::Kernel::Thread;
using Springboard::InternalHAL::GPIOPinMode;
using Springboard::InternalHAL::GPIOPullConfiguration;
using Springboard::InternalHAL::GPIOOutputConfiguration;
using Springboard::InternalHAL::GPIOOutputSpeed;
using Springboard::InternalHAL::InternalGPIOPin;
using Springboard::InternalHAL::DigitalInput;
using Springboard::InternalHAL::DigitalOutput;
using Springboard::Infrastructure::Controller;

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
        mButton.Configure();
        mLED.Configure();

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
        mLED.Configure();

        while (!ShouldTerminate()) {
            mLED.Toggle();
            Sleep_ms(100);
        }
    }

    DigitalOutput mLED;
};

class TestController : public Controller
{
public:
    TestController() : Controller(1, "TestController")
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

        Controller::Start();

        mToggleThread.Start();
        mButtonThread.Start();
    }

private:
    ToggleThread mToggleThread;
    ButtonThread mButtonThread;
};

int main(void)
{
    TestController testController;
    testController.Start();

    while (true) {
        Thread::Sleep_ms(500);
    }

    return 0;
}
