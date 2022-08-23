#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_UnlockTropy()
{
	// unlock N Tropy
	sdata.gameProgress.Unlocks.characters_tracks |= 0x20;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}