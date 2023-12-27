#include <common.h>

// 172 byte budget

void DECOMP_UI_DrawNumTimebox(short posX, short posY, struct Driver* d)
{
	int numCratesOwned;
	int numCratesTotal;
	struct GameTracker* gGT;
	char string[8];

	DECOMP_DecalFont_DrawLine(&sdata->s_x[0], posX+0x14, posY-10, FONT_SMALL, ORANGE);
	
	gGT = sdata->gGT;
	numCratesOwned = d->numTimeCrates;
	numCratesTotal = gGT->timeCratesInLEV;
	
	sprintf(&string[0], 
#ifndef REBUILD_PS1
		&rdata.s_lapString[0], 
#else
		"%2.02d/%ld",
#endif
		numCratesOwned, numCratesTotal);

	DECOMP_DecalFont_DrawLine(&string[0], posX+0x21, posY-0xe, FONT_BIG, ORANGE);
}