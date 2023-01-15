#include <common.h>

void Camera110_FadeOneWindow(struct Camera110* window);

void DECOMP_Camera110_FadeAllWindows()
{
	int i;
	struct GameTracker* gGT;
	gGT = sdata->gGT;

	i=0;
	for(i=0; i < gGT->numPlyrCurrGame; i++)
	{
		Camera110_FadeOneWindow(&gGT->camera110[i]);
	}

	Camera110_FadeOneWindow(&gGT->camera110_UI);
}