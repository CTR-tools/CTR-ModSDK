#include <common.h>

void OVR_Region2();
void LOAD_AppendQueue(int bigfile, int type, int fileIndex, void* destinationPtr, void* callback);
void LOAD_Callback_Overlay_Generic();

// param_1 = numPlyrCurrGame {1,2,3,4}
void DECOMP_LOAD_OvrLOD(unsigned int param_1)
{
  // if new LOD overlay needs to load
  if ((unsigned int)sdata->gGT->overlayIndex_LOD  != (param_1 - 1U))
  {
    sdata->load_inProgress = 1;

	// LOD overlay 226-229 (numPlyrCurrGame + 0xe1)
	// second parameter '1' means readfile
    LOAD_AppendQueue(sdata->ptrBigfileCdPos_2,1,(param_1 + 0xe1),&OVR_Region2,&LOAD_Callback_Overlay_Generic);

	// save ID, and reload next overlay (sector read invalidation)
	sdata->gGT->overlayIndex_LOD = (char)(param_1 - 1U);
    sdata->gGT->overlayIndex_Threads = 0xff;
  }
  return;
}