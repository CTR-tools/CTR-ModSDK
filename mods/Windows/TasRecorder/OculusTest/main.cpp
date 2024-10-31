#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>

#include <stdio.h>
#include <math.h>
#include <OVR_CAPI.h>

#include <thread>

void startVR()
{
	system("vr-screen-cap-CTR.exe");
}

int main()
{
	char* pBuf = 0;
	int mode = 0;

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 480, 240 + 35, TRUE);

	int pid;
	printf("Enter DuckStation PID: ");
	scanf("%d", &pid);

	char duckName[100];
	sprintf_s(duckName, 100, "duckstation_%d", pid);

	TCHAR duckNameT[100];
	swprintf(duckNameT, 100, L"%hs", duckName);

	// 8mb RAM
	const unsigned int size = 0x800000;
	HANDLE hFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, duckNameT);
	pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

	if (pBuf == 0)
	{
		printf("Failed to open\n");
		system("pause");
		exit(0);
	}

	system("cls");
	printf("1 - Save\n");
	printf("2 - Load\n");
	printf("Enter: ");

	scanf("%d", &pid);

	// SAVE mode
	if (pid == 1)
	{
		system("cls");
		printf("Saving...\n");

		int sizeInt = *(int*)&pBuf[0xfff0];
		FILE* fp = fopen("NewTAS.bin", "wb+");
		fwrite(&pBuf[0x200000], 1, sizeInt * 4, fp);
		fclose(fp);

		printf("Saved as NewTAS.bin, you may rename the file\n");
	}

	else
	{
		system("cls");
		printf("Enter File Name: ");

		char name[100];
		scanf("%s", &name[0]);

		FILE* fp;

		fp = fopen(name, "rb");
		fseek(fp, 0L, SEEK_END);
		int sizeByte = ftell(fp);
		fclose(fp);

		fp = fopen(name, "rb");
		fread(&pBuf[0x200000], 1, sizeByte, fp);
		fclose(fp);

		*(int*)&pBuf[0xfff4] = 1;

		printf("Loaded %s, Replay Activated\n");
	}

	system("pause");
	exit(0);
	return 0;
}