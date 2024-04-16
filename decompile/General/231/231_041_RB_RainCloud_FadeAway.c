#include <common.h>

// budget 216/224

void DECOMP_RB_RainCloud_FadeAway(struct Thread* t)
{
  struct Instance* inst;
  struct Instance* parentInst;
  struct RainCloud* rcloud;
  
  inst = t->inst;
  rcloud = t->object;  
  parentInst = t->parentThread->inst;

  // offset upward before averaging
  inst->matrix.t[1] += 0x80;

  // X, Y, Z
  for(int i = 0; i < 3; i++)
  {
	// get average between instance and driver
	inst->matrix.t[i] += parentInst->matrix.t[i];
	inst->matrix.t[i] = inst->matrix.t[i] >> 1;
  }
  
  struct RainLocal* rainLocal = rcloud->rainLocal;
  rainLocal->frameCount -= FPS_HALF(2);
  
  // shrink scale (x, y, z)
  // use this order, for better register
  // allocation, and less cpu instructions
  inst->scale[2] += FPS_HALF(-0x100);
  inst->scale[1] += FPS_HALF(-0x100);
  inst->scale[0] += FPS_HALF(-0x100);
  
  if (inst->scale[0] < 0) 
  {
    DECOMP_JitPool_Remove(
		&sdata->gGT->JitPools.rain,
		rainLocal
	);
	
	// This thread is now dead
    t->flags |= 0x800;
  }
  return;
}
 