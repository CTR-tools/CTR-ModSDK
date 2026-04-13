#include <common.h>
#include "global.h"

struct MyData
{
	short World_posX;
	short World_posY;
	short World_posZ;
	short World_posW;

	short Screen_posX;
	short Screen_posY;

	int Screen_posZ;
};

int GetOverheadLen(struct Driver* d)
{
	struct MyData* ptrDest = (struct MyData*)0x1f800108;
	ptrDest->World_posX = d->posCurr.x >> 8;
	ptrDest->World_posY = (d->posCurr.y >> 8) + 25;
	ptrDest->World_posZ = d->posCurr.z >> 8;
	ptrDest->World_posW = 0;

	gte_ldv0(&ptrDest->World_posX);

	gte_rtps();
	gte_stsxy(&ptrDest->Screen_posX);
	gte_stsz(&ptrDest->Screen_posZ);

	int posZ = ptrDest->Screen_posZ;

	if(posZ < 150) return 0;
	if(posZ < 190) return 6;
	if(posZ < 234) return 5;
	if(posZ < 331) return 4;
	if(posZ < 475) return 3;
	if(posZ < 906) return 2;
	return 0;
}

#if 0
/*
X +- 0x19			This one feels good
150 -> cutoff
in between is 6len
190 -> 50 (6len)
in between is 5len
234 -> 40 (5len)
in between is 4len
331 -> 30 (4len)
in between is 3len
475 -> 20 (3len)
in between is 2len
906 -> 10 (2len)
906+ cutoff

X +- 0x20			This one feels too wide
150 -> cutoff
in between is 7len
205 -> 60 (7len)
in between is 6len
244 -> 50 (6len)
in between is 5len
312 -> 40 (5len)
in between is 4len
414 -> 30 (4len)
in between is 3len
624 -> 20 (3len)
in between is 2len
1200 -> 10 (2len)
1200+ cutoff
*/

// Designed for 2 players on parking lot,
// each with 1-letter names
void DrawOverheadCalibration()
{
	int i;
	MATRIX* m;

	// temporary
	char message[16];

	struct GameTracker* gGT = sdata->gGT;
	struct MyData* ptrDest = (struct MyData*)0x1f800108;

	if(octr->DriverID == 0)
	{
		gGT->drivers[0]->posCurr[0] = 0;
		gGT->drivers[0]->angle = 0;
	}

	m = &gGT->drivers[0]->instSelf->matrix;
	sprintf(message, "%d", gGT->drivers[0]->posCurr[0] >> 8);
	DecalFont_DrawLine(
		message,
		0x100, 8*3,
		FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	sprintf(message, "%d", 0x19+(gGT->drivers[0]->posCurr[1] >> 8));
	DecalFont_DrawLine(
		message,
		0x100, 8*4,
		FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	sprintf(message, "%d", gGT->drivers[0]->posCurr[2] >> 8);
	DecalFont_DrawLine(
		message,
		0x100, 8*5,
		FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	ptrDest->World_posX = (gGT->drivers[1]->posCurr[0] >> 8) - 0x19;
	ptrDest->World_posY = (gGT->drivers[1]->posCurr[1] >> 8) + 0x19;
	ptrDest->World_posZ = gGT->drivers[1]->posCurr[2] >> 8;
	ptrDest->World_posW = 0;
	gte_ldv0(&ptrDest->World_posX);
	gte_rtps();
	gte_stsxy(&ptrDest->Screen_posX);
	gte_stsz(&ptrDest->Screen_posZ);

	int leftX = ptrDest->Screen_posX;
		DecalFont_DrawLine(
			"A",
			ptrDest->Screen_posX,
			ptrDest->Screen_posY-0x4,
			FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	ptrDest->World_posX = (gGT->drivers[1]->posCurr[0] >> 8) + 0x19;
	ptrDest->World_posY = (gGT->drivers[1]->posCurr[1] >> 8) + 0x19;
	ptrDest->World_posZ = gGT->drivers[1]->posCurr[2] >> 8;
	ptrDest->World_posW = 0;
	gte_ldv0(&ptrDest->World_posX);
	gte_rtps();
	gte_stsxy(&ptrDest->Screen_posX);
	gte_stsz(&ptrDest->Screen_posZ);

	int rightX = ptrDest->Screen_posX;
		DecalFont_DrawLine(
			"A",
			ptrDest->Screen_posX,
			ptrDest->Screen_posY-0x4,
			FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	sprintf(message, "%d", leftX - rightX);
	DecalFont_DrawLine(
		message,
		0x100, 8*8,
		FONT_SMALL, (JUSTIFY_CENTER | ORANGE));

	ptrDest->World_posX = (gGT->drivers[1]->posCurr[0] >> 8) + 0;
	ptrDest->World_posY = (gGT->drivers[1]->posCurr[1] >> 8) + 0x19;
	ptrDest->World_posZ = gGT->drivers[1]->posCurr[2] >> 8;
	ptrDest->World_posW = 0;
	gte_ldv0(&ptrDest->World_posX);
	gte_rtps();
	gte_stsxy(&ptrDest->Screen_posX);
	gte_stsz(&ptrDest->Screen_posZ);

	sprintf(message, "%d", ptrDest->Screen_posZ);
	DecalFont_DrawLine(
		message,
		0x100, 8*9,
		FONT_SMALL, (JUSTIFY_CENTER | ORANGE));
}
#endif

void DrawOverheadNames()
{
	int i;
	MATRIX* m;

	struct GameTracker* gGT = sdata->gGT;
	struct MyData* ptrDest = (struct MyData*)0x1f800108;

	// pushBuffer offset 0x28
	m = &gGT->pushBuffer[0].matrix_ViewProj;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

	#if 0
	DrawOverheadCalibration();
	#endif

	// start from P2
	i = 1;
	int color = (JUSTIFY_CENTER | ORANGE);

	if((gGT->gameMode1 & START_OF_RACE) != 0)
	{
		// start from P1
		i = 0;
		color = (JUSTIFY_CENTER | BLUE);

	}

	for(i; i < octr->NumDrivers; i++)
	{
		int len = GetOverheadLen(gGT->drivers[i]);
		if(len == 0) continue;

		// Mirror Mode Disabled
		#if 0

		// if mirror mode
		if(octr->special != 0)
		{
			ptrDest->Screen_posX =
			0x200 - ptrDest->Screen_posX;
		}

		#endif

		DECOMP_DecalFont_DrawLineStrlen(
			octr->nameBuffer[i],
			len,
			ptrDest->Screen_posX,
			ptrDest->Screen_posY-0x4,
			FONT_SMALL, color);

		// all players except P1
		color = (JUSTIFY_CENTER | ORANGE);
	}
}