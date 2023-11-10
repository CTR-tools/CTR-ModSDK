# Psy-Cross (Psy-X)
![](https://i.ibb.co/PFNnw4G/PsyCross.jpg)

Compatibility framework for building and running Psy-Q SDK - based Playstation games across other platforms

### Implementation details
- High-level *Playstation API* reimplementation which translates it's calls into modern/compatible APIs
- Psy-Q - compatible headers
- Implements Geometry Transformation Engine (GTE) in software and adapts it's macros and calls
- Optimized Precise GTE Vertex Cache with *modern 3D hardware perspective transform* and *Z-buffer* support (PGXP-Z)
- *LibSPU* with ADPCM decoding on OpenAL (SPU-AL)
- *LibGPU* with Playstation-style polygon and image handling
- *LibCD* with ISO 9660 BIN/CUE image support by Playstation CD API
- Already proven to be *95% compatible* with the Psy-Q Playstation SDK - Psy-X game look almost identical to the Playstation game
- You can bring your game to *Web with Emscripten* support

### Folder structure
- `src/gpu`: PSX GPU linked lists and polygon handling routines
- `src/gte`: PSX GTE and PGXP-Z implementation
- `src/render`: OpenGL renderer and PSX VRAM emulation
- `src/pad`: Controller handling
- `src/psx`: Implementations of PsyQ - compatible libraries (**libgte, libgpu, libspu, libcd ...**)
- `include/psx`: Headers of PsyQ - compatible libraries (**libgte, libgpu, libspu, libcd ...**)
- `include/PsyX`: PsyCross interfaces (**window management, configuration, renderer, PGXP-Z**)

### Dependencies
- OpenAL-soft (1.21.x or newer)
- SDL2 (2.0.16 or newer)

## TODO
- CMake dependency/build scripts
- Add some missing **LibGTE** functions
- MDEC implementation in **LibPress**
- CD Audio/XA decoding and playback
- SPU Attack-Decay-Sustain-Release (ADSR) support, *maybe through own mixer?*

### Credits
- SoapyMan - more GTE functions, SPU-AL, PGXP-Z
- Gh0stBlade - original source/base [(link)](https://github.com/TOMB5/TOMB5/tree/master/EMULATOR)
