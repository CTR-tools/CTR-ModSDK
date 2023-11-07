#include "EMULATOR_FILESYSTEM_WINDOWS.H"

#include "Core/Setup/Game/GAME_VERSION.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

#include <stdio.h>

#if defined(_DEBUG) && !defined(NO_FILESYSTEM)

void Emulator_ReadFileWIN(const char* filePath, void* buff, int size)
{
	FILE* f = fopen(filePath, "rb");
	
	if (f != NULL)
	{
		fread(buff, size, 1, f);
		fclose(f);
	}
    else
    {
        printf("Failed to open file: %s\n", filePath);
    }
}

void Emulator_OpenReadWIN(char* fileName, void* buff, int size)
{
	if (size == -1)
	{
		Emulator_GetFileSizeWIN(fileName, &size);
	}

	Emulator_ReadFileWIN(fileName, buff, size);
}

void Emulator_OpenReadFPWIN(const char* filePath, void* buff, int size)
{
	Emulator_ReadFileWIN(filePath, buff, size);
}

void Emulator_GetFileSizeWIN(const char* filePath, int* outSize)
{
	FILE* f = fopen(filePath, "rb");

	if (f != NULL)
	{
		fseek(f, 0, SEEK_END);
		outSize[0] = ftell(f);
		fclose(f);
	}
    else
    {
        printf("Failed to open file: %s\n", filePath);
    }
}

#endif
