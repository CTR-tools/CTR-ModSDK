#include <common.h>

void OVR_Region1();
void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);
void LOAD_Callback_Overlay_Generic();

// DLL loaded = param_1 + 221
void DECOMP_LOAD_OvrEndRace(unsigned int param_1)
{
  // if overlayIndex_EndOfRace is different than the overlay requested
  if ((unsigned int)sdata->gGT->overlayIndex_EndOfRace != param_1)
  {
	// load new overlay, this means
	// overlay wont load unless changed

	// game is now loading
    sdata->load_inProgress = 1;

	// Load DLL to 9f6fc
	//add to load queue from range 221 (param1 + 0xdd)
	// DAT_8008d09c is the Pointer to "cd position of bigfile"
	// second parameter '1' means readfile
    LOAD_AppendQueue(sdata->ptrBigfileCdPos_2,1,(param_1 + 0xdd),&OVR_Region1,&LOAD_Callback_Overlay_Generic);

	// save new overlayIndex_EndOfRace
	sdata->gGT->overlayIndex_EndOfRace = (char)param_1;

	// force LOD overlay to reload,
	// by nullifying the saved index
    sdata->gGT->overlayIndex_LOD = 0xff;	// but why? what a waste
  }
  return;
}