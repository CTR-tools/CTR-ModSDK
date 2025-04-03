#include <common.h>

void OVR_Region2();

// param_1 = numPlyrCurrGame {1,2,3,4}
void DECOMP_LOAD_OvrLOD(unsigned int param_1)
{
  // change {1-4} -> {0-3}
  param_1 -= 1;

  struct GameTracker* gGT = sdata->gGT;

  // if new LOD overlay needs to load
  if ((unsigned int)gGT->overlayIndex_LOD != param_1)
  {
#ifndef REBUILD_PC
	// LOD overlay 226-229
    DECOMP_LOAD_AppendQueue(
		0, LT_SETADDR,
		BI_OVERLAYSECT2 + param_1, 
		&OVR_Region2, NULL);
#endif

	// save ID, and reload next overlay (sector read invalidation)
	gGT->overlayIndex_LOD = param_1;
    gGT->overlayIndex_Threads = 0xff;
  }
  return;
}