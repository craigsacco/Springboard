// #pragma once

// #include "Springboard/Drivers/GPIO/IGPIODriver.hpp"

// namespace Springboard {
// namespace Drivers {
// namespace GPIO {

// class BaseGPIODriver : public IGPIODriver
// {
// public:
//     BaseGPIODriver();
//     const DriverConfig_t* GetDriverConfig() const override final;
//     Springboard::DeviceType_t GetDeviceType() const override final;
//     Springboard::UnderlyingDriverType_t GetDriverType() const override final;
//     Springboard::Error_t Configure(Springboard::Drivers::IDriverLookup* lookup,
//                                    DriverConfig_t* config) override final;

// protected:
//     virtual Springboard::Error_t InitialiseDriver(Springboard::Drivers::IDriverLookup* lookup,
//                                                   DriverConfig_t* config) = 0;

// protected:
//     const DriverConfig_t* mConfig;
// };

// }
// }
// }
