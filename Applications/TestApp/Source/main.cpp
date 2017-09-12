#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/DigitalInput.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>
#include <Springboard/InternalHAL/PeripheralFactory.hpp>
#include <Springboard/ExternalHAL/PCF8574.hpp>
#include <Springboard/Kernel/Kernel.hpp>

using namespace Springboard::Kernel;
using namespace Springboard::InternalHAL;
using namespace Springboard::ExternalHAL;

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
    void Run() override final
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
    void Run() override final
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
    ExpanderThread(PCF8574* expander)
        : Thread("ExpanderThread", 256, NORMALPRIO-1),
          mExpander(expander),
          mLED(GPIOH, 3, GPIOPullConfiguration::Floating,
               GPIOOutputConfiguration::PushPull,
               GPIOOutputSpeed::Low_2MHz)
    {
    }

private:
    void Run() override final
    {
        while (!ShouldTerminate()) {
            uint8_t value = mExpander->ReadPort();
            mLED.Set(value & 0x01);
            Sleep_ms(500);
        }
    }

    PCF8574* mExpander;
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
    InternalGPIOPin::SetPinConfiguration(GPIOC, 9, GPIOPinMode::AlternateFunction_I2C3,
                                         GPIOPullConfiguration::Floating,
                                         GPIOOutputConfiguration::OpenDrain,
                                         GPIOOutputSpeed::Low_2MHz);
    InternalGPIOPin::SetPinConfiguration(GPIOH, 7, GPIOPinMode::AlternateFunction_I2C3,
                                         GPIOPullConfiguration::Floating,
                                         GPIOOutputConfiguration::OpenDrain,
                                         GPIOOutputSpeed::Low_2MHz);

    // start peripheral factory
    static PeripheralFactory peripheralFactory;
    peripheralFactory.Start();

    PCF8574 expander(peripheralFactory.GetI2CBus(3), 0x20, 100000);
    static ExpanderThread expanderThread(&expander);
    expanderThread.Start();

    while (true) {
        Thread::Sleep_ms(500);
    }

    return 0;
}
