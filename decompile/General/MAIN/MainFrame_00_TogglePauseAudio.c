#include <common.h>

void DECOMP_MainFrame_TogglePauseAudio(int bool_pause)
{
	if (bool_pause == 0)
	{
		if (sdata->boolSoundPaused)
		{
			DECOMP_howl_StopAudio(0, 0, 1);
			DECOMP_howl_UnPauseAudio();
			sdata->boolSoundPaused = 0;
		}
	}
	else if (sdata->boolSoundPaused == 0)
	{
		DECOMP_OtherFX_Stop2(1);
		DECOMP_howl_PauseAudio();
		sdata->boolSoundPaused = 1;
	}
	return;
}