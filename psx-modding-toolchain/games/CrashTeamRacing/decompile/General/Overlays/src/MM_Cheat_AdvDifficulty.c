#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_AdvDifficulty()
{
	// known to internet as:
	// Enable beakers and TNTs only cheat
	
	// actually involves difficulty somehow
	
	sdata.gGT->advFlags |= 0x40000;
 
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}