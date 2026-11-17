#pragma once
#include <optional>
#include <string>
#include <cstdint>

namespace coreprobe
{
    enum class DeviceType
    {
        Controller,
        Serial,
        Sensor,
        Unknown
    };

    enum class DeviceStatus
    {
        Connected,
        Disconnected,
        Unknown,
        Error
    };

    struct DeviceInfo
    {
        std::string name;
        std::string serialNumber;
        DeviceType type;
        std::optional<std::uint16_t> vendorId;
        std::optional<std::uint16_t> productId;
    };

    class IDevice
    {
    public:
        virtual ~IDevice() = default;

        // Establish a connection to the device.
        virtual bool connect() = 0;

        // Disconnect from the device.
        virtual void disconnect() = 0;

        // Get the current status of the device.
        virtual DeviceInfo getDeviceInfo() const = 0;

        // Return current connection status
        virtual DeviceStatus getStatus() const = 0;
    };

}