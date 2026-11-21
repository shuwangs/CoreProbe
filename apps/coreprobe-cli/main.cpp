#include <getopt.h>
#include <iostream>
#include <string>

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
            return 0;
        }

        const int unexpectedIndex = command == "list" ? optind + 1 : optind;
        std::cerr << "Unexpected argument: " << argv[unexpectedIndex] << '\n';
        return 1;
    }

    std::cout << "CoreProbe Started!\n";
    return 0;
}
