#include <getopt.h>
#include <iostream>
#include <string>

#include <SDL3/SDL_version.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_gamepad.h>


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

                if(gamepads != NULL) {
                    std::cout << "Detected " << padCount << " joysticks. \n";
                    for (int i = 0; i < padCount; i++) {
                        SDL_JoystickID id = gamepads[i];
                        std::cout << "current joystick id is " << id << "\n";
                    }

                    SDL_free(gamepads);
                }

                return 0;
            } else {
                std::cerr <<  SDL_GetError() << "\n";

                return 1;
            }
        }

        const int unexpectedIndex = command == "list" ? optind + 1 : optind;
        std::cerr << "Unexpected argument: " << argv[unexpectedIndex] << '\n';

    }

    std::cout << "CoreProbe Started!\n";
    return 0;
}
