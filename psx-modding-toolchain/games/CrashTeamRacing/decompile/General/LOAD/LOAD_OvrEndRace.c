#include <common.h>

void OVR_Region1();
void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);
void LOAD_Callback_Overlay_Generic();

// DLL loaded = param_1 + 221
void DECOMP_LOAD_OvrEndRace(unsigned int param_1)
{
  // if new EndOfRace overlay needs to load
  if ((unsigned int)sdata->gGT->overlayIndex_EndOfRace != param_1)
  {
    sdata->load_inProgress = 1;

	// EndOfRace overlay 221-225
	// second parameter '1' means readfile
    LOAD_AppendQueue(sdata->ptrBigfileCdPos_2,1,(param_1 + 0xdd),&OVR_Region1,&LOAD_Callback_Overlay_Generic);

	// save ID, and reload next overlay (sector read invalidation)
	sdata->gGT->overlayIndex_EndOfRace = (char)param_1;
    sdata->gGT->overlayIndex_LOD = 0xff;
  }
  return;
}