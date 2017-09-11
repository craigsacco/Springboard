#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/DigitalInput.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>
#include <Springboard/InternalHAL/I2CBus.hpp>
#include <Springboard/ExternalHAL/PCF8574.hpp>
#include <Springboard/Kernel/Kernel.hpp>

using namespace Springboard::Kernel;
using namespace Springboard::InternalHAL;
using namespace Springboard::ExternalHAL;

class ButtonThread : public StaticThread<256>
{
public:
    ButtonThread()
        : StaticThread<256>("ButtonThread", NORMALPRIO-3),
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

class ToggleThread : public StaticThread<256>
{
public:
    ToggleThread()
        : StaticThread<256>("ToggleThread", NORMALPRIO-2),
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

class ExpanderThread : public StaticThread<256>
{
public:
    ExpanderThread(PCF8574* expander)
        : StaticThread<256>("ExpanderThread", NORMALPRIO-1),
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

    // Setup I2C3_SDA on PC9, and I2C3_SCL on PH7
    InternalGPIOPin::SetPinConfiguration(GPIOC, 9, GPIOPinMode::AlternateFunction_I2C3,
                                         GPIOPullConfiguration::Floating,
                                         GPIOOutputConfiguration::OpenDrain,
                                         GPIOOutputSpeed::Low_2MHz);
    InternalGPIOPin::SetPinConfiguration(GPIOH, 7, GPIOPinMode::AlternateFunction_I2C3,
                                         GPIOPullConfiguration::Floating,
                                         GPIOOutputConfiguration::OpenDrain,
                                         GPIOOutputSpeed::Low_2MHz);

    static I2CBus i2c3Bus(&I2CD3, I2CMode::I2C);
    i2c3Bus.Start();

    PCF8574 expander(&i2c3Bus, 0x20, 100000);
    static ExpanderThread expanderThread(&expander);
    expanderThread.Start();

    while (true) {
        Thread::Sleep_ms(500);
    }

    return 0;
}
