#include <common.h>

void RB_TNT_ThTick_ThrowOnHead();
void RB_TNT_ThTick_ThrowOffHead();
void RB_Potion_ThTick_InAir();

void DECOMP_RB_GenericMine_ThTick(struct Thread* t)
{ 
  struct GameTracker* gGT;
  struct Instance* inst;
  struct Instance* coll;
  struct MineWeapon* mw;
  struct Driver* d;
  struct Crate* crate;
  struct Instance* instCrate;
  struct MineWeapon* tnt;
  unsigned int model;
  int numFrames;
  int *func;
  int param;
  int boolPotion;
  
  gGT = sdata->gGT;
  inst = t->inst;
  mw = inst->thread->object;
  model = inst->model->id;
  
  boolPotion = (unsigned int)(model - 0x46) < 2;
  
  // if weapon is "thrown" like Komodo Joe
  if ((mw->extraFlags & 2) != 0) 
  {
	// Potion
    if(boolPotion != 0)
	{
	  // cooldown of 0.24s
      mw->cooldown = 0xf0;
	  
      func = RB_Potion_ThTick_InAir;
    }
	
	// TNT
    else
	{
      func = RB_TNT_ThTick_ThrowOffHead;
	  
	  // set scale (x, y, z)
      inst->scale[0] = 0x800;
      inst->scale[1] = 0x800;
      inst->scale[2] = 0x800;
    }
	
	// this also quits the function
    ThTick_SetAndExec(t,func);
	return;
  }
  
  // === If not "thrown" ===
  
  // reduce cooldown
  mw->cooldown -= gGT->elapsedTimeMS;
  
  if(mw->cooldown < 0)
		mw->cooldown = 0;
  
  numFrames = INSTANCE_GetNumAnimFrames(inst,0);
  
  // if animation is not over
  if (inst->animFrame < numFrames-1) 
  {
	// increment animation frame
    inst->animFrame++;
  }
  // if animation is over
  else 
  {
	// restart animation
    inst->animFrame = 0;
  }
  
  // increment posY by velY * time
  // do NOT use parenthesis
  inst->matrix.t[1] += (mw->velocity[1] * gGT->elapsedTimeMS) >> 5;
  
  if (inst->matrix.t[1] < mw->stopFallAtY) {
    inst->matrix.t[1] = mw->stopFallAtY;
  }
  
  // decrease velocity by time, this is artificial gravity (negative acceleration)
  mw->velocity[1] -= ((gGT->elapsedTimeMS << 2) >> 5);
  
  // terminal velocity
  if(mw->velocity[1] < -0x60) mw->velocity[1] = -0x60;
  
  // If scale is not big enough
  if (inst->scale[0] < 0x1000) 
  {
	// make scale larger each frame
    inst->scale[0] += FPS_HALF(0x200);
    inst->scale[1] += FPS_HALF(0x200);
    inst->scale[2] += FPS_HALF(0x200);
  }
 
  param = 0x3840;

  // red beaker or green beaker
  if (boolPotion != 0) 
  {
    param = 0x1900;
  }
  
  coll = DECOMP_RB_Hazard_CollideWithDrivers(
	inst,mw->frameCount_DontHurtParent,param,mw->instParent);
  
  // if no collision
  if (coll == 0) goto LAB_800ad17c;
  
  // get driver who hit tnt (or nitro) 
  // from the object attached to thread
  d = coll->thread->object;
  
  if (((mw->crateInst != 0) && (mw->crateInst->thread != 0)) &&
     (mw->crateInst->thread->object != 0)) 
  {
    crate = mw->crateInst->thread->object;
    crate->boolPauseCooldown = 0;
  }

  // red beaker or green beaker
  if (boolPotion != 0)
  {
    // count times hit by motionless potion
    param = 2;

    // if fly-forward timer is still active
    if (mw->cooldown != 0)
    {
      // moving potion
      param = 4;
    }

    // spin driver
    coll = RB_Hazard_HurtDriver(d,1,mw->instParent->thread->object,param);
    
	// if collision, and if this was a red potion
	if ((coll != 0) && (mw->extraFlags & 1) != 0)
	{
		RB_RainCloud_Init(d);
	}
	
	// if this driver is not an AI
    if ((d->actionsFlagSet & 0x100000) == 0) 
	{
	  // current fade value (bright white)
	  gGT->pushBuffer[d->driverID].fadeFromBlack_currentValue = 0x1fff;
      
	  // desired fade value (neutral)
	  gGT->pushBuffer[d->driverID].fadeFromBlack_desiredResult = 0x1000;
      
	  // fade step
	  gGT->pushBuffer[d->driverID].fade_step = 0xff78;
	}
	
	// make player icon red
	// If this is a red beaker
    param = 0x1e;
	
	// green beaker
    if (model == 0x47) 
	{
	  // make player icon green
      param = -0x1e;
    }
	
LAB_800ace88:
    
	// set icon damage timer
	d->damageColorTimer = param;
	
LAB_800ad174:

    RB_GenericMine_ThDestroy(t,inst,mw);
  }
  
  // TNT/Nitro
  else
  {  
	// if driver->instTntRecv is valid
    if (d->instTntRecv!= NULL) 
	{
	  // blasted driver
      RB_Hazard_HurtDriver(d,2,0,2);
	  
	  // icon damage timer, draw icon as red
      d->damageColorTimer = 0x1e;
	  
	  // set scale (x, y, z) to zero
      d->instTntRecv->scale[0] = 0;
      d->instTntRecv->scale[1] = 0;
      d->instTntRecv->scale[2] = 0;
	  
	  // make invisible
	  d->instTntRecv->flags |= 0x80;
      
	  // this thread is now dead
      d->instTntRecv->thread->flags |= 0x800;
	  
	  // erase instTntRecv
      d->instTntRecv = 0;
	  
      goto LAB_800ad174;
    }
	
	// if driver has squished timer
    if (d->squishTimer != 0) 
	{
      RB_Hazard_HurtDriver(d,2,0,2);
      
	  param = 0x1e;
      goto LAB_800ace88;
    }
	
	// if model is Nitro
    if (model == 6) 
	{
      RB_Hazard_HurtDriver(d,2,mw->instParent->thread->object,2);
      
	  // Why does icon turn red in gameplay?
	  
	  // icon damage timer, draw icon as green
	  d->damageColorTimer = -0x1e;
	  
      goto LAB_800ad174;
    }
	
	// if model is TNT
    if (model == 0x27) 
	{
	  // RB_Hazard_HurtDriver (keep driving?)
      crate = RB_Hazard_HurtDriver(d,0,mw->instParent->thread->object,2);
      
	  if (crate == 0) goto LAB_800ad174;
	  
	  // if Instance has no InstDef,
	  // if this TNT is not part of the level,
	  // use existing thread
      if (inst->instDef == 0) 
	  {
		// icon damage timer, draw icon as red
       d->damageColorTimer = 0x1e;
		
		// give driver to tnt object
        mw->driverTarget = d;
		
		// driver -> instTntRecv
        d->instTntRecv = inst;
		
        DECOMP_RB_MinePool_Remove(mw);
		
		// play Hit TNT "bounce" sound
        PlaySound3D(0x50,inst);
		
        inst->bitCompressed_NormalVector_AndDriverIndex = 0;
        inst->flags |= 0x200;
        mw->velocity[1] = 0x30;
        mw->velocity[0] = 0;
        mw->velocity[2] = 0;
        mw->deltaPos[0] = 0;
        mw->deltaPos[1] = 0;
        mw->deltaPos[2] = 0;
        mw->stopFallAtY = 0x3fff;
		
        ThTick_SetAndExec(t,RB_TNT_ThTick_ThrowOnHead);
		return;
      }
	  
	  // if this TNT has an InstDef, then it is part of LEV,
	  // kill the old thread and birth a new one (why?)
      else 
	  {
		// DAT_800ab9fc
		// "tnt1"
		
		// create thread for TNT, get an Instance
        instCrate = INSTANCE_BirthWithThread(
			0x27,0,SMALL,MINE,RB_TNT_ThTick_ThrowOnHead,sizeof(struct MineWeapon),0);
		
		// get rotation of player and assign to tnt
        instCrate->matrix.m[0][0] = inst->matrix.m[0][0];
        instCrate->matrix.m[0][2] = inst->matrix.m[0][2];
        instCrate->matrix.m[1][1] = inst->matrix.m[1][1];
        instCrate->matrix.m[2][0] = inst->matrix.m[2][0];
		
		// finish last rotation variable
        instCrate->matrix.m[2][1] = inst->matrix.m[2][1];
        
		// X, Y, Z positions of TNT instanece
		instCrate->matrix.t[0] = inst->matrix.t[0];
        instCrate->matrix.t[1] = inst->matrix.t[1];
        instCrate->matrix.t[2] = inst->matrix.t[2];
		
        instCrate->thread->funcThDestroy = PROC_DestroyInstance;
		
        instCrate->thread->funcThCollide = DECOMP_RB_Hazard_ThCollide_Generic;
		
		// Get object from thread
        tnt = instCrate->thread->object;
		
        tnt->instParent= d->instSelf;
		
        tnt->frameCount_DontHurtParent = FPS_DOUBLE(10);
        tnt->boolDestroyed = 0;
        tnt->tntSpinY = 0;
        tnt->crateInst= 0;
        tnt->extraFlags = 0;
        
		// give driver to tnt object
		tnt->driverTarget = d;

		// stopFallAtY (where it explodes)
        tnt->stopFallAtY = inst->matrix.t[1];
		
		// driver -> instTntRecv
        d->instTntRecv = instCrate;
		
		// TNT bounce sound
        PlaySound3D(0x50,instCrate);
		
        instCrate->bitCompressed_NormalVector_AndDriverIndex = 0;
        instCrate->flags |= 0x200;
        tnt->velocity[0] = 0;
        tnt->velocity[1] = 0x30;
        tnt->velocity[2] = 0;
        tnt->deltaPos[0] = 0;
        tnt->deltaPos[1] = 0;
        tnt->deltaPos[2] = 0;
		
        DECOMP_RB_MinePool_Remove(mw);
		
		// set scale (x, y, z) to zero
        inst->scale[0] = 0;
        inst->scale[0] = 0;
        inst->scale[0] = 0;
		
		// make invisible
        inst->flags |= 0x80;
        
		// this thread is now dead
		t->flags |= 0x800;
      }
    }
  }
LAB_800ad17c:

  if (mw->frameCount_DontHurtParent != 0)
	  mw->frameCount_DontHurtParent--;
  
  // if mineWeapon->boolDestroyed == 0
  if (mw->boolDestroyed == 0) {
    return;
  }
  
  // if thread is dead, quit function
  // this is if GenericMine_ThDestroy already ran
  if ((t->flags & 0x800) != 0) {
    return;
  }
  
  // === If destroyed from MinePool overflow ===
  
  // instance -> model -> modelID
  model = inst->model->id;
  
  // if model is green or red beaker
  if (boolPotion != 0) 
  {
	// glass shatter sound
	PlaySound3D(0x3f,inst);
	
	RB_Explosion_InitPotion(inst);
  }
  
  else
  {
    // if model is TNT
	// tnt explosion sound
	param = 0x3d;
  
	// if model is Nitro
	if (model == 6) 
	{
		// glass shatter
		param = 0x3f;
	}
	
	// play sound
	PlaySound3D(param,inst);
  
	RB_Blowup_Init(inst);
  }
  
  // this thread is now dead
  t->flags |= 0x800;
  
  return;
}