#include <common.h> 

// function for moving bomb, shiledbomb, or missile
void DECOMP_RB_MovingExplosive_ThTick(struct Thread* t)
{
  short sVar1;
  struct GameTracker* gGT = sdata->gGT;
  short sVar3;
  code *pcVar4;
  undefined2 uVar5;
  int iVar6;
  unsigned short uVar7;
  struct Driver* iVar8;
  struct TrackerWeapon* tw;
  struct Instance* inst;
  short posA[3];
  short posB[3];

  // get instance from thread
  inst = t->inst;
  
  // get object, from thread, from instance
  tw = inst->thread->object;
  
  tw->vel[1] += gGT->elapsedTimeMS;
  
  // instance -> model -> modelID
  sVar3 = inst->model->id;
  
  // if model is missile
  if (sVar3 == 0x29) 
  {
    if ((t->flags & 0x800) == 0) {
      uVar7 = 0x4b;
      goto LAB_800adc00;
    }
  }
  else 
  {
	// if model is bomb
    if (sVar3 == 0x3b) 
	{
      uVar7 = 0x48;
    }
    else 
	{
	  // if model is not blue or green shield
      if ((sVar3 != 0x56) && (sVar3 != 0x5e)) goto LAB_800adc08;
	  
	  // if model is blue or green shield
      uVar7 = 0x59;
    }
LAB_800adc00:

    PlaySound3D_Flags(tw->audioPtr,uVar7,inst);
  }
LAB_800adc08:

  if (tw->driverParent->invisibleTimer == 0) 
  {
    if (
			(tw->driverParent->actionsFlagSetPrevFrame < 0) && 
			
			// missile
			(sVar3 == 0x29)
		) 
	{
      tw[0x15] = 10;
    }
  }
  
  // if driver is invisible
  else 
  {
	// erase pointer to driver,
	// cause tracker can't find invisible driver
    tw->driverTarget = 0;
  }
  
  // "tracker" can be missile, bomb, or shield
  
  // get driver the tracker is chasing
  iVar8 = tw->driverTarget;
  
  if (
		// if driver is invalid
		(iVar8 == 0) || 
		(tw->data4[2] != 0)
	 ) 
  {
    if (tw->data4[2] != 0) {
      tw->data4[2] = tw->data4[2] + -1;
    }
  }
  else {
    if (tw[0x15] == 0) 
	{
	  // get distance between tracker and the driver being chased
      iVar6 = (*(int *)(iVar8 + 0x2d4) >> 8) - inst->matrix.t[0];
      iVar8 = (*(int *)(iVar8 + 0x2dc) >> 8) - inst->matrix.t[2];
      tw[10] = iVar6 * iVar6 + iVar8 * iVar8;
	  
LAB_800add14:

	  // get direction, given X and Y distance to travel
      sVar3 = ratan2(iVar6,iVar8);
    }
    else {
      tw[0x15] = tw[0x15] + -1;
      iVar8 = *(int *)(*tw + 0x20);
      if (iVar8 != 0) 
	  {
		// Get X and Y differences between two instances
        iVar6 = *(int *)(iVar8 + 0x44) - inst->matrix.t[0];
        iVar8 = *(int *)(iVar8 + 0x4c) - inst->matrix.t[2];
        goto LAB_800add14;
      }
      sVar3 = *(short *)((int)tw + 0x1e);
      tw[0x15] = 0;
    }
    
	// instance -> model -> modelID
	sVar1 = inst->model->id;
    
	// DYNAMIC_BOMB or DYNAMIC_SHIELD
	if ((sVar1 == 0x3b) || (sVar1 == 0x56)) 
	{
	  // 
      sVar3 = RB_Hazard_InterpolateValue((int)*(short *)((int)piVar9 + 0x1e),(int)sVar3,4);  
	  *(short *)((int)tw + 0x1e) = sVar3;
      
	  // Sine(angle)
	  iVar8 = MATH_SIN((int)sVar3);
      
	  // posX += velocity >> 7
	  tw->vel[0] = (short)((unsigned int)(iVar8 * 3) >> 7);
      
	  // Cosine(angle)
	  iVar8 = MATH_Cos((int)*(short *)((int)tw + 0x1e));
      
	  // posZ += velocity >> 7
	  sVar3 = (short)((unsigned int)(iVar8 * 3) >> 7);
	  tw->vel[2] = sVar3;
      
	  // if bomb is rolled backwards
	  if ((tw->flags & 0x20) != 0) {
        tw->vel[2] = -sVar3;
        tw->vel[0] = -tw->vel[0];
      }
    }
	
	// if 0x29 (MISSILE)
    else 
	{
	  // if 10 wumpa were not used
      if ((tw->flags & 1) == 0) 
	  {
		// 
        sVar3 = RB_Hazard_InterpolateValue((int)*(short *)((int)piVar9 + 0x1e),(int)sVar3,0x40);  
		*(short *)((int)tw + 0x1e) = sVar3;
        
		// Sine(angle)
		iVar8 = MATH_SIN((int)sVar3);
        
		// posX += velocity >> 8
		tw->vel[0] = (short)((unsigned int)(iVar8 * 5) >> 8);
        
		// Cosine(angle)
		iVar8 = MATH_Cos((int)*(short *)((int)tw + 0x1e));
        
		// posZ += velocity >> 8
		uVar5 = (undefined2)((unsigned int)(iVar8 * 5) >> 8);
      }
	  
	  // if 10 wumpa were used
      else 
	  {
		// 
        sVar3 = RB_Hazard_InterpolateValue((int)*(short *)((int)piVar9 + 0x1e),(int)sVar3,0x80);
		*(short *)((int)tw + 0x1e) = sVar3;
        
		// Sine(angle)
		iVar8 = MATH_SIN((int)sVar3);
        
		// posX += velocity >> 7
		tw->vel[0] = (short)((unsigned int)(iVar8 * 3) >> 7);
        
		// Cosine(angle)
		iVar8 = MATH_Cos((int)*(short *)((int)tw + 0x1e));
        
		// posZ += velocity >> 7
		uVar5 = (undefined2)((unsigned int)(iVar8 * 3) >> 7);
      }
	  
	  // posZ += velocity
      tw->vel[2] = uVar5;
	  
      tw->dir[0] = 0;
      tw->dir[2] = 0;
      tw->dir[1] = *(short *)((int)tw + 0x1e);
	  
	   // convert 3 rotation shorts into rotation matrix
      ConvertRotToMatrix(&inst->matrix,&tw->dir);
    }
  }
  
  sVar3 = inst->animFrame;
  
  iVar8 = INSTANCE_GetNumAnimFrames(inst,0);
  
  // if instance is not at end of animation
  if ((int)sVar3 + 1 < iVar8) 
  {
	// increment animation frame
    inst->animFrame += 1;
  }
  
  // if animation finished
  else 
  {
	// go back to first frame of animation
    inst->animFrame = 0;
  }
  
  if (
		(
			// if missile
			(inst->model->id == 0x29) && 
			
			// numPlyrCurrGame < 2
			(sdata->gGT->numPlyrCurrGame < 2)
		) && 
		(
			// Make Instane in Particle Pool
			iVar8 = Particle_Init(0,(gGT + 0x2114),0x800b2ae4),
			iVar8 != 0
		)
	 ) 
  {
	// Position in a particle struct
	  
    *(int *)(iVar8 + 0x24) = inst->matrix.t[0] << 8;
    *(int *)(iVar8 + 0x2c) = inst->matrix.t[1] << 8;
    *(int *)(iVar8 + 0x34) = inst->matrix.t[2] << 8;
  }
  
  // posX
  inst->matrix.t[0] += ((int)tw->vel[0] * gGT->elapsedTimeMS >> 5);
  
  // posY
  inst->matrix.t[1] += ((int)tw->vel[1] * gGT->elapsedTimeMS >> 5);
  
  // posZ
  inst->matrix.t[2] += ((int)tw->vel[2] * gGT->elapsedTimeMS >> 5);
  
  // If this is bomb
  if (inst->model->id == 0x3b) 
  {  
	// if bomb is forwards
	if ((tw->flags & 0x20) == 0) 
	{
	  // rotation
      sVar3 = tw->dir[0] + 0x200;
    }
    
	// if bomb is backwards
	else 
	{
	  // rotation
      sVar3 = tw->dir[0] + -0x200;
    }
	
	// rotation
    tw->dir[0] = sVar3;
	
	 // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&inst->matrix,&tw->dir);
  }
  
  posA[0] = inst->matrix.t[0];
  posA[1] = inst->matrix.t[1] + -0x40;
  posA[2] = inst->matrix.t[2];
  posB[0] = inst->matrix.t[0];
  posB[1] = inst->matrix.t[1] + 0x100;
  posB[2] = inst->matrix.t[2];
  DAT_1f80012c = 0x1040;
  DAT_1f800130 = 0;
  DAT_1f80012a = 0x41;
  
  if (gGT->numPlyrCurrGame < 3) {
    DAT_1f80012a = 0x43;
  }
  
  DAT_1f800134 = gGT->level1;
  
  COLL_SearchTree_FindQuadblock_Touching(&posA,&posB,&DAT_1f800108,0);
  
  RB_MakeInstanceReflective(&DAT_1f800108,inst);
  
  if ((DAT_1f8002ac & 4) != 0) 
  {
	// negate velocity in all directions
    tw->vel[0] = -tw->vel[0];
    tw->vel[1] = -tw->vel[1];
    tw->vel[2] = -tw->vel[2];
	
	// posX += -VelX
    inst->matrix.t[0] += (int)tw->vel[0] * gGT->elapsedTimeMS >> 5;
    
	// posY += -VelY
	inst->matrix.t[1] += (int)tw->vel[1] * gGT->elapsedTimeMS >> 5;
    
	// posZ += -VelZ
	inst->matrix.t[2] += (int)tw->vel[2] * gGT->elapsedTimeMS >> 5;

	RB_MovingExplosive_Explode(t,inst,tw);
    return;
  }
  
  if (DAT_1f80014a == 0) {
    if (DAT_1f800146 == 0) 
	{
	  // hitbox
      inst->vertSplit = 0;
      posA[0] = inst->matrix.t[0];
      posA[1] = inst->matrix.t[1] + -0x900;
      posA[2] = inst->matrix.t[2];
	  
      COLL_SearchTree_FindQuadblock_Touching(&posA,&posB,&DAT_1f800108,0);
	  
      if (DAT_1f800146 == 0) goto LAB_800ae42c;
      iVar8 = gGT->elapsedTimeMS << 2;
	  
	  // if missile
      if (inst->model->id == 0x29) 
	  {
        iVar8 = gGT->elapsedTimeMS << 3;
      }
      
	  iVar8 = tw->vel[1] - (iVar8 >> 5);
       tw->vel[1] = (short)iVar8;


      if (iVar8 < -0x60) {
        tw->vel[1] = 0xffa0;
      }
    }
    else {
      tw->vel[1] = 0;
	  
	  // DYNAMIC_ROCKET
      if (inst->model->id == 0x29) 
	  {
        VehPhysForce_RotAxisAngle(&inst->matrix,&DAT_1f800178,(int)*(short *)((int)tw + 0x1e));
      }
	  
	  // position
      inst->matrix.t[0] = (int)(short)DAT_1f800124;
      inst->matrix.t[1] = (int)DAT_1f800124._2_2_ + 0x30;
      inst->matrix.t[2] = (int)DAT_1f800128;
    }
  }
  else 
  {
	// if instance -> model -> modelID
    DAT_1f800114 = inst->model->id;
	
    iVar8 = RB_Hazard_CollLevInst(&DAT_1f800108,t);
    
	// if hit bsp hitbox
	if (iVar8 == 1) 
	{
	  // copy/paste from Potion_InAir
      if ((((*DAT_1f800150 & 0x80) != 0) && (iVar8 = *(int *)(DAT_1f800150 + 0x1c), iVar8 != 0)) &&
         ((*(int *)(iVar8 + 0x2c) != 0 && (*(short *)(iVar8 + 0x3c) == 0x70)))) 
	  {
        RB_Teeth_OpenDoor(*(int *)(iVar8 + 0x2c));
      }
      goto LAB_800ae42c;
    }
  }
  
  iVar8 = RB_Hazard_CollideWithDrivers(inst,(int)tw->data4[0],0x2400,tw->instParent);
  
  // if no driver hit
  if (iVar8 == 0) 
  {
	// check Mine threadbucket
    iVar8 = RB_Hazard_CollideWithBucket(inst,t,gGT->threadBuckets[4].thread,
                       (int)tw->data4[0],0x2400,tw->instParent);
    
	// if mine was not hit
	if (iVar8 == 0) {
      
	  // instance -> model -> modelID is not bomb
	  if (inst->model->id != 0x3b) {
LAB_800ae440:
        if (tw->data4[0] == 0) {
          return;
        }
        tw->data4[0] += -1;
        return;
      }
      
	  // if you are here, this must be a bomb
	  
	  // check Tracking threadbucket
	  iVar8 = RB_Hazard_CollideWithBucket(inst,t,gGT->threadBuckets[6].thread,
                         (int)tw->data4[0],0x2400,tw->instParent);
      
	  // if no collision
	  if (iVar8 == 0) {
        if ((tw->flags & 2) == 0) goto LAB_800ae440;
      }
      
	  // if bomb collides with Tracker
	  else 
	  {
		// not a missile
        if (inst->model->id != 0x29) 
		{
		  // quit, warpball collisions dont matter
          return;
        }
		
		// this must be a missile
		
		// instance -> thread -> funcThCollide
        pcVar4 = *(code **)(*(int *)(iVar8 + 0x6c) + 0x28);
		
		// execute funcThCollide
        (*pcVar4)(*(int *)(iVar8 + 0x6c),t,pcVar4,0);
      }
    }
    
	// if mine was hit
	else 
	{
	  // instance -> thread -> funcThCollide
      pcVar4 = *(code **)(*(int *)(iVar8 + 0x6c) + 0x28);
	  
	  // execute funcThCollide
      (*pcVar4)(*(int *)(iVar8 + 0x6c),t,pcVar4,0);
    }
  }
  
  // if driver was hit
  else {
    
	((struct Driver*)t->object)->damageColorTimer = 0x1e;
	
    if (((struct Driver*)t->object) == tw->driverTarget) 
	{
	  // flags
      tw->flags |= 0x10;
    }
  }
LAB_800ae42c:

  RB_MovingExplosive_Explode(t,inst,tw);
  return;
}
 