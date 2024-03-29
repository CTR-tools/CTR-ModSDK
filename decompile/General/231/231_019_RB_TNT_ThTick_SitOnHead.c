#include <common.h>

void RB_TNT_ThTick_ThrowOffHead();

void DECOMP_RB_TNT_ThTick_SitOnHead(struct Thread* t)
{
  struct Instance* inst;
  struct MineWeapon* mw;
  char state;
  short numFrames;
  unsigned short uVar3;
  int rng;
  
  inst = t->inst;
  
  // object (tnt)
  mw = t->object;
  
  // CopyMatrix
  // To: TNT instance
  // From: obj->driverWhoHitMe->instance
  // Delta: TNT -> 0x1c (position relative to driver)
  LHMatrix_Parent(inst,mw->driverTarget->instSelf,&mw->deltaPos[0]);
  
  // Get Kart State
  state = mw->driverTarget->kartState;
  
  if (
		(state == KS_CRASHING) || 
		(state == KS_MASK_GRABBED) || 
		(state == KS_SPINNING)
	) 
  {
    
	// Play explosion sound
	PlaySound3D(0x3d,inst);
	
	RB_Blowup_Init(inst);
	
LAB_800ad4ec:

	// reset TNT-related pointers
    inst->scale[0] = 0;
    inst->scale[1] = 0;
    inst->scale[2] = 0;
	
	// make invisible
    inst->flags |= 0x80;
	
	// this thread is now dead
    t->flags |= 0x800;
	
    mw->driverTarget->instTntRecv = 0;
		
	return;
  }
  else 
  {
	// If you are already blasted
    if (state == 6) 
	{
	  // Play explosion sound
      PlaySound3D(0x3d,inst);
	  
      RB_Explosion_InitGeneric(inst);
	  
      goto LAB_800ad4ec;
    }
  }
  
  // if this driver is not an AI
  if ((mw->driverTarget->actionsFlagSet & 0x100000) == 0) 
  {
	// if player did not start jumping this frame
    if ((mw->driverTarget->actionsFlagSet & 0x400) == 0) goto LAB_800ad5f8;
	
    if (mw->jumpsRemaining != 0) {
      mw->jumpsRemaining += -1;
      goto LAB_800ad5f8;
    }
    mw->jumpsRemaining = 0;
  }
  else {
    rng = DECOMP_MixRNG_Scramble();
    if (rng != (rng / 0x10e) * 0x10e) goto LAB_800ad5f8;
  }
  
  // set scale (x, y, z)
   inst->scale[0] = 0x800;
   inst->scale[1] = 0x800;
   inst->scale[2] = 0x800;
  
  mw->driverTarget->instTntRecv = 0;
  
  mw->velocity[0] = 0;
  mw->velocity[1] = 0x30;
  mw->velocity[2] = 0;
  mw->deltaPos[0] = 0;
  mw->deltaPos[1] = 0;
  mw->deltaPos[2] = 0;
  
  // assign RB_TNT_ThTick_ThrowOffHead
  ThTick_SetAndExec(t,RB_TNT_ThTick_ThrowOffHead);
  return;
  
LAB_800ad5f8:

  // Get how many frames the TNT has 
  // been on top of someone's head
  numFrames = mw->numFramesOnHead;
  
  // If there is time remaining until TNT blows up,
  // which takes 0x5a frames, 3 seconds
  if (numFrames < 0x5a) 
  {
	// If frame is any of these 6 numbers
    if (
		(numFrames == 0x0) || (numFrames == 0x14) || (numFrames == 0x28) || 
		(numFrames == 0x3c) || (numFrames == 0x46) || (numFrames == 0x50)
	   ) 
	{
	  // Make a "honk" sound
      PlaySound3D(0x3e,inst);
    }
	
	#ifdef USE_60FPS
	if(sdata->gGT->timer & 1)
	#endif
		// add to the frame counter
		mw->numFramesOnHead += 1;
	
	// set scale of TNT, given frame of animation
	uVar3 = ((short*)0x800b295c)[numFrames*2+0];
	inst->scale[0] = uVar3;
	inst->scale[2] = uVar3;
	inst->scale[1] = ((short*)0x800b295c)[numFrames*2+1];
  }
  
  // If time runs out
  else 
  {
	// Blow up
	
    RB_Hazard_HurtDriver(mw->driverTarget,2,mw->instParent->thread->object,0);
    
	// icon damage timer, draw icon as red
	mw->driverTarget->damageColorTimer = 0x1e;
	
	// play 3D sound for TNT explosion
    PlaySound3D(0x3d,inst);
	
    RB_Blowup_Init(inst);
	
	// this thread is now dead
    t->flags |= 0x800;
	
    mw->driverTarget->instTntRecv = NULL;
  }
  
}