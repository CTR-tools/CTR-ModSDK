#include <common.h>

void DECOMP_MainFrame_TogglePauseAudio(int bool_pause)
{
	if (bool_pause == 0)
	{
		if (sdata->boolSoundPaused)
		{
			howl_StopAudio(0, 0, 1);
			howl_UnPauseAudio();
			sdata->boolSoundPaused = 0;
		}
	}
	else if (sdata->boolSoundPaused == 0)
	{
		OtherFX_Stop2(1);
		howl_PauseAudio();
		sdata->boolSoundPaused = 1;
	}
	return;
}