#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_InfiniteMasks()
{
	// Enable Infinite Masks cheat
	sdata.gGT->gameMode2 |= 0x400;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}