# CoreProbe v0.1

CoreProbe is a C++20 headless framework for device input capture and automated testing. Its first hardware target is a gamepad such as the Nintendo Switch Pro Controller.

## Build on macOS

```sh
brew install cmake sdl3
cmake -S . -B build
cmake --build build
```

If CMake cannot find SDL3, pass `-DSDL3_ROOT="$(brew --prefix sdl3)"` at configuration time.

## Record → Replay → Verify

```sh
./build/coreprobe list
```

