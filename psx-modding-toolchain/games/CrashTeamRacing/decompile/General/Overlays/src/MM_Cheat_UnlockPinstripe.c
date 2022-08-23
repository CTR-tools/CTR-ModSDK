#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_UnlockPinstripe()
{
	// unlock pinstripe
	sdata.gameProgress.Unlocks.characters_tracks |= 0x400;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}