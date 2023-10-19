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

    // if player sees a track icon AND track icon has been seen for 20+ frames
	if (OVR_230.trackSel_video_state == 1 && OVR_230.trackSel_video_frameCount > 20)
	{
        // increase frame count
	    OVR_230.trackSel_video_frameCount++;
		// allocate video memory, prepare to play video
		OVR_230.trackSel_video_state = 2;
	}
}
