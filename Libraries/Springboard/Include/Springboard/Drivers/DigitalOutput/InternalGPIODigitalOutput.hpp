// #pragma once

// #include "Springboard/Drivers/DigitalOutput/IDigitalOutput.hpp"

// namespace Springboard {
// namespace Drivers {

// namespace GPIO {
//     class InternalGPIO;
// }

// namespace DigitalOutput {

// class InternalGPIODigitalOutput : public IDigitalOutput
// {
//     struct DriverSpecificConfig_t {

//         uint8_t pin;
//     };

// public:
//     InternalGPIODigitalOutput();
//     Error_t Configure(DriverConfig_t* config) override final;

// private:
//     GPIO_TypeDef* mGPIO;

// private:
//     struct InternalGPIOStaticInfoRecord_t {
//         GPIOPort_t port;
//         GPIO_TypeDef* gpio;
//         uint32_t rccEnable;
//     };
// };

// }
// }
// }
