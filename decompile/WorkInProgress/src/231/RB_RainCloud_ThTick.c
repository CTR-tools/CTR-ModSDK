#include <common.h>

void DECOMP_RB_RainCloud_ThTick(struct Thread* t)
{
  short animFrame;
  int numFrames;
  int reduce;
  int rng;
  struct Instance* inst;
  struct Driver* parent;
  struct RainCloud* rcloud;
  struct Instance* parentInst;
  
  struct GameTracker* gGT = sdata->gGT;
  
  inst = t->inst;
  rcloud = t->object;
  
  animFrame = inst->animFrame;
  
  // get player who put the potion
  parent = t->parentThread->object;
  parentInst = t->parentThread->inst;
  
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
  
  // set scale of one instance to half the scale of another
  inst->scale[0] += parentInst->scale[0] >> 1;
  inst->scale[1] += parentInst->scale[1] >> 1;
  inst->scale[2] += parentInst->scale[2] >> 1;
	   
  inst->matrix.t[0] += parentInst->matrix.t[0] >> 1;
  inst->matrix.t[1] += (parentInst->matrix.t[1] + (inst->scale[1] * 5 >> 7)) >> 1;
  inst->matrix.t[2] += parentInst->matrix.t[2] >> 1;
  
  // if driver is not using mask weapon
  if ((parent->actionsFlagSet & 0x800000) == 0) 
  {
	// if RainCloud alive
    if (rcloud->timeMS != 0) 
	{
      rcloud->timeMS -= gGT->elapsedTimeMS;
	  if (rcloud->timeMS < 0) 
		  rcloud->timeMS = 0;
	  
      if (rcloud->boolScrollItem != 1)
        return;
	  
	  // If your weapon is "no weapon"
      if (parent->heldItemID == 0xf)
        return;
	  
	  // This is if weapon was already fired,
	  // but is flickering in the UI
      if (parent->noItemTimer != 0)
        return;
	  
	  
	  // === Have weapon, have not used it yet ===
	  
	  
	  // === Naughty Dog Bug fixed ===
	  // Allow warpball to be found in itemRNG
	  // if the warpball "was" held, then lost
	  if(parent->heldItemID == 9)
		  gGT->gameMode1 &= ~(WARPBALL_HELD);
	  
	  // set weapon to "weapon roulette" to make it spin
      parent->heldItemID = 0x10;
	  
	  // you are always 5 frames away from new weapon,
	  // so you get weapon 5 frames after cloud dies
      parent->itemRollTimer = FPS_DOUBLE(5);
	  
	  // you hold zero of this item
      parent->numHeldItems = 0;
      return;
    }
	
	// === RainCloud timeMS is over ===

    rcloud->timeMS = 0;
	
	// erase cloudTh pointer
    parent->thCloud = NULL;
    
	if (
			(rcloud->boolScrollItem == 1) && 
			
			// If your weapon is not "no weapon"
			(parent->heldItemID != 0xf)
		)
	{
      parent->itemRollTimer = 0;
	  
	  // pick random weapon for driver
      VehPhysGeneral_SetHeldItem(parent);
    }
  }
  else {
    rcloud->timeMS = 0;
	
	// erase pointer to cloud thread
    parent->thCloud = NULL;
  }
  
  ThTick_SetAndExec(t,RB_RainCloud_FadeAway);
  return;
}
