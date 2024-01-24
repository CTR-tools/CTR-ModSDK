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

	printf("Type a number (1-3),\n");
	printf("then press Enter to continue.\n\n");

	printf("1: 3rd-person (normal)\n");
	printf("2: 1st-person (kart head)\n");
	printf("3: 1st-person (velocity)\n\n");

	printf("Enter Mode: ");
	scanf_s("%d", &mode, 4);
	system("cls");




	printf("Note: Use a brand new installation of DuckStation,\n");
	printf("to prevent corruption of an existing installation.\n\n");

	char duckPath[1024];
	printf("Drag DuckStation exe file into this window,\n");
	printf("then press Enter to continue.\n\n");

	printf("DuckStation exe: ");
	scanf_s("%s", &duckPath[0], 1024);
	system("cls");




	char romPath[1024];
	printf("Drag CTR modded rom into this window,\n");
	printf("then press Enter to launch in VR mode.\n\n");

	printf("CTR modded rom: ");
	scanf_s("%s", &romPath[0], 1024);
	system("cls");

	char cmdArgs[1024];
	// to-do, think of a smarter way to get exe name, without assuming 
	// duckstation-qt-x64-ReleaseLTCG.exe
	sprintf(cmdArgs, "duckstation-qt-x64-ReleaseLTCG.exe %s", &romPath[0]);


	wchar_t wName[1024];
	mbstowcs(wName, duckPath, strlen(duckPath) + 1);//Plus null
	LPWSTR ptrName = wName;

	wchar_t wRom[1024];
	mbstowcs(wRom, cmdArgs, strlen(cmdArgs) + 1);//Plus null
	LPWSTR ptrRom = wRom;

	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcess(
		ptrName,		// the path
		ptrRom,			// Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);

	int pid = pi.dwProcessId;

	if (pid == 0)
	{
		printf("Error: Failed to open DuckStation\nTry again\n");
		system("pause");
		system("cls");
		main();
	}

	char duckName[100];
	sprintf_s(duckName, 100, "duckstation_%d", pid);

	TCHAR duckNameT[100];
	swprintf(duckNameT, 100, L"%hs", duckName);

	while (pBuf == 0)
	{
		// 8mb RAM
		const unsigned int size = 0x800000;
		HANDLE hFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, duckNameT);
		pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

		Sleep(100);
	}

	printf("Do this yourself:\n\n");
	printf("- Patch the Crash Team Racing rom with the XDELTA,\n");
	printf("- Launch the modified rom in the THIS DuckStation window,\n");
	printf("- Wait for the game to boot into the Naughty Dog Box Scene,\n");
	printf("- Check this window again for next steps, they'll appear automatically\n");

	// wait for game to launch MEMPACK_Init
	while (*(unsigned int*)&pBuf[0x990e8] != 0x800ba9f0)
		Sleep(100);

	system("cls");



	ovrResult result;
	ovrInitParams initParams = { ovrInit_RequestVersion, OVR_MINOR_VERSION, NULL, 0, 0 };
	result = ovr_Initialize(&initParams);

	if (OVR_FAILURE(result))
	{
		ovrErrorInfo errorInfo;
		ovr_GetLastErrorInfo(&errorInfo);
		printf("ovr_Initialize failed: %s\n", errorInfo.ErrorString);
		system("pause");
		exit(0);
	}

	ovrSession session;
	ovrGraphicsLuid luid;
	result = ovr_Create(&session, &luid);

	while (OVR_FAILURE(result))
	{
		ovrErrorInfo errorInfo;
		ovr_GetLastErrorInfo(&errorInfo);
		printf("Ovr_Create failed: %s\n", errorInfo.ErrorString);
		printf("Please plug in your headset and enter Quest Link mode\n");
		
		Sleep(100);
		result = ovr_Create(&session, &luid);
		system("cls");
	}



	std::thread t1(startVR);
	

	float time = 0.0f;
	short backupRot[9];

	// Main loop...
	while (1)
	{
		if ((mode == 2) || (mode == 3))
		{
			// dont run during loading, cutscene, or intro-race camera
			if ((*(int*)&pBuf[0x80096b20 & 0xfffffff] & 0x60000040) == 0)
			{
				// 0xF = first-person mode 1
				// 0x10 = first-person mode 2
				*(char*)&pBuf[(0x80096b20 + 0x1498 + 0x9a) & 0xfffffff] = (mode - 2) + 0xF;
			}
		}

		// posX, posY, posZ, rotX, rotY, rotZ
		short variables[6] = {};

		// grab the position and rotation
		memcpy(variables, &pBuf[(0x80096B20 & 0xfffffff) + 0x168], sizeof(variables));

		// oculus data
		ovrTrackingState  ts = ovr_GetTrackingState(session, 0.0, ovrFalse);

		// gamepadSystem.controller[0].buttonsTapped, 
		// if you tap Select button, then reset view
		if (*(int*)&pBuf[(0x80096804 & 0xfffffff) + 0x14] & 0x2000)
		{
			ovr_SpecifyTrackingOrigin(session, ts.HeadPose.ThePose);
		}

		glm::quat q;
		q.x = -ts.HeadPose.ThePose.Orientation.x;
		q.y = ts.HeadPose.ThePose.Orientation.y;
		q.z = ts.HeadPose.ThePose.Orientation.z;
		q.w = ts.HeadPose.ThePose.Orientation.w;

		float rotY = 2.0f * 3.14159f * (float)variables[4] / 4096.0f;
		rotY = -rotY;

		glm::mat4 rotMatrix = glm::rotate(glm::mat4_cast(q), 3.14159f, glm::vec3(1, 0, 0));
		rotMatrix = glm::rotate(rotMatrix, rotY, glm::vec3(0, 1, 0));

		short rot[16];
		rot[0] = 4096.0f * rotMatrix[0][0];
		rot[1] = 4096.0f * rotMatrix[0][1];
		rot[2] = 4096.0f * rotMatrix[0][2];
		rot[3] = 4096.0f * rotMatrix[1][0];
		rot[4] = 4096.0f * rotMatrix[1][1];
		rot[5] = 4096.0f * rotMatrix[1][2];
		rot[6] = 4096.0f * rotMatrix[2][0];
		rot[7] = 4096.0f * rotMatrix[2][1];
		rot[8] = 4096.0f * rotMatrix[2][2];
		rot[9] = 0;

		float addX =
			cos(rotY) * ts.HeadPose.ThePose.Position.x +
			sin(-rotY) * ts.HeadPose.ThePose.Position.z;

		float addY = ts.HeadPose.ThePose.Position.y;

		float addZ =
			sin(rotY) * ts.HeadPose.ThePose.Position.x +
			cos(-rotY) * ts.HeadPose.ThePose.Position.z;

		*(int*)&rot[10] = (int)(addX * 512.0f);
		*(int*)&rot[12] = (int)(addY * 512.0f);
		*(int*)&rot[14] = (int)(addZ * 512.0f);

		memcpy(&pBuf[(0x8000c000 & 0xfffffff)], &rot[0], sizeof(short) * 16);

		// 8ms = 240 updates per second
		Sleep(4);
	}

	return 0;
}