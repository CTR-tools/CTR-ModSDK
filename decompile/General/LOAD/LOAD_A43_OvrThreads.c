#include <common.h>

void OVR_Region3();

// DLL loaded = param_1 + 230
void DECOMP_LOAD_OvrThreads(unsigned int param_1)
{
	struct GameTracker* gGT = sdata->gGT;
  
	// if new Threads overlay needs to load
    if (gGT->overlayIndex_Threads != param_1)
    {
#ifndef REBUILD_PC
        sdata->load_inProgress = 1;

		// gets overwritten in overlay callback,
		// commented out or this function wont fit,
		// dont erase this, need more research
		
        // gGT->overlayIndex_Threads = 0xff;

		// Threads overlay 230-233
        DECOMP_LOAD_AppendQueue(
			sdata->ptrBigfileCdPos_2,LT_RAW,
			(param_1+0xe6),&OVR_Region3,
			data.overlayCallbackFuncs[param_1]
		);
#else
		gGT->overlayIndex_Threads = param_1;
#endif
    }
}