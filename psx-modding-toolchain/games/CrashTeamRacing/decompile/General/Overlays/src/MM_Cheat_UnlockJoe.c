#include <common.h>

void OtherFX_Play(int sfxID, int flag);

void MM_Cheat_UnlockJoe()
{
	// unlock Komodoe Joe
	sdata.gameProgress.Unlocks.characters_tracks |= 0x200;
	
	// play cheat sound
	OtherFX_Play(0x67, 1);
	return;
}