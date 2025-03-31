#include <common.h>

void DECOMP_MM_TrackSelect_Video_State(int state)
{
	// if viewing new icon this frame
	if (state == 1)
	{
        // icon has been viewed for zero frames
		D230.trackSel_video_frameCount = 0;
		
        // player sees a track icon (not video)
		D230.trackSel_videoStateCurr = 1;
		
		return;
	}
	
	#ifdef USE_PCDRV
	// dont start video
	// can also enable this for no$psx
	return;
	#endif

    // if player sees a track icon
	if (D230.trackSel_videoStateCurr == 1)
	{
		// wait 20 frames
	    D230.trackSel_video_frameCount++;
		if(D230.trackSel_video_frameCount > FPS_DOUBLE(20))
		{
			// allocate video memory, prepare to play video
			D230.trackSel_videoStateCurr = 2;
		}
	}
}
