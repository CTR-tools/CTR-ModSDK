#include <common.h> 

void DECOMP_RB_Warpball_FadeAway(struct Thread* t)
{
  short frameId;
  int iVar2;
  struct TrackerWeapon* tw;
  struct Instance* inst;
  struct Driver* d;
  
  // get object from thread
  tw = t->object;
  
  // get instance from thread
  inst = t->inst;
  
  if (tw->fadeAway_frameCount5 > 5) 
  {
    d = tw->driverTarget;
    
	if (d != NULL) 
	{
	  // remove 2D square-target being drawn on the player's screen 
      d->actionsFlagSet &= 0xfbffffff;
    }
	
	// remove active warpball flag
	sdata->gGT->gameMode1 &= ~(WARPBALL_HELD);
	
	// This thread is now dead
    t->flags |= 0x800;
    return;
  }
  
  // frame counter
  frameId = tw->fadeAway_frameCount5;
  
  iVar2 = (int)frameId * 6;
  
  // set scale (x, y, z)
  inst->scale[0] = ((char *)0x800b2c88)[iVar2];
  inst->scale[1] = ((char *)0x800b2c8a)[iVar2];
  inst->scale[2] = ((char *)0x800b2c8c)[iVar2];
  
  inst->matrix.t[1] = tw->distFromGround + ((int *)0x800b2cac)[frameId];
  
  #ifdef USE_60FPS
  if(sdata->gGT->timer&1)
  #endif  
	tw->fadeAway_frameCount5 += 1;
  
  return;
}