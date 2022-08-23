#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_SuperHard()
{
	// enable super hard mode cheat
	sdata.gGT->advFlags |= 0x200000;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}