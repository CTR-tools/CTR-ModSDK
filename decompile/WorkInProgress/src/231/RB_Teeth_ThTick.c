#include <common.h>

void RB_Teeth_BSP_Callback(struct ScratchpadStruct*,struct Thread*);

void DECOMP_RB_Teeth_ThTick(struct Thread* t)
{
  int iVar1;
  u_int flags;
  struct Teeth* teeth;
  struct Instance* inst;
  
  teeth = t->object;
  inst = t->inst;

  #define SPS \
	((struct ScratchpadStruct*)0x1f800108)
  
  // if door is not moving
  if (teeth->direction == 0) 
  {
	// if timer is zero
    if (teeth->timeOpen == 0) goto LAB_800b9ff8;
    
	// reduce timer by milliseconds
	iVar1 = teeth->timeOpen - sdata->gGT->elapsedTimeMS;
    
	// set new timer
	teeth->timeOpen = iVar1;
    
	// if timer is up
	if (iVar1 < 1) 
	{
	  // play sound
	  // teeth closing
      PlaySound3D(0x75,inst);
      
	  // timer is zero
	  teeth->timeOpen = 0;
	  
	  // door is closing
      teeth->direction = -1;
	  
      goto LAB_800b9fe8;
    }
  }
  
  // if door is moving
  else 
  {
	// modify animation index by direction
    inst->animFrame = inst->animFrame + teeth->direction;
	
    iVar1 = Instance_GetNumAnimFrames(inst,0);
	
	// if animation is not on last frame
    if ((int)inst->animFrame < iVar1) 
	{
	  // if animation when backwards past beginning
      if ((int)inst->animFrame < 0) 
	  {
		// set animation to beginning
        inst->animFrame = 0;
		
		// door is not moving
        teeth->direction = 0;
		
		// timer is zero
        teeth->timeOpen = 0;
		
		// remove access (enable collision)
        sdata->doorAccessFlags &= 0xfffffffe;
      }
    }
	
	// if animation is on last frame (or past)
    else 
	{
	  // set animation to last frame
      inst->animFrame = (short)iVar1 + -1;
	  
	  // door is not moving (fully open)
      teeth->direction = 0;
	  
	  // timer, 2 seconds 
      teeth->timeOpen = 0x780;
    }
LAB_800b9fe8:
    if (teeth->timeOpen == 0) {
LAB_800b9ff8:
      if (-1 < teeth->direction) goto LAB_800ba084;
    }
  }
  
  // Teeth instance position
  SPS->Input1.pos[0] = inst->matrix.t[0];
  SPS->Input1.pos[1] = inst->matrix.t[1];
  SPS->Input1.pos[2] = inst->matrix.t[2];
  
  SPS->Input1.hitRadius = 0x300;
  SPS->Input1.hitRadiusSquared = 0x90000;
  
  SPS->Input1.modelID = 0x70;
  
  SPS->Union.ThBuckColl.thread = t;
  SPS->Union.ThBuckColl.funcCallback = RB_Teeth_BSP_Callback;
  
  // If door wants to close, but Player or Mine
  // is in the way, then do not force the doors to close
  
  THREAD_CollideHitboxWithBucket(sdata->gGT->threadBuckets[PLAYER],SPS,0);
  
  THREAD_CollideHitboxWithBucket(sdata->gGT->threadBuckets[MINE],SPS,0);
  
LAB_800ba084:

  // if no timer exists
  // (opening, closing, or full closed)
  if (teeth->timeOpen == 0) 
  {
	// make visible
	flags = inst->flags & 0xffffff7f;
  }

  // if a timer is active
  // (fully open)
  else 
  {
	// make invisible
    flags = inst->flags | 0x80;
  }

  inst->flags = flags;
  
  return;
}
 