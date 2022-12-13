#include <common.h>

// This is only one piece of the giant RenderFrame function

// CTR funcs
int RCNT_GetTime_Elapsed(int, int);

// stored in RDATA
void CustomEnd()
{
	// dont optimize frontBuffer to a local variable,
	// it makes zero byte-difference in assembly
	struct GameTracker* gGT;
	gGT = sdata->gGT;
	
	gGT->countTotalTime =
	RCNT_GetTime_Elapsed(gGT->countTotalTime,0);
	
	// do I need the "if"? will it ever be nullptr?
	if(gGT->frontBuffer != 0)
	{
		sdata->frameDuplicator = 2;
		
		// skip debug stuff
		
		PutDispEnv(&gGT->frontBuffer->dispEnv);
		PutDrawEnv(&gGT->frontBuffer->drawEnv);
		
		// dont wip frontBuffer, will reset it rn...
	}
	
	// swap=0, get db[1]
	// swap=1, get db[0]
	gGT->frontBuffer = &gGT->db
		[
			1 - sdata->gGT->swapchainIndex
		];
		
	gGT->bool_DrawOTag_InProgress = 1;
	
	DrawOTag((int)gGT->camera110[0].ptrOT + 0xffc);
	
	gGT->frameTimer_notPaused = gGT->frameTimer_VsyncCallback;
}