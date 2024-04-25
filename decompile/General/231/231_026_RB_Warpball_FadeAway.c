#include <common.h> 

void DECOMP_RB_Warpball_FadeAway(struct Thread* t)
{
  short frameId;
  int iVar2;
  struct TrackerWeapon* tw;
  struct Instance* inst;
  struct Driver* d;
  struct GameTracker* gGT;
  
  gGT = sdata->gGT;
  
  tw = t->object;
  inst = t->inst;
  frameId = tw->fadeAway_frameCount5;
  
  if (frameId > 5) 
  {
    d = tw->driverTarget;
    
	if (d != NULL) 
	{
	  // remove 2D square-target being drawn on the player's screen 
      d->actionsFlagSet &= 0xfbffffff;
    }
	
	// remove active warpball flag
	gGT->gameMode1 &= ~(WARPBALL_HELD);
	
	// This thread is now dead
    t->flags |= 0x800;
    return;
  }
  
  // set scale (x, y, z)
  inst->scale[0] = ((short*)0x800b2c88)[(frameId*3)+0];
  inst->scale[1] = ((short*)0x800b2c88)[(frameId*3)+1];
  inst->scale[2] = ((short*)0x800b2c88)[(frameId*3)+2];
  
  inst->matrix.t[1] = tw->distFromGround + ((int *)0x800b2cac)[frameId];
  
  #ifdef USE_60FPS
  if(gGT->timer&1)
  #endif  
	tw->fadeAway_frameCount5 += 1;
  
  return;
}