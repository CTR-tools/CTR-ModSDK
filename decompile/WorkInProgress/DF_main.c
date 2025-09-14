#include <common.h>

void DF_DrawOTag(u_long* ot)
{
	if(sdata->gGT->levelID == CRASH_COVE)
	{
		*(int*)0x8000c000 = *(int*)0x8000c000 + 1;
		
		// Demo Mode never times out, for inf-long unit testing
		sdata->gGT->demoCountdownTimer = 900;
		
		// wait 24 seconds, 720 frames,
		// includes loading screen (12 seconds)
		// includes camera-fly-in, DotLights frames, racing (12 seconds)
		
		// 24s really is 7s, because fly-in and DotLights are 17 seconds
		if(*(int*)0x8000c000 == (45*30))
		{
			while(1) {}
		}
	}
	
	DrawOTag(ot);
}