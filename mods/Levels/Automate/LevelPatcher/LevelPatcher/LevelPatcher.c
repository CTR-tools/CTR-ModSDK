#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <Windows.h>

int main(int argc, char** argv)
{
	printf("\n\nLevelPatcher: Starting!\n");

	if (argc != 2)
	{
		printf("Error!\nNo .lev passed as argument\n\n");
		return;
	}

	// 2mb
	char* fileBuf = malloc(1024 * 1024 * 2);
	printf("Opening: %s\n", argv[1]);
	FILE* f = fopen(argv[1], "rb");
	if (!f)
	{
		printf("Error!\nFile not found\n\n");
		return;
	}

	fseek(f, 0L, SEEK_END);
	int sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	fread(fileBuf, sz, 1, f);
	fclose(f);

	char* levelPtr = &fileBuf[4];

	// level->configFlags (0xDC)
	// does not use the flag & 0x80 in-game
	if ((*(int*)&levelPtr[0xDC] & 0x80) == 0)
	{
		printf("Level Unpatched, now patching...\n");
		*(int*)&levelPtr[0xDC] |= 0x80;
	}

	else
	{
		printf("Error!\nThe .lev is already patched\nBuild a new one from build.bat\n\n");
		return;
	}

	f = fopen(argv[1], "wb");
	fwrite(fileBuf, sz, 1, f);
	fclose(f);

	printf("Level Patched! Exiting Patcher\n\n");
}