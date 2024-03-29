#include <common.h>

void DECOMP_Particle_OnDestroy(struct Particle* p)
{
  struct Particle *pp;

  pp = p->prev;

  while (pp != NULL)
  {
    pp = pp->next;
	
	// free list of Oscillator Pool
    LIST_AddFront(&sdata->gGT->JitPools.oscillator.free, pp);
  }
}