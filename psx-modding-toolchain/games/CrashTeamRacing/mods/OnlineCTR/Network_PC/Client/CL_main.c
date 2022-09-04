// To do: Make this share the header

enum State
{
	ENTER_PID,
	BOOT_GAME,
	OPEN_MENU,
	MINIMIZE
};

struct OnlineCTR
{
	// 0x10
	int NextInit;
	int PageNumber;
	int CountPressX;
	int NumDrivers;

	// 0x10
	int DriverID;
	int funcs[4];
};

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
	char pid[16];
	printf("Enter DuckStation PID: ");
	scanf_s("%s", pid, sizeof(pid));

	char duckName[100];
	sprintf_s(duckName, 100, "duckstation_%s", pid);

	TCHAR duckNameT[100];
	swprintf(duckNameT, 100, L"%hs", duckName);

	// 8mb RAM
	const unsigned int size = 0x800000;
	HANDLE hFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, duckNameT);
	char* pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

	// read/write sample
#if 0
	printf("%d\n", *(short*)&pBuf[0x86e84]);
	*(short*)&pBuf[0x86e84] = 13;

	printf("%08x\n", *(int*)&pBuf[0x600000]);
#endif

	((struct OnlineCTR*)&pBuf[0x8000C000 & 0xffffff])->NextInit = BOOT_GAME;

	system("pause");
}