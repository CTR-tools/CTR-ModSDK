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

	// MeshInfo = Level->0x0
	char* meshInfo =	&levelPtr[	*(int*)&levelPtr[0]		];
	
	// QuadBlockArr = meshInfo->0xC
	char* quadBlockArr =&levelPtr[	*(int*)&meshInfo[0xC]	];

	// QuadBlockCount = meshInfo->0x0
	int quadBlockCount = *(int*)&meshInfo[0];

	// bspArr = meshInfo->0x18
	char* bspArr =		&levelPtr[	*(int*)&meshInfo[0x18]	];

	// bspCount = meshInfo->0x1C
	int bspCount = *(int*)&meshInfo[0x1C];

	SetBlockIDs(quadBlockArr, quadBlockCount);
	SetBspBoxes(levelPtr, quadBlockArr, bspArr, bspArr);

#if 0
	int testCount = 0;
	for (int i = 0; i < bspCount; i++)
	{
		char* newBspArr = &bspArr[0x20*i];

		// skip if not a leaf node
		if ((*(short*)&newBspArr[0] & 1) == 0)
			continue;

		int numBlock =	*(int*)&newBspArr[0x18];
		char* newBlockArr = &levelPtr[	*(int*)&newBspArr[0x1C]	];

		int firstIndex = ((int)newBlockArr - (int)quadBlockArr)/0x5c;
		int lastIndex = firstIndex + numBlock - 1;

		for (int j = 0; j < numBlock; j++)
		{
			*(short*)&newBlockArr[0x5c * j + 0x3C] = lastIndex - j;

			printf("BlockID -- NEW: %d\n", 
				lastIndex - j);
		}

		printf("\n");
	}
#endif


	// === #if 0 for testing ===
#if 1
	f = fopen(argv[1], "wb");
	fwrite(fileBuf, sz, 1, f);
	fclose(f);
#endif
	printf("Level Patched! Exiting Patcher\n\n");
}