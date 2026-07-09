# OnlineCTR Network_PC - Linux Port

This folder contains the Client and Server applications for OnlineCTR, which originally were developed strictly for Windows using Windows-specific APIs (`windows.h`, `psapi.lib`, `EnumProcessModules`, etc.).

This repository has been ported to support **Linux natively** via CMake and POSIX APIs.

## What was changed

1. **Process Detection**: The original code used Win32 `EnumProcesses` to find the DuckStation emulator. In Linux, it now parses the `/proc/` filesystem to look for the emulator by checking `comm` and `cmdline` to properly support native DuckStation installations and AppImages.
2. **Shared Memory Mapping**: The emulator memory is read/written to sync data. Replaced `MapViewOfFile` with POSIX `shm_open` and `mmap` to read the shared memory space `duckstation_<PID>` exported by DuckStation.
3. **Cross-Platform Compatibility**: Replaced Windows-only functions with portable macros or implementations:
   - `strcpy_s` -> `STRCPY_SAFE`
   - `sprintf_s` -> `SPRINTF_SAFE`
   - `system("cls")` -> `system("clear")`
   - Custom `Sleep`/`usleep` wrappers
   - Proper `_Static_assert` mapping for C++ compilers (`g++`/`clang++`).
4. **Build System**: Added `CMakeLists.txt` for the Client and updated the Server's `CMakeLists.txt` to compile ENet directly from the submodules, preventing linker errors from missing pre-compiled ENet libraries.

## How to build on Linux

Make sure you have `cmake`, `make` (or `ninja`), and a C/C++ compiler installed (`gcc`/`g++`).
Also ensure that the ENet submodule is populated (`git submodule update --init --recursive`).

### Compiling the Client

```bash
cd mods/Windows/OnlineCTR/Network_PC/Client
mkdir build && cd build
cmake ..
cmake --build .
```
This will produce the executable `ctr_client`.

### Compiling the Server

```bash
cd mods/Windows/OnlineCTR/Network_PC/Server
mkdir build && cd build
cmake ..
cmake --build .
```
This will produce the executable `ctr_srv`.

## Running the Client

1. Open DuckStation and ensure **Enable Shared Memory** (PINE) is checked in the Advanced or Developer settings. Also make sure the **8MB RAM** (Console RAM Size) option is enabled!
2. Launch your patched Crash Team Racing game.
3. Open a terminal and run the Client:
   ```bash
   ./ctr_client <YourUsername>
   ```
4. If it detects multiple DuckStation instances (e.g., when running an AppImage), it will ask for the PID. Look at the DuckStation console logs to find the exact Shared Memory PID, and enter it.
5. Select a server (or run your own `ctr_srv` locally and choose "Private Server" with IP `127.0.0.1`).
