#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_UnlockTracks()
{
	// unlock all tracks
	sdata.gameProgress.Unlocks.characters_tracks |= 0x1e;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}