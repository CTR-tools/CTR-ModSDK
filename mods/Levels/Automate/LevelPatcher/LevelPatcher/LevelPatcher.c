#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <math.h>
#include <Windows.h>

#define SHIFT_HARD 8

char GetTriSize(char* quadBlcokArr, char* vertexArr, int id, int n1, int n2, int n3)
{
	// ======== Copy ================

	int vect_A[3];
	int vect_B[3];
	int cross_P[3];

	char* quadBlock = &quadBlcokArr[0x5C * id];
	char* vertN1 = &vertexArr[*(short*)&quadBlock[2 * n1] * 0x10];
	char* vertN2 = &vertexArr[*(short*)&quadBlock[2 * n2] * 0x10];
	char* vertN3 = &vertexArr[*(short*)&quadBlock[2 * n3] * 0x10];

	for (int j = 0; j < 3; j++)
	{
		vect_A[j] = *(short*)&vertN1[2 * j] - *(short*)&vertN2[2 * j];
		vect_B[j] = *(short*)&vertN3[2 * j] - *(short*)&vertN1[2 * j];
	}

	cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
	cross_P[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
	cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];

	cross_P[0] = cross_P[0] >> SHIFT_HARD;
	cross_P[1] = cross_P[1] >> SHIFT_HARD;
	cross_P[2] = cross_P[2] >> SHIFT_HARD;

	int len = (int)sqrt(
		(cross_P[0] * cross_P[0]) +
		(cross_P[1] * cross_P[1]) +
		(cross_P[2] * cross_P[2])
	) << SHIFT_HARD;

	// ======== Copy ================

	// close enough for now
	return len > (1 << 0x11) ? 0x12 : 0x11;
}

short GetTriNorm(char* quadBlcokArr, char* vertexArr, int id, int n1, int n2, int n3)
{
	// ======== Copy ================

	int vect_A[3];
	int vect_B[3];
	int cross_P[3];

	char* quadBlock = &quadBlcokArr[0x5C * id];
	char* vertN1 = &vertexArr[*(short*)&quadBlock[2 * n1] * 0x10];
	char* vertN2 = &vertexArr[*(short*)&quadBlock[2 * n2] * 0x10];
	char* vertN3 = &vertexArr[*(short*)&quadBlock[2 * n3] * 0x10];

	for (int j = 0; j < 3; j++)
	{
		vect_A[j] = *(short*)&vertN1[2 * j] - *(short*)&vertN2[2 * j];
		vect_B[j] = *(short*)&vertN3[2 * j] - *(short*)&vertN1[2 * j];
	}

	cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
	cross_P[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
	cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];

	cross_P[0] = cross_P[0] >> SHIFT_HARD;
	cross_P[1] = cross_P[1] >> SHIFT_HARD;
	cross_P[2] = cross_P[2] >> SHIFT_HARD;

	int len = (int)sqrt(
		(cross_P[0] * cross_P[0]) +
		(cross_P[1] * cross_P[1]) +
		(cross_P[2] * cross_P[2])
	) << SHIFT_HARD;

	// ======== Copy ================

	int top = 0x1000 << *(char*)&quadBlock[0x3f];

	// fail-safe for quadblocks that have zero size,
	// used to make textures load in TexLayout
	if (len == 0) return 0;

	// real result
	return top / len;
}

