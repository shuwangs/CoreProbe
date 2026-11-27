#include "coreprobe/adapters/sdl_controllers.hpp"

namespace coreprobe
{
    SDLController::SDLController(SDL_JoystickID instanceId)
        : instanceId_(instanceId)
    {
    }

    // Destructor ensures that the gamepad is closed
    //  when the SDLController object is destroyed.
    SDLController::~SDLController()
    {
        disconnect();
    }

    bool SDLController::connect()
    {
        if (status_ == DeviceStatus::Connected) {
            return true; // Already connected
        }

        gamepad_ = SDL_OpenGamepad(instanceId_);
        if (!gamepad_) {
            status_ = DeviceStatus::Error;
            return false;
        }

        status_ = DeviceStatus::Connected;
        return true;
    }

    void SDLController::disconnect()
    {
       
        if (gamepad_ != nullptr) {
            SDL_CloseGamepad(gamepad_);
            gamepad_ = nullptr;
        }

        status_ = DeviceStatus::Disconnected;
    }

    DeviceInfo SDLController::getDeviceInfo() const
    {        
        DeviceInfo info{};
        info.type = DeviceType::Controller;

        if (gamepad_ != nullptr) {
            const char* name = SDL_GetGamepadName(gamepad_);

            if (name != nullptr) {
                info.name = name;
            }
        }
        return info;
    }

    DeviceStatus SDLController::getStatus() const
    {
        return status_;
    }
}