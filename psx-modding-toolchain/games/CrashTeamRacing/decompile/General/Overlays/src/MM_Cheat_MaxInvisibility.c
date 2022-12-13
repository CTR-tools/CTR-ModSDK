#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_MaxInvisibility()
{
	// Enable permanent invisibility cheat
	sdata->gGT->gameMode2 |= 0x8000;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}