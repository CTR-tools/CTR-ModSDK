#include <common.h>

void DECOMP_MM_TrackSelect_Video_State(int state)
{
	// if viewing new icon this frame
	if (state == 1)
	{
        // icon has been viewed for zero frames
		OVR_230.trackSel_video_frameCount = 0;
		
        // player sees a track icon (not video)
		OVR_230.trackSel_video_state = 1;
		
		return;
	}

    // if player sees a track icon
	if (OVR_230.trackSel_video_state == 1)
	{
		// wait 20 frames
	    OVR_230.trackSel_video_frameCount++;
		if(OVR_230.trackSel_video_frameCount > 20)
		{
			// allocate video memory, prepare to play video
			OVR_230.trackSel_video_state = 2;
		}
	}
}
