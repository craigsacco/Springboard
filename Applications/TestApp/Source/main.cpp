#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/DigitalInput.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>
#include <Springboard/Kernel/Kernel.hpp>

using namespace Springboard::Kernel;
using namespace Springboard::InternalHAL;

/*
class InputThread : public StaticThread<128>
{
public:
    InputThread()
        : StaticThread<128>("InputThread", NORMALPRIO),
          mButton(GPIOF, 10, PullConfiguration::PullDown),
          mLED(GPIOH, 2, PullConfiguration::Floating,
               OutputConfiguration::PushPull,
               OutputSpeed::Low)
    {
    }

    void Run() override final
    {
        while (!ShouldTerminate()) {
            bool state = mButton.Get();
            mLED.Set(state);
            Sleep_ms(10);
        }
    }

private:
    DigitalInput mButton;
    DigitalOutput mLED;
};

class OutputThread : public StaticThread<128>
{
public:
    OutputThread()
        : StaticThread<128>("OutputThread", NORMALPRIO-1),
          mLED(GPIOI, 10, PullConfiguration::Floating,
               OutputConfiguration::PushPull,
               OutputSpeed::Low)
    {
    }

    void Run() override final
    {
        while (!ShouldTerminate()) {
            mLED.Toggle();
            Sleep_ms(500);
        }
    }

private:
    DigitalOutput mLED;
};
*/

int main(void)
{
    Springboard::InternalHAL::Initialise();
    Springboard::Kernel::Initialise();

    /*
    InputThread inputThread;
    OutputThread outputThread;

    inputThread.Start();
    outputThread.Start();
    */

    DigitalInput Button(GPIOF, 10, PullConfiguration::PullDown);
    DigitalOutput LED(GPIOH, 2, PullConfiguration::Floating,
                      OutputConfiguration::PushPull,
                      OutputSpeed::Low);

    while (true) {
        bool state = Button.Get();
        LED.Set(state);
        Thread::Sleep_ms(10);
    }

    return 0;
}
