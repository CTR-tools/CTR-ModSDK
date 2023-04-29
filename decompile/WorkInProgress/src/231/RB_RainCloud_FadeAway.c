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
  inst->scale[0] += -0x100;
  inst->scale[1] += -0x100;
  inst->scale[2] += -0x100;
  
  // animation?
  *(int *)(rcloud[0] + 8) -= 2;
  
  if (inst->scale[0] < 0) {
    JitPool_Remove(sdata->gGT->JitPools.rain,rcloud[0]);
	
	// This thread is now dead
    t->flags |= 0x800;
  }
  return;
}
 