#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_MaxTurbos()
{
	// enable unlimited turbos cheat
	sdata->gGT->gameMode2 |= 0x800;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}