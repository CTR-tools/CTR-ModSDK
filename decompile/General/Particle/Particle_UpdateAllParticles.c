#include <common.h>

void DECOMP_Particle_UpdateAllParticles(void)
{
  int* ptrToList;
  struct GameTracker* gGT = sdata->gGT;
  
  // Pretty sure this is only for debugging,
  // not an actual game feature, and we need bytes
#if 0
  if ((gGT->gameMode1 & PAUSE_THREADS) != 0)
	  return;
#endif
  
  // world-space particles (exhaust on cars)
  ptrToList = &gGT->particleList_ordinary;
  Particle_UpdateList(ptrToList, *ptrToList);
  
  // Draw "heat" particles that warp the screen
  // (above fire in tiger temple flamejet and player missiles)
  ptrToList = &gGT->particleList_heatWarp;
  Particle_UpdateList(ptrToList, *ptrToList);
}