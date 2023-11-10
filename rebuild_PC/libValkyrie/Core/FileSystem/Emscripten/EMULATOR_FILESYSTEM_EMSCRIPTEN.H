#ifndef EMULATOR_FILESYSTEM_EMSCRIPTEN_H
#define EMULATOR_FILESYSTEM_EMSCRIPTEN_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include <stdio.h>

#if defined(__EMSCRIPTEN__)
extern void Emulator_OpenReadEM(char* fileName, void* buff, int size);
extern void Emulator_OpenReadFPEM(const char* filePath, void* buff, int size);
extern void Emulator_GetFileSizeEM(const char* filePath, int* outSize);
extern void* Emulator_OpenFile(const char* filePath, const char* mode, int* outSize);
extern void Emulator_ReadFileEM(const char* filePath, void* buff, int size);
#endif

#endif