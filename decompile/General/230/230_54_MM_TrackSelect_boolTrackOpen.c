#include <common.h>

char DECOMP_MM_TrackSelect_boolTrackOpen(struct MainMenu_LevelRow* menuSelect)
{
	short flag = menuSelect->unlock;
	char unlocked = false;
		
	if (
		// -1, always unlocked by default
		flag == -1 ||

		// -2, Oxide Station, unlocked by default only on 1P.
		(flag == -2 && sdata->gGT->numPlyrNextGame == 1) ||

		// track has requirements AND requirements is met
		(flag >= -1 && (sdata->gameProgress.unlocks[flag >> 5] >> flag) & 1))
	{
		// unlock track
		unlocked = true;
	}

	return unlocked;
}
