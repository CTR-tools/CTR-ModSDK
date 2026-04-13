#include <common.h>

void DECOMP_MainDrawCb_DrawSync()
{
	struct GameTracker* gGT;
	gGT = sdata->gGT;
	
	if (gGT->bool_DrawOTag_InProgress == 1)
	{
		gGT->bool_DrawOTag_InProgress = 0;
	
		#ifdef USE_PROFILER
		void DebugProfiler_Subsection(int flag);
		DebugProfiler_Subsection(2);
		#endif
	}
	
	return;
}