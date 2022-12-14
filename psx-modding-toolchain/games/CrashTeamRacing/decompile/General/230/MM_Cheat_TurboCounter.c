#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_TurboCounter()
{
	// enable turbo counter cheat
	sdata->gGT->gameMode2 |= 0x8000000;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}