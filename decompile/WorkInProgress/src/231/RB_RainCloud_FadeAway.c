#include <common.h>

void DECOMP_RB_RainCloud_FadeAway(struct Thread* t)
{
  struct Instance* inst;
  struct Instance* parentInst;
  struct RainCloud* rcloud;
  
  inst = t->inst;
  
  parentInst = t->parentThread->inst;

  rcloud = inst->thread->object;
  
  // set X, Y and Z
  inst->matrix.t[0] += parentInst->matrix.t[0] >> 1;
  inst->matrix.t[1] += (parentInst->matrix.t[1] + 0x80) >> 1;
  inst->matrix.t[2] += parentInst->matrix.t[2] >> 1;
  
  // shrink scale (x, y, z)
  inst->scale[0] += FPS_HALF(-0x100);
  inst->scale[1] += FPS_HALF(-0x100);
  inst->scale[2] += FPS_HALF(-0x100);
  
  *(int *)((int)rcloud->rainBuffer + 8) -= FPS_HALF(2);
  
  if (inst->scale[0] < 0) 
  {
    DECOMP_JitPool_Remove(
		sdata->gGT->JitPools.rain,
		rcloud->rainBuffer
	);
	
	// This thread is now dead
    t->flags |= 0x800;
  }
  return;
}
 