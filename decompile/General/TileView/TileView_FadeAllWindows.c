#include <common.h>

void DECOMP_TileView_FadeAllWindows()
{
	int i;
	struct GameTracker* gGT;
	gGT = sdata->gGT;

	i=0;
	for(i=0; i < gGT->numPlyrCurrGame; i++)
	{
		TileView_FadeOneWindow(&gGT->tileView[i]);
	}

	TileView_FadeOneWindow(&gGT->tileView_UI);
}