#include <common.h>

void OVR_Region1();

// DLL loaded = param_1 + 221
void DECOMP_LOAD_OvrEndRace(unsigned int param_1)
{
  struct GameTracker* gGT = sdata->gGT;
  
  // if new EndOfRace overlay needs to load
  if ((unsigned int)gGT->overlayIndex_EndOfRace != param_1)
  {
#ifndef REBUILD_PC
    sdata->load_inProgress = 1;

	// EndOfRace overlay 221-225
    DECOMP_LOAD_AppendQueue(
		(int)sdata->ptrBigfileCdPos_2,LT_RAW,
		BI_OVERLAYSECT1 + param_1, &OVR_Region1,
		&DECOMP_LOAD_Callback_Overlay_Generic);
#endif

	// save ID, and reload next overlay (sector read invalidation)
	gGT->overlayIndex_EndOfRace = param_1;
	
	// Optimization, new Region1 overlays
	// cut off loading at 2 disc sectors (not 3),
	// so Region2 RAM is protected, dont reload
	// Region2 unless numPlayers changes (LOAD_OvrLOD)
	#if 0
    gGT->overlayIndex_LOD = 0xff;
	#endif
  }
  return;
}