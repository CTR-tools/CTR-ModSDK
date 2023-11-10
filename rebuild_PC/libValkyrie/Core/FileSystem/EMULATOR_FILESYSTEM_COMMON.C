#include "EMULATOR_FILESYSTEM_COMMON.H"

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

#include <stdio.h>

#if defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#endif

#if !defined(NO_FILESYSTEM)

char currentLoadingFile[128];

void Emulator_OpenRead(char* fileName, void* buff, int size)
{
#if defined(__EMSCRIPTEN__)

	if (strcmp(currentLoadingFile, fileName))
	{
		strcpy(currentLoadingFile, fileName);
		Emulator_OpenReadEM(fileName, buff, size);
	}
#elif defined(_WIN32) || defined(_WIN64) || defined(__APPLE__) || defined(__linux__)
    
#if defined(__APPLE__) || defined(__linux__)
    char newFilePath[256];
    char* pFilePath = &newFilePath[0];
    getcwd(newFilePath, sizeof(newFilePath));
    strcat(newFilePath, "/");
    strcat(newFilePath, fileName);
    if (strcmp(currentLoadingFile, fileName))
    {
        strcpy(currentLoadingFile, fileName);
        while(*pFilePath++)
        {
            if(*pFilePath == '\\')
            {
                *pFilePath = '/';
            }
        }
        Emulator_OpenReadWIN(newFilePath, buff, size);
    }
#else
    if (strcmp(currentLoadingFile, fileName))
    {
        strcpy(currentLoadingFile, fileName);
        Emulator_OpenReadWIN(fileName, buff, size);
    }
#endif
#endif
}

void Emulator_OpenReadFP(const char* filePath, void* buff, int size)
{
#if defined(__EMSCRIPTEN__)
	Emulator_OpenReadFPEM(filePath, buff, size);
#elif defined(_WIN32) || defined(_WIN64) || defined(__APPLE__) || defined(__linux__)
    
#if defined(__APPLE__) || defined(__linux__)
    char newFilePath[256];
    char* pFilePath = &newFilePath[0];
    getcwd(newFilePath, sizeof(newFilePath));
    strcat(newFilePath, "/");
    strcat(newFilePath, filePath);
    while(*pFilePath++)
    {
        if(*pFilePath == '\\')
        {
            *pFilePath = '/';
        }
    }
    Emulator_OpenReadFPWIN(newFilePath, buff, size);
#else
    Emulator_OpenReadFPWIN(filePath, buff, size);
#endif
#endif
}

void Emulator_ReadFile(const char* filePath, void* buff, int size)
{
#if defined(__EMSCRIPTEN__)
	Emulator_ReadFileEM(filePath, buff, size);
#elif defined(_WIN32) || defined(_WIN64) || defined(__APPLE__) || defined(__linux__)

#if defined(__APPLE__) || defined(__linux__)
    char newFilePath[256];
    char* pFilePath = &newFilePath[0];
    getcwd(newFilePath, sizeof(newFilePath));
    strcat(newFilePath, "/");
    strcat(newFilePath, filePath);
    while(*pFilePath++)
    {
        if(*pFilePath == '\\')
        {
            *pFilePath = '/';
        }
    }
    Emulator_ReadFileWIN(newFilePath, buff, size);
#else
    Emulator_ReadFileWIN(filePath, buff, size);
#endif
	
#endif
}

void Emulator_GetFileSize(const char* filePath, int* outSize)
{
#if defined(__EMSCRIPTEN__)
	Emulator_GetFileSizeEM(filePath, outSize);
#elif defined(_WIN32) || defined(_WIN64) || defined(__APPLE__) || defined(__linux__)
#if defined(__APPLE__) || defined(__linux__)
    char newFilePath[256];
    char* pFilePath = &newFilePath[0];
    getcwd(newFilePath, sizeof(newFilePath));
    strcat(newFilePath, "/");
    strcat(newFilePath, filePath);
    printf("%s\n", newFilePath);
    
    while(*pFilePath++)
    {
        if(*pFilePath == '\\')
        {
            *pFilePath = '/';
        }
    }
    Emulator_GetFileSizeWIN(newFilePath, outSize);
#else
    Emulator_GetFileSizeWIN(filePath, outSize);
#endif
	
#endif
}

#endif
