#include <common.h>

void DECOMP_UI_DrawNumCrystal(int posX, int posY, struct Driver* d)
{
	int numCrystalsOwned;
	int numCrystalsTotal;
	struct GameTracker* gGT;
	char string[8];

	DecalFont_DrawLine(&sdata->s_x[0], posX, posY+4, FONT_SMALL, ORANGE);
	
	gGT = sdata->gGT;
	numCrystalsOwned = d->numCrystals;
	numCrystalsTotal = gGT->numCrystalsInLEV;
	
	sprintf(&string[0], &rdata.s_lapString[0], numCrystalsOwned, numCrystalsTotal);
	DecalFont_DrawLine(&string[0], posX+0xD, posY, FONT_BIG, ORANGE);
}