#include <common.h>

void DF_DrawOTag(u_long* ot)
{
	if(sdata->gGT->levelID == CRASH_COVE)
	{
		*(int*)0x8000c000 = *(int*)0x8000c000 + 1;
		
		// Demo Mode never times out, for inf-long unit testing
		sdata->gGT->demoCountdownTimer = 900;
		
		// 45*30 = 45 seconds,
		// subtract 17s to get race-time, to take out camera fly-in
		
		// At 32s(15s racing), decomp/retail match,
		// At 45s(28s racing), decomp/retail miss
		if(*(int*)0x8000c000 == (45*30))
		{
			while(1) {}
		}
	}
	
	DrawOTag(ot);
}