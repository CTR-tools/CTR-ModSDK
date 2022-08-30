#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_SuperTurboPads()
{
	// enable super turbo pads cheat
	sdata.gGT->gameMode2 |= 0x100000;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}