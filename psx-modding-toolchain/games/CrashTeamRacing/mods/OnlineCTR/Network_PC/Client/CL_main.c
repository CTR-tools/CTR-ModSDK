#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#define WINDOWS_INCLUDE
#include "../../Network_PS1/src/global.h"

char* pBuf;
struct OnlineCTR* octr;

void ClientState_EnterPID()
{
	// allow game to pass the prompt screen
	octr->CurrState = BOOT_GAME;
}

void ClientState_BootGame()
{
	// do nothing, this lasts one frame on PS1-side
}

void ClientState_Navigate()
{
	// do nothing, this is when track and car are selected
}

void ClientState_Minimize()
{
	// this is gameplay, should send and recv position
}

void (*ClientState[]) () =
{
	ClientState_EnterPID,
	ClientState_BootGame,
	ClientState_Navigate,
	ClientState_Minimize
};

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
	pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

	if (pBuf == 0)
	{
		printf("Error\n");
		system("pause");
		return;
	}

	system("cls");
	printf("Connected to Client\n");

	octr = (struct OnlineCTR*)&pBuf[0x8000C000 & 0xffffff];

	while (1)
	{
		ClientState[octr->CurrState]();
	}

	system("pause");
}