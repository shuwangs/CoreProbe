// connect device and events 
#pragma once


#include <SDL3/SDL.h>
#include <vector>

#include "coreprobe/core/device.hpp"
#include "coreprobe/core/event.hpp"

namespace coreprobe
{
    class SDLController final : public IDevice
    {
    public:
        SDLController(int deviceIndex);
        ~SDLController() override;

        SDLController(const SDLController&) = delete;
        SDLController& operator=(const SDLController&) = delete;


        bool connect() override;
        void disconnect() override;

        DeviceInfo getDeviceInfo() const override;
        DeviceStatus getStatus() const override;

        std::vector<Event> pollEvents();

    private:
        SDL_Gamepad* gamepad_ = nullptr;

        SDL_JoystickID instanceId_ = 0;

        DeviceStatus status_ = DeviceStatus::Disconnected;
    };
}