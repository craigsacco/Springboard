#pragma once

// common includes
#include <cstdint>

namespace Springboard {

// error type
enum class Error_t : uint32_t
{
    Success,
    DeviceNotCreated,
    InvalidDeviceType,
    InvalidDeviceConfig,
    DuplicateDeviceId,
    DriverNotCreated,
    InvalidDriverType,
    InvalidDriverConfig,
};
#define RAISE_ERROR(error, message_fmt, ...)    (error)

// device and driver id and type definitions
typedef uint16_t DeviceId_t;
typedef uint32_t UnderlyingDeviceType_t;
typedef uint32_t UnderlyingDriverType_t;

// device types
enum class DeviceType_t : UnderlyingDeviceType_t {
    GPIO,
};

}
