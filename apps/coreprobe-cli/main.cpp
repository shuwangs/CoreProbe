#include "coreprobe/adapters/sdl_controllers.hpp"

#include <getopt.h>
#include <iostream>
#include <string>

#include <SDL3/SDL_version.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>

void printHelp(const char* programName)
{
    std::cout << "CoreProbe — A C++ device diagnostics toolkit.\n\n"
              << "Usage:\n"
              << "  " << programName << " [--help | list]\n\n"
              << "Options:\n"
              << "  -h, --help    Show this help message and exit.\n";
}

int main(int argc, char* argv[])
{
    const option options[] = {
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, 0},
    };

    int parsedOption;
    while ((parsedOption = getopt_long(argc, argv, "h", options, nullptr)) != -1) {
        switch (parsedOption) {
        case 'h':
            printHelp(argv[0]);
            return 0;
        case '?':
            return 1;
        }
    }

    if (optind < argc) {
        const std::string command = argv[optind];
        if (command == "list" && optind + 1 == argc) {
            std::cout << "Listing devices...\n";

            int version = SDL_GetVersion();
            std::cout << version << "\n";

            // isInitialized
            bool isInitialized = SDL_Init(SDL_INIT_GAMEPAD);

            if (isInitialized) {
                std::cout <<  "Gamepad subsystem ready..." << "\n";

                int padCount = 0;

                // Get currently connected gamepads
                SDL_JoystickID *gamepads = SDL_GetGamepads(&padCount);
                if (gamepads == nullptr) {
                    std::cerr << "Failed to get gamepads: " << SDL_GetError() << "\n";
                    SDL_Quit();
                    return 1;
                } else {
                    std::cout << "Detected " << padCount << " joysticks. \n";
                    for (int i = 0; i < padCount; i++) {
                        SDL_JoystickID id = gamepads[i];
                        const char* name = SDL_GetGamepadNameForID(id);
                        // SDL_Gamepad* gamepad = SDL_OpenGamepad(id);
                        
                        // Create an SDLController instance for the detected gamepad
                        coreprobe::SDLController controller(id);
                        if (!controller.connect()) {
                            std::cerr << "Failed to open gamepad: "
                                    << SDL_GetError() << '\n';

                            SDL_free(gamepads);
                            SDL_Quit();
                            return 1;
                        }


                        std::cout << "Gamepad " << id << ": " << name << '\n';
                        std::cout << "Gamepad opened successfully\n";
                        
                        // Try to press the A button on the gamepad
                        std::cout << "Press and release buttons within 10 seconds.\n";

                        const Uint64 startTime = SDL_GetTicks();

                        while(SDL_GetTicks() - startTime < 10000) {
                            const auto events = controller.pollEvents();

                            for (const auto& event : events) {
                                const char* action =
                                event.value == 1 ? "pressed" : "released";

                                std::cout << action 
                                    <<" button= " << event.code
                                    << " on device_id= " << event.device_id << '\n';
                            }
                            SDL_Delay(10); // Small delay to avoid excessive CPU usage
                        }

               
                    }
                    
                    SDL_free(gamepads);
                    SDL_Quit();
         

                    return 0;
                }
                


            } else {
                std::cerr <<  SDL_GetError() << "\n";
                SDL_Quit();

                return 1;
            }
        }

        const int unexpectedIndex = command == "list" ? optind + 1 : optind;
        std::cerr << "Unexpected argument: " << argv[unexpectedIndex] << '\n';
        return 1;
    }

    std::cout << "CoreProbe Started!\n";
    return 0;
}
