#include <common.h>

void OVR_Region2();
void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);
void LOAD_Callback_Overlay_Generic();

// DLL = 225 + param_1
void DECOMP_LOAD_OvrLOD(unsigned int param_1)
{
  // if overlayIndex_LOD loaded is not the one being requested
  if ((unsigned int)sdata->gGT->overlayIndex_LOD  != (param_1 - 1U))
  {
	// load new overlay,
	// this means it skips loading if
	// the overlay was already loaded before

	// game is now loading
    sdata->load_inProgress = 1;

	// Load DLL to 0xa0cb8
	// add to load queue from range 225 (param1 + 0xe1)
	// DAT_8008d09c is the Pointer to "cd position of bigfile"
	// second parameter '1' means readfile
    LOAD_AppendQueue(sdata->ptrBigfileCdPos_2,1,(param_1 + 0xe1),&OVR_Region2,&LOAD_Callback_Overlay_Generic);

	// overlayIndex_LOD loaded
	sdata->gGT->overlayIndex_LOD = (char)(param_1 - 1U);

	// force overlayIndex_Threads to reload
    sdata->gGT->overlayIndex_Threads = 0xff;	// but why? what a waste
  }
  return;
}