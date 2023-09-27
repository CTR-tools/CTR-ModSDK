#include <common.h>

void OVR_Region2();

// param_1 = numPlyrCurrGame {1,2,3,4}
void DECOMP_LOAD_OvrLOD(unsigned int param_1)
{
  // if new LOD overlay needs to load
  if ((unsigned int)sdata->gGT->overlayIndex_LOD  != (param_1 - 1U))
  {
    sdata->load_inProgress = 1;

	// LOD overlay 226-229 (numPlyrCurrGame + 0xe1)
    DECOMP_LOAD_AppendQueue(sdata->ptrBigfileCdPos_2,LT_RAW,(param_1 + 0xe1),&OVR_Region2,&DECOMP_LOAD_Callback_Overlay_Generic);

	// save ID, and reload next overlay (sector read invalidation)
	sdata->gGT->overlayIndex_LOD = (char)(param_1 - 1U);
    sdata->gGT->overlayIndex_Threads = 0xff;
  }
  return;
}