#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_MaxBombs()
{
	// enable infinite bowling bombs cheat
	sdata.gGT->advFlags |= 0x400000;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}