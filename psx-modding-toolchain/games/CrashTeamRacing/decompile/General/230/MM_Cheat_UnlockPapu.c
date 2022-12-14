#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_UnlockPapu()
{
	// unlock papu
	sdata->gameProgress.Unlocks.characters_tracks |= 0x100;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}