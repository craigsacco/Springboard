#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <Springboard/InternalHAL/DigitalInput.hpp>
#include <Springboard/InternalHAL/DigitalOutput.hpp>
#include <Springboard/Kernel/Kernel.hpp>

class TestThread : public Springboard::Kernel::StaticThread<128>
{
public:
    TestThread()
        : Springboard::Kernel::StaticThread<128>("InputThread", NORMALPRIO),
          mButton(GPIOE, 6, Springboard::InternalHAL::PullConfiguration::Floating),
          mLED(GPIOH, 2, Springboard::InternalHAL::PullConfiguration::Floating,
               Springboard::InternalHAL::OutputConfiguration::PushPull,
               Springboard::InternalHAL::OutputSpeed::Low)
    {
    }

    void Run() override final
    {
        while (true) {
            mLED.Set(mButton.Get());
            Sleep_ms(10);
        }
    }

private:
    Springboard::InternalHAL::DigitalInput mButton;
    Springboard::InternalHAL::DigitalOutput mLED;
};

int main(void)
{
    Springboard::InternalHAL::Initialise();
    Springboard::Kernel::Initialise();

    TestThread testThread;
    testThread.Start();

    while (true) {
        Springboard::Kernel::Thread::Sleep_ms(500);
    }

    return 0;
}
