#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_OneLap()
{
	// enable 1-lap race cheat
	sdata->gGT->gameMode2 |= 0x800000;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}