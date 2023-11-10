#include "Core/EMULATOR.H"
#include "LIBSN.H"
#include <stdio.h>

FILE* fileHandle = 0;

#define INVALID_FILE_HANDLE (-1)

int PCinit()
{
	//UNIMPLEMENTED();
	return 0;
}

FILE* PCopen(char* name, int flags, int perms)
{
	//TOMB5 hack for CUTSEQ.JIZ
	if (name[0] == '\\')
	{
		++name;
	}

#if defined(__ANDROID__)
	char buff[64];
	sprintf(&buff[0], "/storage/self/primary/%s/%s", GAME_SHORT_NAME, name);
	name = &buff[0];
#elif defined(_XBOX)
	char buff[64];
	sprintf(&buff[0], "game:/%s", name);
	name = &buff[0];
#endif

	switch (flags)
	{
	case 0:
		fileHandle = (FILE*)fopen(name, "rb");
		break;
	case 1:
		fileHandle = (FILE*)fopen(name, "wb");
		break;
	case 2:
		fileHandle = (FILE*)fopen(name, "rwb");
		break;
	}

	return fileHandle == 0 ? (FILE*)INVALID_FILE_HANDLE : fileHandle;
}

int PCcreat(char* name, int perms)
{
	//UNIMPLEMENTED();
	return 0;
}

int PClseek(FILE* fd, int offset, int mode)
{
	fseek(fd, offset, mode);
	return ftell(fd);
}

int PCread(FILE* fd, char* buff, int len)
{
 	return fread(buff, len, 1, fd);
}

int PCwrite(FILE* fd, char* buff, int len)
{
	return fwrite(buff, len, 1, fd);
}

int PCclose(FILE* fd)
{
	return fclose(fd);
}