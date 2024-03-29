#include <common.h>

void DECOMP_Particle_UpdateAllParticles(void)
{
  int* ptrToList;
  struct GameTracker* gGT = sdata->gGT;
  
  if ((gGT->gameMode1 & PAUSE_THREADS) != 0)
	  return;
  
  // byte buget

  // world-space particles (exhaust on cars)
  ptrToList = &gGT->particleList_ordinary;
  Particle_UpdateList(ptrToList, *ptrToList);
  
// dang byte budget
#if 0
  // Draw "heat" particles that warp the screen
  // (above fire in tiger temple flamejet and player missiles)
  ptrToList = &gGT->particleList_heatWarp;
  Particle_UpdateList(ptrToList, *ptrToList);
#endif
}