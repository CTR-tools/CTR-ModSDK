#include <common.h>

void DECOMP_CS_Podium_Stand_ThTick(struct Thread *t)
{
  if (OVR_233.isCutsceneOver != 0) 
  {
    // thread is now dead
    t->flags |= 0x800;
  }
}