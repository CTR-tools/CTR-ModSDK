#include <common.h>

void OVR_Region3();

// temporary, till DATA and SDATA are done
#ifdef REBUILD_PS1
int overlayCallbackFuncs[4] =
{
	DECOMP_LOAD_Callback_Overlay_230,
	DECOMP_LOAD_Callback_Overlay_231,
	DECOMP_LOAD_Callback_Overlay_232,
	DECOMP_LOAD_Callback_Overlay_233
};
#endif

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
        DECOMP_LOAD_AppendQueue(
			sdata->ptrBigfileCdPos_2,LT_RAW,
			(param_1+0xe6),&OVR_Region3,
		
			// temporary, till DATA and SDATA are done
			#ifdef REBUILD_PS1
			overlayCallbackFuncs[param_1]
			#else
			data.overlayCallbackFuncs[param_1]
			#endif
		);
    }
    return;
}