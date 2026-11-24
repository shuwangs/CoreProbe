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
./build/coreprobe record 12 10 > recorded.jsonl
./build/coreprobe replay recorded.jsonl > replayed.jsonl
./build/coreprobe verify recorded.jsonl expected.jsonl
```

Replace `12` with the current gamepad instance ID from `list`. The second argument to `record` is the capture duration in seconds. Disconnecting the selected gamepad writes a final disconnect event and ends capture early. A recording with no input events produces an empty trace.

Replay emits events immediately in their original order, preserving their relative timestamps. For an initial round-trip check, use `recorded.jsonl` as the expected trace. For a regression test, keep a separate expected JSONL fixture. Verification compares event order, relative timestamp, device ID, type, code, and value. It returns `0` on a match, `1` on the first mismatch, and `2` on invalid arguments, input, or I/O errors.

## Run the headless tests

```sh
cmake -S . -B build-headless -DCOREPROBE_WITH_SDL=OFF
cmake --build build-headless
COREPROBE_BIN=build-headless/coreprobe python3 -m unittest discover -s tests -v
```

The tests require Python 3.11 or later. GitHub Actions runs the same scenarios on Linux. See [the architecture](doc/architecture.md) for the event format and adapter interface.
