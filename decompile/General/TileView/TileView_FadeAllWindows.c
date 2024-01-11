#include <common.h>

void DECOMP_TileView_FadeAllWindows()
{
	struct GameTracker* gGT = sdata->gGT;

	for(int i=0; i < gGT->numPlyrCurrGame; i++)
	{
		TileView_FadeOneWindow(&gGT->tileView[i]);
	}

	TileView_FadeOneWindow(&gGT->tileView_UI);
}