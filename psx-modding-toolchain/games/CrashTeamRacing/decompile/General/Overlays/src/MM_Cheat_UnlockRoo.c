#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_UnlockRoo()
{
	// unlock ripper roo
	sdata.gameProgress.Unlocks.characters_tracks |= 0x80;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}