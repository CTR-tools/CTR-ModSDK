#include <common.h>

int DECOMP_MixRNG_Scramble()
{
	*(int*)0x8000fff0 = *(int*)0x8000fff0 + 1;
	
	// random algorithm for seemingly-random numbers
	sdata->randomNumber = sdata->randomNumber * 0x6255 + 0x3619 & 0xffff;
	return sdata->randomNumber;
}

#define height 200

void RunUpdateHook()
{
	if (!(sdata->gGT->gameMode1 & LOADING))
	{
		char number[32];
		sprintf(number, "%d", *(int*)0x8000fff0);
		DecalFont_DrawLine(number, 10, height, FONT_SMALL, ORANGE);
	}
}