short GetTriNorm_LOWPOLY(char* quadBlcokArr, char* vertexArr, int id, int n1, int n2, int n3)
{
	// ======== Copy ================

	int vect_A[3];
	int vect_B[3];
	int cross_P[3];

	char* quadBlock = &quadBlcokArr[0x5C * id];
	char* vertN1 = &vertexArr[*(short*)&quadBlock[2 * n1] * 0x10];
	char* vertN2 = &vertexArr[*(short*)&quadBlock[2 * n2] * 0x10];
	char* vertN3 = &vertexArr[*(short*)&quadBlock[2 * n3] * 0x10];

	for (int j = 0; j < 3; j++)
	{
		vect_A[j] = *(short*)&vertN1[2 * j] - *(short*)&vertN2[2 * j];
		vect_B[j] = *(short*)&vertN3[2 * j] - *(short*)&vertN1[2 * j];

		// only for LOWPOLY
		vect_A[j] /= 2;
		vect_B[j] /= 2;
	}

	cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
	cross_P[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
	cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];

	cross_P[0] = cross_P[0] >> SHIFT_HARD;
	cross_P[1] = cross_P[1] >> SHIFT_HARD;
	cross_P[2] = cross_P[2] >> SHIFT_HARD;

	int len = (int)sqrt(
		(cross_P[0] * cross_P[0]) +
		(cross_P[1] * cross_P[1]) +
		(cross_P[2] * cross_P[2])
	) << SHIFT_HARD;

	// ======== Copy ================

	int top = 0x1000 << *(char*)&quadBlock[0x3f];

	// fail-safe for quadblocks that have zero size,
	// used to make textures load in TexLayout
	if (len == 0) return 0;

	// real result
	return top / len;
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
	char* vertexArr;
	char* bspArr;

	int quadBlockCount, bspCount;

	meshInfo = &levelPtr[*(int*)&levelPtr[0]];
	
	quadBlockArr = &levelPtr[*(int*)&meshInfo[0xC]];
	vertexArr = &levelPtr[*(int*)&meshInfo[0x10]];
	bspArr = &levelPtr[*(int*)&meshInfo[0x18]];

	quadBlockCount = *(int*)&meshInfo[0];
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

		char* visMem = &levelPtr[*(int*)&levelPtr[0x190]];

		// visLeafList -> bspList
		for (int i = 0; i < 0x90; i+=4)
		{
			if (*(int*)&visMem[i] != 0)
			{
				*(int*)&ptr_Arr[ptr_Count++] = (int)&visMem[i] - (int)levelPtr;
				sz += 1 * 4;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (*(int*)&visMem[0x80 + 4 * i] != 0)
			{
				char* bspList = &levelPtr[*(int*)&visMem[0x80 + 4 * i]];

				// do BSP leafs
				for (int j = 0; j < bspCount; j++)
				{
					char* newBspArr = &bspArr[0x20 * j];

					// skip if not a leaf node
					if ((*(short*)&newBspArr[0] & 1) == 0)
						continue;

					// pointer to BSP node in BSP list
					*(int*)&bspList[8 * j + 4] = (int)&bspArr[0x20 * j] - (int)levelPtr;

					// patch pointer in BSP list
					*(int*)&ptr_Arr[ptr_Count++] = (int)&bspList[8 * j + 4] - (int)levelPtr;
					sz += 1 * 4;
				}
			}
		}
	}

	// skip level->0x10, 0x18, 0x24, 0x38, 0x3c, 0x40, 0x44, 
	// 0xD4, 0xE0, 0xE4, 0xE8, 0x13C, 0x144, 
		
	// all quadblocks
	for (int i = 0; i < quadBlockCount; i++)
	{
		// patch pointer table
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x1c] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x20] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x24] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x28] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x40] - (int)levelPtr;
		*(int*)&ptr_Arr[ptr_Count++] = (int)&quadBlockArr[i * 0x5C + 0x44] - (int)levelPtr;
		sz += 6 * 4;

		// block IDs
		int id = (i & 0xFFE0) + 0x1F - (i & 0x1f);
		*(short*)&quadBlockArr[0x5C * i + 0x3C] = id;
		//if ((i & 0x1f) == 0) printf("\n");
		//printf("%d ", id);

		// Normal Vectors
		*(char*)&quadBlockArr[0x5C * i + 0x3F] = GetTriSize(quadBlockArr, vertexArr, i, 0, 4, 5);
		*(short*)&quadBlockArr[0x5C * i + 0x48] = GetTriNorm(quadBlockArr, vertexArr, i, 0, 4, 5);
		*(short*)&quadBlockArr[0x5C * i + 0x4A] = GetTriNorm(quadBlockArr, vertexArr, i, 4, 6, 5);
		*(short*)&quadBlockArr[0x5C * i + 0x4C] = GetTriNorm(quadBlockArr, vertexArr, i, 6, 4, 1);
		*(short*)&quadBlockArr[0x5C * i + 0x4E] = GetTriNorm(quadBlockArr, vertexArr, i, 5, 6, 2);
		*(short*)&quadBlockArr[0x5C * i + 0x50] = GetTriNorm(quadBlockArr, vertexArr, i, 8, 6, 7);
		*(short*)&quadBlockArr[0x5C * i + 0x52] = GetTriNorm(quadBlockArr, vertexArr, i, 7, 3, 8);
		*(short*)&quadBlockArr[0x5C * i + 0x54] = GetTriNorm(quadBlockArr, vertexArr, i, 1, 7, 6);
		*(short*)&quadBlockArr[0x5C * i + 0x56] = GetTriNorm(quadBlockArr, vertexArr, i, 2, 6, 8);
		*(short*)&quadBlockArr[0x5C * i + 0x58] = GetTriNorm_LOWPOLY(quadBlockArr, vertexArr, i, 0, 1, 2);
		*(short*)&quadBlockArr[0x5C * i + 0x5A] = GetTriNorm_LOWPOLY(quadBlockArr, vertexArr, i, 1, 3, 2);

		// Bounding Box
		struct BoundingBox* bspBox;
		bspBox = &quadBlockArr[0x5c*i + 0x2C];
		bspBox->min[0] = 0x7FFF;
		bspBox->min[1] = 0x7FFF;
		bspBox->min[2] = 0x7FFF;
		bspBox->max[0] = -0x7FFF;
		bspBox->max[1] = -0x7FFF;
		bspBox->max[2] = -0x7FFF;

		for (int j = 0; j < 9; j++)
		{
			short* vertData = &vertexArr[*(short*)&quadBlockArr[0x5c*i + 2*j] * 0x10];

			for (int k = 0; k < 3; k++)
			{
				if (vertData[k] < bspBox->min[k]) bspBox->min[k] = vertData[k];
				if (vertData[k] > bspBox->max[k]) bspBox->max[k] = vertData[k];
			}
		}
	}

	// dont inline this, also make sure this call is AFTER
	// the generation of quadblock BoundingBox (in above for-loop)
	SetBspBoxes(levelPtr, quadBlockArr, bspArr, bspArr);

	// Finalize
	*(int*)&ptrMap[0] = ptr_Count << 2;
	printf("NumPointers: %d\n", ptr_Count);

	// === #if 0 for testing ===
#if 1
	f = fopen(argv[1], "wb");
	fwrite(fileBuf, sz, 1, f);
	fclose(f);
#endif
	printf("Level Patched! Exiting Patcher\n\n");
}