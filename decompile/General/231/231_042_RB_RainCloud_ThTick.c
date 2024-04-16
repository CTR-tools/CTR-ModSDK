#include <common.h>

void DECOMP_RB_RainCloud_ThTick(struct Thread* t)
{
  short animFrame;
  int numFrames;
  int reduce;
  int rng;
  struct Instance* inst;
  struct Driver* d;
  struct RainCloud* rcloud;
  struct Instance* dInst;
  
  struct GameTracker* gGT = sdata->gGT;
  
  inst = t->inst;
  rcloud = t->object;
  
  // get player who put the potion
  struct Thread* driverTh = 
	t->parentThread;
  
  d = driverTh->object;
  dInst = driverTh->inst;
  
  animFrame = inst->animFrame;
  numFrames = INSTANCE_GetNumAnimFrames(inst,0);
  
  // if you have not reached the end of the animation
  if ((int)animFrame < numFrames - 1) 
  {
	// increment animation frame
    inst->animFrame++;
  }
  
  // if animation is done
  else 
  {
	// restart animation
    inst->animFrame = 0;
  }
  
  // X, Y, Z
  for(int i = 0; i < 3; i++)
  {
	// get average between instance and driver
	inst->scale[i] += dInst->scale[i];
	inst->scale[i] = inst->scale[i] >> 1;
  }
  
  // offset upward before averaging
  inst->matrix.t[1] += (inst->scale[1] * 5 >> 7);
  
  // X, Y, Z
  for(int i = 0; i < 3; i++)
  {
	// get average between instance and driver
	inst->matrix.t[i] += dInst->matrix.t[i];
	inst->matrix.t[i] = inst->matrix.t[i] >> 1;
  }
  
  // if driver is not using mask weapon
  if ((d->actionsFlagSet & 0x800000) == 0) 
  {
	// if RainCloud alive
    if (rcloud->timeMS != 0) 
	{
      rcloud->timeMS -= gGT->elapsedTimeMS;
	  if (rcloud->timeMS < 0) 
		  rcloud->timeMS = 0;
	  
      if (rcloud->boolScrollItem != 1)
        return;
	  
	  // skip this, cause RainCloud_Init
	  // already checks before setting bool
	  #if 0
      if (d->heldItemID == 0xf)
        return;
      if (d->noItemTimer != 0)
        return;
	  #endif
	  
	  // === Have weapon, have not used it yet ===
	  
	  
	  // === Naughty Dog Bug fixed ===
	  // Allow warpball to be found in itemRNG
	  // if the warpball "was" held, then lost
	  if(d->heldItemID == 9)
		  gGT->gameMode1 &= ~(WARPBALL_HELD);
	  
	  // set weapon to "weapon roulette" to make it spin
      d->heldItemID = 0x10;
	  
	  // you are always 5 frames away from new weapon,
	  // so you get weapon 5 frames after cloud dies
      d->itemRollTimer = FPS_DOUBLE(5);
	  
	  // you hold zero of this item
      d->numHeldItems = 0;
      return;
    }
	
	// === RainCloud timeMS is over ===
    
	if (
			(rcloud->boolScrollItem == 1) && 
			
			// If your weapon is not "no weapon"
			(d->heldItemID != 0xf)
		)
	{
      d->itemRollTimer = 0;
	  
	  // pick random weapon for driver
      VehPhysGeneral_SetHeldItem(d);
    }
  }

  // using mask weapon,
  // or timeMS is over
  rcloud->timeMS = 0;
  d->thCloud = NULL;
  
  ThTick_SetAndExec(t,DECOMP_RB_RainCloud_FadeAway);
  return;
}
