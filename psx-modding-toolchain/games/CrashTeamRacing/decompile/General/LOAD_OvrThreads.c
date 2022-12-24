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

        // do not save overlayIndex_Threads,
        // the value will be written in a callback
        sdata->gGT->overlayIndex_Threads = 0xff; // why not set it here?

		// Threads overlay 230-233
		// second parameter '1' means readfile
        LOAD_AppendQueue(sdata->ptrBigfileCdPos_2,1,(param_1+0xe6),&OVR_Region3,data.overlayCallbackFuncs[param_1]);
    }
    return;
}