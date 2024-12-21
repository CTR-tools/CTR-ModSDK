#include <common.h>

void DECOMP_PushBuffer_FadeAllWindows()
{
	struct GameTracker* gGT = sdata->gGT;

	for(int i=0; i < gGT->numPlyrCurrGame; i++)
	{
		DECOMP_PushBuffer_FadeOneWindow(&gGT->pushBuffer[i]);
	}

	DECOMP_PushBuffer_FadeOneWindow(&gGT->pushBuffer_UI);
}