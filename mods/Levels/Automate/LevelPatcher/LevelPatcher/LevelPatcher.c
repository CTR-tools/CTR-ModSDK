#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <Windows.h>

void SetBlockIDs(char* quadBlockArr, int quadBlockCount)
{
	// Set BlockIDs
	for (int i = 0; i < quadBlockCount; i++)
	{
		int id = (i & 0xFFE0) + 0x1F - (i & 0x1f);
		*(short*)&quadBlockArr[0x5C * i + 0x3C] = id;
		//if ((i & 0x1f) == 0) printf("\n");
		//printf("%d ", id);
	}
}

struct BoundingBox
{
	short min[3];
	short max[3];
};

void SetBspBoxes(char* levelPtr, char* quadBlockArr, char* bspArr, char* bspCurr)
{
	// not a leaf node
	if ((*(short*)&bspCurr[0] & 1) == 0)
	{
		SetBspBoxes(
			levelPtr, quadBlockArr, bspArr,
			&bspArr[(*(short*)&bspCurr[0x18] & 0x3fff) * 0x20]
		);

		SetBspBoxes(
			levelPtr, quadBlockArr, bspArr,
			&bspArr[(*(short*)&bspCurr[0x1A] & 0x3fff) * 0x20]
		);

		// if child
		if ((*(short*)&bspArr[(*(short*)&bspCurr[0x18] & 0x3fff) * 0x20] & 1) != 0)
		{
			// tag child
			*(short*)&bspCurr[0x18] |= 0x4000;
		}

		// if child
		if ((*(short*)&bspArr[(*(short*)&bspCurr[0x1A] & 0x3fff) * 0x20] & 1) != 0)
		{
			// tag child
			*(short*)&bspCurr[0x1A] |= 0x4000;
		}

		struct BoundingBox* bspBox;
		bspBox = &bspCurr[4];
		bspBox->min[0] = 0x7FFF;
		bspBox->min[1] = 0x7FFF;
		bspBox->min[2] = 0x7FFF;
		bspBox->max[0] = -0x7FFF;
		bspBox->max[1] = -0x7FFF;
		bspBox->max[2] = -0x7FFF;

		struct BoundingBox* bspBoxKid;
		bspBoxKid = &bspArr[(*(short*)&bspCurr[0x18] & 0x3fff) * 0x20 + 4];
		for (int j = 0; j < 3; j++)
		{
			if (bspBoxKid->min[j] < bspBox->min[j]) bspBox->min[j] = bspBoxKid->min[j];
			if (bspBoxKid->max[j] > bspBox->max[j]) bspBox->max[j] = bspBoxKid->max[j];
		}
		bspBoxKid = &bspArr[(*(short*)&bspCurr[0x1A] & 0x3fff) * 0x20 + 4];
		for (int j = 0; j < 3; j++)
		{
			if (bspBoxKid->min[j] < bspBox->min[j]) bspBox->min[j] = bspBoxKid->min[j];
			if (bspBoxKid->max[j] > bspBox->max[j]) bspBox->max[j] = bspBoxKid->max[j];
		}
	}

	// if a leaf node
	else
	{
		int numBlock = *(int*)&bspCurr[0x18];
		char* newBlockArr = &levelPtr[*(int*)&bspCurr[0x1C]];

		struct BoundingBox* bspBox;
		bspBox = &bspCurr[4];
		bspBox->min[0] = 0x7FFF;
		bspBox->min[1] = 0x7FFF;
		bspBox->min[2] = 0x7FFF;
		bspBox->max[0] = -0x7FFF;
		bspBox->max[1] = -0x7FFF;
		bspBox->max[2] = -0x7FFF;

		struct BoundingBox* qbBox;
		for (int i = 0; i < numBlock; i++)
		{
			qbBox = &newBlockArr[0x5c * i + 0x2c];

			for (int j = 0; j < 3; j++)
			{
				if (qbBox->min[j] < bspBox->min[j]) bspBox->min[j] = qbBox->min[j];
				if (qbBox->max[j] > bspBox->max[j]) bspBox->max[j] = qbBox->max[j];
			}
		}
	}
}

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

	char* ptrMap = &levelPtr[*(int*)&fileBuf[0]];

	int ptr_Count = *(int*)&ptrMap[0] >> 2;
	int* ptr_Arr = &ptrMap[4];

	char* meshInfo;
	char* quadBlockArr;
	char* bspArr;

	int quadBlockCount, bspCount;

	meshInfo = &levelPtr[*(int*)&levelPtr[0]];
	quadBlockArr = &levelPtr[*(int*)&meshInfo[0xC]];
	quadBlockCount = *(int*)&meshInfo[0];
	bspArr = &levelPtr[*(int*)&meshInfo[0x18]];
	bspCount = *(int*)&meshInfo[0x1C];

	// level->0x0
	int offsetPtrMeshInfo = *(int*)&levelPtr[0];
	if (offsetPtrMeshInfo != 0)
	{
		*(int*)&ptr_Arr[ptr_Count++] = (int)&levelPtr[0] - (int)levelPtr;
		sz += 1 * 4;

		// meshInfo->0xC
		int offsetPtrQuadblock = *(int*)&meshInfo[0xC];
		if (offsetPtrQuadblock != 0)
		{
			*(int*)&ptr_Arr[ptr_Count++] = (int)&meshInfo[0xC] - (int)levelPtr;
			sz += 1 * 4;
		}

		// meshInfo->0x10
		int offsetPtrVertex = *(int*)&meshInfo[0x10];
		if (offsetPtrVertex != 0)
		{
			*(int*)&ptr_Arr[ptr_Count++] = (int)&meshInfo[0x10] - (int)levelPtr;
			sz += 1 * 4;
		}

		// meshInfo->0x18
		int offsetPtrBSP = *(int*)&meshInfo[0x18];
		if (offsetPtrBSP != 0)
		{
			// patch BSP
			*(int*)&ptr_Arr[ptr_Count++] = (int)&meshInfo[0x18] - (int)levelPtr;
			sz += 1 * 4;

			// patch BSP leaf nodes
			for (int i = 0; i < bspCount; i++)
			{
				char* newBspArr = &bspArr[0x20 * i];

				// skip if not a leaf node
				if ((*(short*)&newBspArr[0] & 1) == 0)
					continue;

				// patch leaf node
				*(int*)&ptr_Arr[ptr_Count++] = (int)&newBspArr[0x1c] - (int)levelPtr;
				sz += 1 * 4;
			}
		}
	}

	// level->0x4
	int offsetPtrSkybox = *(int*)&levelPtr[4];
	if (offsetPtrSkybox != 0)
	{
		*(int*)&ptr_Arr[ptr_Count++] = (int)&levelPtr[4] - (int)levelPtr;
		sz += 1 * 4;
	}

	// level->0x8
	int offsetPtrAnimTex = *(int*)&levelPtr[8];
	if (offsetPtrAnimTex != 0)
	{
		*(int*)&ptr_Arr[ptr_Count++] = (int)&levelPtr[8] - (int)levelPtr;
		sz += 1 * 4;

		char* animTex = &levelPtr[*(int*)&levelPtr[8]];

		// null terminator is a pointer back to the start,
		// do NOT forget to put that in the level
		while(*(int*)animTex != *(int*)&levelPtr[8])
		{
			*(int*)&ptr_Arr[ptr_Count++] = (int)&animTex[0] - (int)levelPtr;
			sz += 1 * 4;

			short numFrames = *(short*)&animTex[4];
			
			// animTex header is 0xC bytes large, before ptrArray
			animTex += 0xC;

			for (int i = 0; i < numFrames; i++)
			{
				*(int*)&ptr_Arr[ptr_Count++] = (int)&animTex[0] - (int)levelPtr;
				sz += 1 * 4;
				animTex += 4;
			}
		}

		// patch null terminator
		*(int*)&ptr_Arr[ptr_Count++] = (int)&animTex[0] - (int)levelPtr;
		sz += 1 * 4;
	}

	// level->0x134
	int offsetPtrSpawn1 = *(int*)&levelPtr[0x134];
	if (offsetPtrSpawn1 != 0)
	{
		*(int*)&ptr_Arr[ptr_Count++] = (int)&levelPtr[0x134] - (int)levelPtr;
		sz += 1 * 4;
	}

	// level->0x14c
	int offsetPtrCheckpoint = *(int*)&levelPtr[0x14c];
	if (offsetPtrCheckpoint != 0)
	{
		*(int*)&ptr_Arr[ptr_Count++] = (int)&levelPtr[0x14c] - (int)levelPtr;
		sz += 1 * 4;
	}

	// level->0x188
	int offsetPtrNavTable = *(int*)&levelPtr[0x188];
	if (offsetPtrNavTable != 0)
	{
		*(int*)&ptr_Arr[ptr_Count++] = (int)&levelPtr[0x188] - (int)levelPtr;
		sz += 1 * 4;

		// NavTable: Array of 3 NavHeader pointers
		char* NavTable = &levelPtr[*(int*)&levelPtr[0x188]];
		for (int i = 0; i < 3; i++)
		{
			// If NavHeader is valid
			int offsetPtrNav = *(int*)&NavTable[4*i];
			if (offsetPtrNav != 0)
			{
				// Patch NavHeader
				*(int*)&ptr_Arr[ptr_Count++] = (int)&NavTable[4 * i] - (int)levelPtr;
				sz += 1 * 4;

				char* NavHeader = &levelPtr[*(int*)&NavTable[4 * i]];

				// Patch NavHeader->last
				int offsetNavFrameLast = *(int*)&NavHeader[8];
				if (offsetNavFrameLast != 0)
				{
					*(int*)&ptr_Arr[ptr_Count++] = (int)&NavHeader[8] - (int)levelPtr;
					sz += 1 * 4;
				}
			}
		}
	}

	// level->0x190
	int offsetPtrVisMem = *(int*)&levelPtr[0x190];
	if (offsetPtrVisMem != 0)
	{
		*(int*)&ptr_Arr[ptr_Count++] = (int)&levelPtr[0x190] - (int)levelPtr;
		sz += 1 * 4;
	}

	// skip level->0x10, 0x18, 0x24, 0x38, 0x3c, 0x40, 0x44, 
	// 0xD4, 0xE0, 0xE4, 0xE8, 0x13C, 0x144, 
	
	SetBlockIDs(quadBlockArr, quadBlockCount);
	SetBspBoxes(levelPtr, quadBlockArr, bspArr, bspArr);
	
	for (int i = 0; i < quadBlockCount; i++)
	{
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x1c] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x20] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x24] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x28] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x40] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x44] - (int)levelPtr;
	
		// increase file size
		sz += 6 * 4;
	}

	// Finalize
	*(int*)&ptrMap[0] = ptr_Count << 2;
	printf("%d\n", ptr_Count);

	// === #if 0 for testing ===
#if 1
	f = fopen(argv[1], "wb");
	fwrite(fileBuf, sz, 1, f);
	fclose(f);
#endif
	printf("Level Patched! Exiting Patcher\n\n");
}