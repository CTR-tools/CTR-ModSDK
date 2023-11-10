#ifndef EMULATOR_FILESYSTEM_WINDOWS_H
#define EMULATOR_FILESYSTEM_WINDOWS_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"

#if defined(_WIN32) || defined(_WIN64) || defined(__APPLE__) || defined(__linux__)
extern void Emulator_OpenReadWIN(char* fileName, void* buff, int size);
extern void Emulator_OpenReadFPWIN(const char* filePath, void* buff, int size);
extern void Emulator_GetFileSizeWIN(const char* filePath, int* outSize);
extern void Emulator_ReadFileWIN(const char* filePath, void* buff, int size);
#endif

#endif
