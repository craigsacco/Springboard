#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/DigitalInput.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>
#include <Springboard/Kernel/Kernel.hpp>

using namespace Springboard::Kernel;
using namespace Springboard::InternalHAL;

class ButtonThread : public StaticThread<256>
{
public:
    ButtonThread()
        : StaticThread<256>("ButtonThread", NORMALPRIO),
          mButton(GPIOE, 6, GPIOPullConfiguration::PullDown),
          mLED(GPIOH, 2, GPIOPullConfiguration::Floating,
               GPIOOutputConfiguration::PushPull,
               GPIOOutputSpeed::Low_2MHz)
    {
    }

    void Run() override final
    {
        while (!ShouldTerminate()) {
            mLED.Set(mButton.Get());
            Sleep_ms(10);
        }
    }

private:
    DigitalInput mButton;
    DigitalOutput mLED;
};

class ToggleThread : public StaticThread<256>
{
public:
    ToggleThread()
        : StaticThread<256>("ToggleThread", NORMALPRIO-1),
          mLED(GPIOI, 10, GPIOPullConfiguration::Floating,
               GPIOOutputConfiguration::PushPull,
               GPIOOutputSpeed::Low_2MHz)
    {
    }

    void Run() override final
    {
        while (!ShouldTerminate()) {
            mLED.Toggle();
            Sleep_ms(100);
        }
    }

private:
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

    while (true) {
        Thread::Sleep_ms(500);
    }

    return 0;
}
