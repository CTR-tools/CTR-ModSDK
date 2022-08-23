#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_UnlockScrapbook()
{
	// unlock the scrapbook
	sdata.gameProgress.Unlocks.scrapbook |= 0x10;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}