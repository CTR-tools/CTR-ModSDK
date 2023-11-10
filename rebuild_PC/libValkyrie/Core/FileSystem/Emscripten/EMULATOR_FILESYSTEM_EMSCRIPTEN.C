#include "EMULATOR_FILESYSTEM_EMSCRIPTEN.H"

#include "Core/Setup/Game/GAME_VERSION.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

#include <stdio.h>

#define DEMO

#if defined(DEMO)
#define BUILD_PATH "DEMO"
#else
#define BUILD_PATH "REVIEW"
#endif

#if defined(__EMSCRIPTEN__)

#include <emscripten.h>

void Emulator_ReadFileEM(const char* filePath, void* buff, int size)
{
	int fileExists = 0;
	int err = 0;
	void* outBuff = NULL;
	int outSize;

	emscripten_idb_exists(SHORT_GAME_NAME, filePath, &fileExists, &err);

	if (err != 0)
	{
		printf("Failed to open file indexed db %s! Err: %d Exists: %d\n", filePath, err, fileExists);
	}

	if (fileExists && err == 0)
	{
		emscripten_idb_load(SHORT_GAME_NAME, filePath, &outBuff, &outSize, &err);

		if (err != 0)
		{
			printf("Failed to open file indexed db %s!\n", filePath);
			return;
		}

		if (outBuff != NULL)
		{
			memcpy(buff, outBuff, outSize);
		}
	}
	else
	{
		const char* urlName = "https://legacyofkain.co.uk/";
		char fullName[256];
		int err = 0;

		sprintf(fullName, "%s/%s/%s/%s", urlName, SHORT_GAME_NAME, BUILD_PATH, filePath);

		emscripten_wget_data(fullName, &outBuff, &outSize, &err);

		if (err != 0)
		{
			printf("Failed to open file wget %s!\n", filePath);
			return;
		}

		err = 0;

		emscripten_idb_store(SHORT_GAME_NAME, filePath, outBuff, outSize, &err);

		if (err != 0)
		{
			printf("Failed to store file indexed db %s!\n", filePath);

			return;
		}

		if (outBuff != NULL)
		{
			memcpy(buff, outBuff, outSize);
		}
	}
}

void Emulator_OpenReadEM(char* fileName, void* buff, int size)
{
	Emulator_ReadFileEM(fileName, buff, size);
}

void Emulator_OpenReadFPEM(const char* filePath, void* buff, int size)
{
	Emulator_ReadFileEM(filePath, buff, size);
}

void* Emulator_OpenFile(const char* filePath, const char* mode, int* outSize)
{
	int fileExists = 0;
	int err = 0;
	void* outBuff = NULL;

	emscripten_idb_exists(SHORT_GAME_NAME, filePath, &fileExists, &err);

	if (err != 0)
	{
		printf("Failed to open file indexed db %s! Err:%d Exists: %d\n", filePath, err, fileExists);
	}

	if (fileExists && err == 0)
	{
		emscripten_idb_load(SHORT_GAME_NAME, filePath, &outBuff, outSize, &err);
		
		if (err != 0)
		{
			printf("Failed to open file indexed db %s!\n", filePath);
			return NULL;
		}
	}
	else
	{
		const char* urlName = "https://legacyofkain.co.uk/";
		char fullName[256];
		int err = 0;

		sprintf(fullName, "%s/%s/%s/%s", urlName, SHORT_GAME_NAME, BUILD_PATH, filePath);

		emscripten_wget_data(fullName, &outBuff, outSize, &err);

		if (err != 0)
		{
			printf("Failed to open file wget %s!\n", filePath);
			return NULL;
		}

		err = 0;

		emscripten_idb_store(SHORT_GAME_NAME, filePath, outBuff, *outSize, &err);

		if (err != 0)
		{
			printf("Failed to store file indexed db %s!\n", filePath);

			return NULL;
		}
	}

	return outBuff;
}


void Emulator_GetFileSizeEM(const char* filePath, int* outSize)
{
	void* outBuff = Emulator_OpenFile(filePath, "rb", outSize);
}

#endif