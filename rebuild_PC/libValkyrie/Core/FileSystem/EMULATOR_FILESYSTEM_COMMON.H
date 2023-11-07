#ifndef EMULATOR_FILESYSTEM_COMMON_H
#define EMULATOR_FILESYSTEM_COMMON_H


#if defined(_WIN32) || defined(_WIN64) || defined(__APPLE__) || defined(__linux__)
#include "Core/FileSystem/Windows/EMULATOR_FILESYSTEM_WINDOWS.H"
#elif defined(__EMSCRIPTEN__)
#include "Core/FileSystem/Emscripten/EMULATOR_FILESYSTEM_EMSCRIPTEN.H"
#endif

#if !defined(NO_FILESYSTEM)
extern void Emulator_OpenRead(char* fileName, void* buff);
extern void Emulator_OpenReadFP(const char* filePath, void* buff, int size);
extern void Emulator_GetFileSize(const char* filePath, int* outSize);
#endif

#endif
