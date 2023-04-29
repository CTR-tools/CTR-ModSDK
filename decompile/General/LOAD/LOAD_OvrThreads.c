#include <common.h>

void OVR_Region3();
void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);

// DLL loaded = param_1 + 230
void DECOMP_LOAD_OvrThreads(unsigned int param_1)
{
	// if new Threads overlay needs to load
    if ((unsigned int) sdata->gGT->overlayIndex_Threads != param_1)
    {
        sdata->load_inProgress = 1;

		// gets overwritten in overlay callback,
		// commented out or this function wont fit,
		// dont erase this, need more research
        // sdata->gGT->overlayIndex_Threads = 0xff;

		// Threads overlay 230-233
		// second parameter '1' means readfile
        LOAD_AppendQueue(sdata->ptrBigfileCdPos_2,1,(param_1+0xe6),&OVR_Region3,data.overlayCallbackFuncs[param_1]);
    }
    return;
}