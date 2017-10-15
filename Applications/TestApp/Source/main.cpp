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
#if SPRINGBOARD_HAL_ENABLE_I2C
using Springboard::ExternalHAL::MCP23017;
using Springboard::Drivers::MCP23017Driver;
#endif
#if SPRINGBOARD_HAL_ENABLE_UART
using Springboard::ExternalHAL::NMEA0183GPSDevice;
using Springboard::Drivers::NMEA0183GPSDriver;
#endif
#if SPRINGBOARD_HAL_ENABLE_SPI
using Springboard::ExternalHAL::AT45DB041E;
using Springboard::Drivers::AT45DB041EDriver;
#endif


#if MCU_FAMILY == MCU_FAMILY_STM32F4 && MCU_LINE == MCU_LINE_STM32F407_F417
// Setup on a Waveshare Open407I-C development board
static constexpr size_t SerialMessagingUARTBusIndex = 2;
static constexpr GPIOPinMode SerialMessagingUARTBusPinMode =
    GPIOPinMode::AlternateFunction_USART1;
static constexpr InternalGPIOPin::Pad SerialMessagingUARTBusPad_TX =
    { GPIOA, 2 };
static constexpr InternalGPIOPin::Pad SerialMessagingUARTBusPad_RX =
    { GPIOA, 3 };
static constexpr size_t GPSDeviceUARTBusIndex = 1;
static constexpr GPIOPinMode GPSDeviceUARTBusPinMode =
    GPIOPinMode::AlternateFunction_USART3;
static constexpr InternalGPIOPin::Pad GPSDeviceUARTBusPad_TX = { GPIOA, 9 };
static constexpr InternalGPIOPin::Pad GPSDeviceUARTBusPad_RX = { GPIOA, 10 };
static constexpr size_t I2CBusIndex = 3;
static constexpr GPIOPinMode I2CBusPinMode =
    GPIOPinMode::AlternateFunction_I2C1;
static constexpr InternalGPIOPin::Pad I2CBusPad_SDA = { GPIOC, 9 };
static constexpr InternalGPIOPin::Pad I2CBusPad_SCL = { GPIOH, 7 };
static constexpr size_t SPIBusIndex = 1;
static constexpr GPIOPinMode SPIBusPinMode =
    GPIOPinMode::AlternateFunction_SPI1;
