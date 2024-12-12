#include <common.h>

// Check if ghosts are beaten on all tracks
// 0 for N Tropy Open
// 1 for N Tropy Beaten
// 2 for N Oxide Beaten
int DECOMP_GAMEPROG_CheckGhostsBeaten(int ghostID)
{
	int i;
	
	// check all tracks
	for(i = 0; i < 18; i++)
	{
		// if a single track has not beaten this ghost
		if((sdata->gameProgress.highScoreTracks[i].timeTrialFlags >> ghostID) == 0)
		{
			return 0;
		}
	}
	
	// beaten on all tracks
	return 1;
}