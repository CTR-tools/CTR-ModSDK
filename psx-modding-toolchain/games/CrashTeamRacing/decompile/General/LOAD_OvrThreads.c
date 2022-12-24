#include <common.h>

void OVR_Region3();
void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);

// DLL loaded = param_1 + 230
void DECOMP_LOAD_OvrThreads(unsigned int param_1)
{
    // if overlayIndex_Threads changed from last time
    if ((unsigned int) sdata->gGT->overlayIndex_Threads != param_1)
    {
        // load new overlay,
        // therefore, overlay shouldn't reload unless changed

        // game is now loading
        sdata->load_inProgress = 1;

        // do not save overlayIndex_Threads,
        // the value will be written in a callback
        sdata->gGT->overlayIndex_Threads = 0xff;	// but why? why not do it here?

        // Load DLL to 0xab9f0
        // add to load queue from range 230 (param1 + 0xe6)
        // DAT_8008d09c is the Pointer to "cd position of bigfile"
        // second parameter '1' means readfile
        LOAD_AppendQueue(sdata->ptrBigfileCdPos_2,1,(param_1+0xe6),&OVR_Region3,data.overlayCallbackFuncs[param_1]);
    }
    return;
}