static constexpr InternalGPIOPin::Pad SPIBusPad_CLK = { GPIOA, 5 };
static constexpr InternalGPIOPin::Pad SPIBusPad_MISO = { GPIOA, 6 };
static constexpr InternalGPIOPin::Pad SPIBusPad_MOSI = { GPIOA, 7 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nCS = { GPIOA, 4 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nWP = { GPIOH, 12 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nRST = { GPIOB, 12 };
static constexpr InternalGPIOPin::Pad LEDPad_1 = { GPIOH, 2 };
static constexpr InternalGPIOPin::Pad LEDPad_2 = { GPIOH, 3 };
static constexpr InternalGPIOPin::Pad LEDPad_3 = { GPIOI, 8 };
static constexpr InternalGPIOPin::Pad LEDPad_4 = { GPIOI, 10 };
#endif  // MCU_FAMILY == MCU_FAMILY_STM32F4 && MCU_LINE == ...

#if MCU_FAMILY == MCU_FAMILY_STM32F4 && MCU_LINE == MCU_LINE_STM32F429_F439
// Setup on a Waveshare Open429I-C development board
static constexpr size_t SerialMessagingUARTBusIndex = 1;
static constexpr GPIOPinMode SerialMessagingUARTBusPinMode =
    GPIOPinMode::AlternateFunction_USART1;
static constexpr InternalGPIOPin::Pad SerialMessagingUARTBusPad_TX =
    { GPIOD, 8 };
static constexpr InternalGPIOPin::Pad SerialMessagingUARTBusPad_RX =
    { GPIOD, 9 };
static constexpr size_t GPSDeviceUARTBusIndex = 3;
static constexpr GPIOPinMode GPSDeviceUARTBusPinMode =
    GPIOPinMode::AlternateFunction_USART3;
static constexpr InternalGPIOPin::Pad GPSDeviceUARTBusPad_TX = { GPIOA, 9 };
static constexpr InternalGPIOPin::Pad GPSDeviceUARTBusPad_RX = { GPIOA, 10 };
static constexpr size_t I2CBusIndex = 1;
static constexpr GPIOPinMode I2CBusPinMode =
    GPIOPinMode::AlternateFunction_I2C1;
static constexpr InternalGPIOPin::Pad I2CBusPad_SDA = { GPIOB, 6 };
static constexpr InternalGPIOPin::Pad I2CBusPad_SCL = { GPIOB, 7 };
static constexpr size_t SPIBusIndex = 1;
static constexpr GPIOPinMode SPIBusPinMode =
    GPIOPinMode::AlternateFunction_SPI1;
static constexpr InternalGPIOPin::Pad SPIBusPad_CLK = { GPIOA, 5 };
static constexpr InternalGPIOPin::Pad SPIBusPad_MISO = { GPIOA, 6 };
static constexpr InternalGPIOPin::Pad SPIBusPad_MOSI = { GPIOA, 7 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nCS = { GPIOA, 4 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nWP = { GPIOH, 11 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nRST = { GPIOH, 10 };
static constexpr InternalGPIOPin::Pad LEDPad_1 = { GPIOF, 6 };
static constexpr InternalGPIOPin::Pad LEDPad_2 = { GPIOF, 7 };
static constexpr InternalGPIOPin::Pad LEDPad_3 = { GPIOF, 8 };
static constexpr InternalGPIOPin::Pad LEDPad_4 = { GPIOF, 9 };
#endif  // MCU_FAMILY == MCU_FAMILY_STM32F4 && MCU_LINE == ...

#if MCU_FAMILY == MCU_FAMILY_STM32F7 && MCU_LINE == MCU_LINE_STM32F746_F756
// Setup on a Waveshare Open746I-C development board
static constexpr size_t SerialMessagingUARTBusIndex = 1;
static constexpr GPIOPinMode SerialMessagingUARTBusPinMode =
    GPIOPinMode::AlternateFunction_USART1;
static constexpr InternalGPIOPin::Pad SerialMessagingUARTBusPad_TX =
    { GPIOA, 9 };
static constexpr InternalGPIOPin::Pad SerialMessagingUARTBusPad_RX =
    { GPIOA, 10 };
static constexpr size_t GPSDeviceUARTBusIndex = 3;
static constexpr GPIOPinMode GPSDeviceUARTBusPinMode =
    GPIOPinMode::AlternateFunction_USART3;
static constexpr InternalGPIOPin::Pad GPSDeviceUARTBusPad_TX = { GPIOD, 8 };
static constexpr InternalGPIOPin::Pad GPSDeviceUARTBusPad_RX = { GPIOD, 9 };
static constexpr size_t I2CBusIndex = 1;
static constexpr GPIOPinMode I2CBusPinMode =
    GPIOPinMode::AlternateFunction_I2C1;
static constexpr InternalGPIOPin::Pad I2CBusPad_SDA = { GPIOB, 8 };
static constexpr InternalGPIOPin::Pad I2CBusPad_SCL = { GPIOB, 9 };
static constexpr size_t SPIBusIndex = 1;
static constexpr GPIOPinMode SPIBusPinMode =
    GPIOPinMode::AlternateFunction_SPI1;
static constexpr InternalGPIOPin::Pad SPIBusPad_CLK = { GPIOA, 5 };
static constexpr InternalGPIOPin::Pad SPIBusPad_MISO = { GPIOA, 6 };
static constexpr InternalGPIOPin::Pad SPIBusPad_MOSI = { GPIOA, 7 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nCS = { GPIOA, 4 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nWP = { GPIOH, 11 };
static constexpr InternalGPIOPin::Pad ExternalFlashPad_nRST = { GPIOH, 10 };
static constexpr InternalGPIOPin::Pad LEDPad_1 = { GPIOB, 6 };
static constexpr InternalGPIOPin::Pad LEDPad_2 = { GPIOB, 7 };
static constexpr InternalGPIOPin::Pad LEDPad_3 = { GPIOH, 4 };
static constexpr InternalGPIOPin::Pad LEDPad_4 = { GPIOI, 8 };
#endif  // MCU_FAMILY == MCU_FAMILY_STM32F7 && MCU_LINE == ...


class TestController : public Controller
{
public:
    TestController() :
        Controller(1, "TestController")
#if SPRINGBOARD_HAL_ENABLE_I2C
        , mExpander(mPeripheralFactory.GetI2CBus(I2CBusIndex), 0x20, 400000)
        , mExpanderDriver(this, 2, "MCP23017", &mExpander)
#endif
#if SPRINGBOARD_HAL_ENABLE_UART
        , mSerialMessaging(
              this, mPeripheralFactory.GetUARTBus(SerialMessagingUARTBusIndex),
              "SerialMessaging", NORMALPRIO)
        , mGPS(mPeripheralFactory.GetUARTBus(GPSDeviceUARTBusIndex),
               "GPSDeviceComms", NORMALPRIO-1)
        , mGPSDriver(this, 3, "GPSDevice", &mGPS)
#endif
#if SPRINGBOARD_HAL_ENABLE_SPI
        , mExternalFlash_nCS(ExternalFlashPad_nCS,
                             GPIOPullConfiguration::Floating,
                             GPIOOutputConfiguration::PushPull,
                             GPIOOutputSpeed::Low_2MHz)
        , mExternalFlash_nWP(ExternalFlashPad_nWP,
                             GPIOPullConfiguration::Floating,
                             GPIOOutputConfiguration::PushPull,
                             GPIOOutputSpeed::Low_2MHz)
        , mExternalFlash_nRST(ExternalFlashPad_nRST,
                              GPIOPullConfiguration::Floating,
                              GPIOOutputConfiguration::PushPull,
                              GPIOOutputSpeed::Low_2MHz)
        , mExternalFlash(mPeripheralFactory.GetSPIBus(SPIBusIndex),
                         &mExternalFlash_nCS, 25000000, &mExternalFlash_nWP,
                         &mExternalFlash_nRST)
        , mExternalFlashDriver(this, 4, "FlashDevice", &mExternalFlash)
#endif
    {
    }

    void Start() final
    {
        // setup I2C bus pins
        InternalGPIOPin::SetPinConfiguration(
            I2CBusPad_SDA, I2CBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::OpenDrain,
            GPIOOutputSpeed::Low_2MHz);
        InternalGPIOPin::SetPinConfiguration(
            I2CBusPad_SCL, I2CBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::OpenDrain,
            GPIOOutputSpeed::Low_2MHz);

        // setup serial messaging UART bus pins
        InternalGPIOPin::SetPinConfiguration(
            SerialMessagingUARTBusPad_TX, SerialMessagingUARTBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);
        InternalGPIOPin::SetPinConfiguration(
            SerialMessagingUARTBusPad_RX, SerialMessagingUARTBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);

        // setup GPS device UART bus pins
        InternalGPIOPin::SetPinConfiguration(
            GPSDeviceUARTBusPad_TX, GPSDeviceUARTBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);
        InternalGPIOPin::SetPinConfiguration(
            GPSDeviceUARTBusPad_RX, GPSDeviceUARTBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::Low_2MHz);

        // setup SPI1_CLK on PA5, SPI1_MISO on PA6 and SPI1_MOSI on PA7
        InternalGPIOPin::SetPinConfiguration(
            SPIBusPad_CLK, SPIBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::VeryHigh_100MHz);
        InternalGPIOPin::SetPinConfiguration(
            SPIBusPad_MISO, SPIBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::VeryHigh_100MHz);
        InternalGPIOPin::SetPinConfiguration(
            SPIBusPad_MOSI, SPIBusPinMode,
            GPIOPullConfiguration::Floating,
            GPIOOutputConfiguration::PushPull,
            GPIOOutputSpeed::VeryHigh_100MHz);

#if SPRINGBOARD_HAL_ENABLE_UART
        mPeripheralFactory.GetUARTBus(GPSDeviceUARTBusIndex)
            ->SetConfig(9600);
        mPeripheralFactory.GetUARTBus(SerialMessagingUARTBusIndex)
            ->SetConfig(57600);
#endif
//        mPeripheralFactory.GetWatchdog(1)
//            ->SetTimeout(100000U);

        Controller::Start();

        mSerialMessaging.Start();
        mGPS.Start();
    }

private:
#if SPRINGBOARD_HAL_ENABLE_I2C
    MCP23017 mExpander;
    MCP23017Driver mExpanderDriver;
#endif
#if SPRINGBOARD_HAL_ENABLE_UART
    MessageStreamHandler mSerialMessaging;
    NMEA0183GPSDevice mGPS;
    NMEA0183GPSDriver mGPSDriver;
#endif
#if SPRINGBOARD_HAL_ENABLE_SPI
    DigitalOutput mExternalFlash_nCS;
    DigitalOutput mExternalFlash_nWP;
    DigitalOutput mExternalFlash_nRST;
    AT45DB041E mExternalFlash;
    AT45DB041EDriver mExternalFlashDriver;
#endif
};

int main(void)
{
    volatile uint32_t rstf = RCC->CSR;

    TestController testController;
    testController.Start();

    DigitalOutput led1(LEDPad_1, GPIOPullConfiguration::Floating,
                       GPIOOutputConfiguration::PushPull,
                       GPIOOutputSpeed::Low_2MHz);
    DigitalOutput led2(LEDPad_2, GPIOPullConfiguration::Floating,
                       GPIOOutputConfiguration::PushPull,
                       GPIOOutputSpeed::Low_2MHz);
    DigitalOutput led3(LEDPad_3, GPIOPullConfiguration::Floating,
                       GPIOOutputConfiguration::PushPull,
                       GPIOOutputSpeed::Low_2MHz);
    DigitalOutput led4(LEDPad_4, GPIOPullConfiguration::Floating,
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
