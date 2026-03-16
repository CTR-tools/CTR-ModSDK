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
  inst->matrix.t.y += 0x80;

	// pos X, Y, Z
	// get average between instance and driver
	for (unsigned char i = 0; i < 3; i++)
	{
		//cant separate this per coord, byte budget
		///Apparently looping uses fewer bytes
		inst->matrix.t.v[i] = (parentInst->matrix.t.v[i] + inst->matrix.t.v[i]) >> 1;
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
		(struct Item*)rainLocal
	);
	
	// This thread is now dead
    t->flags |= 0x800;
  }
  return;
}
 