#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* pBuf;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// for EnumProcessModules
#pragma comment(lib, "psapi.lib")

void DECOMP_LOAD_RunPtrMap(char* origin, int* patchArr, int numPtrs, int dstAddr)
{
	for (int i = 0; i < numPtrs; i++)
	{
		*(int*)&origin[patchArr[i]] += dstAddr;
	}
}

struct DramPointerMap
{
	int numBytes;

	//int offsets[0];
};

#define DRAM_GETOFFSETS(x) \
	((char*)x + sizeof(struct DramPointerMap))

void wait()
{
	while (*(int*)&pBuf[(0x8000c000) & 0xffffff] != 3)
	{
		// do nothing
	}
}

void UploadToDuck(char** argv)
{
	FILE* f;
	int size;

	// tell emu to pause, cause LEV is overwritten by VRM
	*(int*)&pBuf[(0x8000c000) & 0xffffff] = 1;

	// wait 0.1s for emu to actually stop
	Sleep(100);

	f = fopen("data.vrm", "rb");

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	rewind(f);

	// read to 4mb on PS1
	fread(&pBuf[0x200000], size, 1, f);

	fclose(f);

	// tell PS1 to load VRAM
	*(int*)&pBuf[(0x8000c000) & 0xffffff] = 2;

	// wait for VRAM to finish uploading
	wait();

	// ============================================

	f = fopen("data.lev", "rb");

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	rewind(f);

	// read to 2mb on PS1
	fread(&pBuf[0x200000], size, 1, f);

	fclose(f);

	char* fileBuf = &pBuf[0x200000];
	int ptrMapOffset = *(int*)&fileBuf[0];
	char* realFileBuf = &fileBuf[4];

	struct DramPointerMap* dpm = &realFileBuf[ptrMapOffset];
	DECOMP_LOAD_RunPtrMap(
		realFileBuf,
		(int*)DRAM_GETOFFSETS(dpm),
		dpm->numBytes >> 2,
		0x80200004);

	// set level file pointer
	*(int*)&pBuf[(0x80096b20 + 0x160) & 0xffffff] = 0x80200004;

	// tell PS1 to start level
	*(int*)&pBuf[(0x8000c000) & 0xffffff] = 4;

	// ============================================
	
	printf("Here\n");
	system("pause");
	exit(0);
}

int main(int argc, char** argv)
{
	int numDuckInstances = 0;
	char* duckTemplate = "duckstation";
	int duckPID = -1;

	// copy from
	// https://learn.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);
	cProcesses = cbNeeded / sizeof(DWORD);

	for (int i = 0; i < cProcesses; i++)
	{
		DWORD processID = aProcesses[i];

		if (processID != 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

			if (NULL != hProcess)
			{
				HMODULE hMod;
				DWORD cbNeeded;

				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
				{
					TCHAR szProcessName[MAX_PATH];
					GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));

					char* procName = (char*)&szProcessName[0];

					if (
						(*(int*)&procName[0] == *(int*)&duckTemplate[0]) &&
						(*(int*)&procName[4] == *(int*)&duckTemplate[4])
						)
					{
						numDuckInstances++;
						duckPID = processID;
					}
				}
			}
		}
	}

	if (numDuckInstances == 0)
	{
		printf("Error: DuckStation is not running!\n\n");
		system("pause");
		exit(0);
	}
	else printf("Client: DuckStation detected\n");

	char pidStr[16];

	if (numDuckInstances > 1)
	{
		printf("Warning: Multiple DuckStations detected\n");
		printf("Please enter the PID manually\n\n");

		printf("Input.: DuckStation PID: ");
		scanf_s("%s", pidStr, (int)sizeof(pidStr));
	}
	else
	{
		sprintf_s(pidStr, 100, "%d", duckPID);
	}

	char duckName[100];
	sprintf_s(duckName, 100, "duckstation_%s", pidStr);

	TCHAR duckNameT[100];
	swprintf(duckNameT, 100, L"%hs", duckName);

	// 8 MB RAM
	const unsigned int size = 0x800000;
	HANDLE hFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, duckNameT);
	pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

	if (pBuf == 0)
	{
		printf("Error: Failed to open DuckStation!\n\n");
		system("pause");
		system("cls");
		main(argc, argv);
	}

	UploadToDuck(argv);
}