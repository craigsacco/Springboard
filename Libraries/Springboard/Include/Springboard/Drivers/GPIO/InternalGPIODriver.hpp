// #pragma once

// #include "Springboard/Drivers/GPIO/BaseGPIODriver.hpp"
// #include "stm32f4xx_gpio.h"

// namespace Springboard {
// namespace Drivers {
// namespace GPIO {

// class InternalGPIODriver : public BaseGPIODriver
// {
// public:
//     enum class GPIOPort_t : uint32_t {
//         A,
//         B,
//         C,
//         D,
//         E,
//         F,
//         G,
//         H,
//         I,
//         J,
//         K,
//     };

//     struct DriverSpecificConfig_t {
//         GPIOPort_t port;
//     };

// // public:
// //     InternalGPIODriver();
// //     Springboard::Error_t InitialiseDriver(Springboard::Drivers::IDriverLookup* lookup,
// //                                           DriverConfig_t* config) override final;
// //     GPIO_TypeDef* GetGPIO() const;

// // private:
// //     GPIO_TypeDef* mGPIO;

// // private:
// //     struct InternalGPIOStaticInfoRecord_t {
// //         GPIOPort_t port;
// //         GPIO_TypeDef* gpio;
// //         uint32_t rccEnable;
// //     };
// };

// }
// }
// }
