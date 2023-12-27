#include <common.h>

void DECOMP_UI_DrawNumRelic(short posX, short posY)
{
	int num;
	struct GameTracker* gGT;
	char string[8];

	DECOMP_DecalFont_DrawLine(&sdata->s_x[0], posX, posY+4, FONT_SMALL, ORANGE);
	
	gGT = sdata->gGT;
	num = gGT->currAdvProfile.numRelics;
	if((gGT->gameMode2 & 0x1000000) != 0) num--;
	
	sprintf(&string[0], &sdata->s_longInt[0], num);
	DECOMP_DecalFont_DrawLine(&string[0], posX+0xD, posY, FONT_BIG, ORANGE);
}