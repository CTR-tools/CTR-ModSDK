#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
	// 8mb RAM
	const unsigned int size = 0x800000;
	HANDLE hFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, _T("duckstation_8328")); // "duckstation_PID"
	char* pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

	printf("%d\n", *(short*)&pBuf[0x86e84]);
	*(short*)&pBuf[0x86e84] = 13;

	printf("%08x\n", *(int*)&pBuf[0x600000]);

	system("pause");
}