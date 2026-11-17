#pragma once

#include <chrono>
#include <cstdint>

namespace coreprobe
{
    enum class EventType: std::uint8_t
    {
        Button,
        Axis,
        Sensor,
        DeviceConnected,
        DeviceDisconnected,
        Unknown
    };

    struct Event
    {
        using Clock = std::chrono::steady_clock;

        std::uint32_t device_id = 0;

        EventType type = EventType::Unknown;
        
        std::uint32_t code = 0; //用来标识同一类事件里，具体是哪一个按键、摇杆或传感器

        float value = 0.0f; // used for button, sentor, and axis events
        Clock::time_point timestamp = Clock::now();
    };
}