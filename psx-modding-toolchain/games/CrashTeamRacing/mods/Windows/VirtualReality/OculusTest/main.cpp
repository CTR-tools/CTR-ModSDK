
#include <windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>

char* pBuf;

void initializeEmu()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 480, 240 + 35, TRUE);

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
}

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <math.h>
#include <OVR_CAPI.h>

int main()
{
	initializeEmu();

	if (pBuf == 0)
	{
		printf("Error: Failed to open DuckStation\nTry again\n");
		system("pause");
		system("cls");
		main();
	}

	ovrResult result;

	ovrInitParams initParams = { ovrInit_RequestVersion, OVR_MINOR_VERSION, NULL, 0, 0 };
	result = ovr_Initialize(&initParams);

	if (OVR_FAILURE(result))
	{
		ovrErrorInfo errorInfo;
		ovr_GetLastErrorInfo(&errorInfo);
		printf("ovr_Initialize failed: %s\n", errorInfo.ErrorString);
		system("pause");
	}

	ovrSession session;
	ovrGraphicsLuid luid;
	result = ovr_Create(&session, &luid);

	if (OVR_FAILURE(result))
	{
		ovrErrorInfo errorInfo;
		ovr_GetLastErrorInfo(&errorInfo);
		printf("ovr_Create failed: %s\n", errorInfo.ErrorString);
		system("pause");
	}

	system("cls");

	float time = 0.0f;

	short backupRot[9];

	// Main loop...
	while (1)
	{
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

		short rot[9];
		rot[0] = 4096.0f * rotMatrix[0][0];
		rot[1] = 4096.0f * rotMatrix[0][1];
		rot[2] = 4096.0f * rotMatrix[0][2];
		rot[3] = 4096.0f * rotMatrix[1][0];
		rot[4] = 4096.0f * rotMatrix[1][1];
		rot[5] = 4096.0f * rotMatrix[1][2];
		rot[6] = 4096.0f * rotMatrix[2][0];
		rot[7] = 4096.0f * rotMatrix[2][1];
		rot[8] = 4096.0f * rotMatrix[2][2];

		// to make this work
		// patch 80042c14 = li s1, 8000c000
		// dont waste time with build list,
		// just open your game (modded or OG) with hex editors,
		// search 80 1f 11 3c d4 03 31 36
		// replace 00 80 11 3c 00 c0 31 36

		memcpy(&pBuf[(0x8000c000 & 0xfffffff)], &rot[0], sizeof(short) * 9);

		// 8ms = 240 updates per second
		Sleep(4);
	}

	return 0;
}