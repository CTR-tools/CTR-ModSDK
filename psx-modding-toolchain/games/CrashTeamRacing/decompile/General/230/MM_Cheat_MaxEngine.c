#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_MaxEngine()
{
	// Enable Super Engine Cheat
	sdata->gGT->gameMode2 |= 0x10000;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}