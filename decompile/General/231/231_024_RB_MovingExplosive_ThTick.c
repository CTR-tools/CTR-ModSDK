#include <common.h>

// function for moving bomb, shiledbomb, or missile
void DECOMP_RB_MovingExplosive_ThTick(struct Thread* t)
{
  short sVar1;
  short sVar3;
  struct GameTracker* gGT = sdata->gGT;
  short modelID;
  int iVar6;
  int iVar8;
  unsigned short sound;
  struct TrackerWeapon* tw;
  struct Instance* inst;
  short posA[3];
  short posB[3];

  inst = t->inst;
  modelID = inst->model->id;

  tw = t->object;
  tw->timeAlive += gGT->elapsedTimeMS;

#ifndef REBUILD_PS1
  if (modelID == DYNAMIC_ROCKET)
  {
    if ((t->flags & 0x800) == 0) {
      sound = 0x4b;
      goto LAB_800adc00;
    }
  }
  else
  {
    if (modelID == DYNAMIC_BOMB)
	{
      sound = 0x48;
    }
    else
	{
      if (
			(modelID != DYNAMIC_SHIELD) &&
			(modelID != DYNAMIC_SHIELD_GREEN)
		)
		goto LAB_800adc08;

	  // if model is blue or green shield
      sound = 0x59;
    }
LAB_800adc00:
    PlaySound3D_Flags(&tw->audioPtr,sound,inst);
  }
#endif

LAB_800adc08:;

  struct Driver* driverTarget =
	tw->driverTarget;

  // driver not invisible
  if (
		(driverTarget != 0) &&
		(driverTarget->invisibleTimer == 0)
	  )
  {
    if (
			// Naughty Dog Bug? That's so unlikely?
			// Literally a ONE-frame window

			// dropped mine previous frame
			(driverTarget->actionsFlagSetPrevFrame < 0) &&

			(modelID == DYNAMIC_ROCKET)
		)
	{
      tw->framesSeekMine = FPS_DOUBLE(10);
    }
  }

  // if driver is invisible
  else
  {
	// erase pointer to driver,
	// cause tracker can't find invisible driver
    tw->driverTarget = 0;
  }

  driverTarget = tw->driverTarget;

  if (
		// if driver is invalid
		(driverTarget == 0) ||
		(tw->frameCount_Blind != 0)
	 )
  {
    if (tw->frameCount_Blind != 0)
		tw->frameCount_Blind--;
  }
  else
  {
    if (tw->framesSeekMine == 0)
	{
	  // get distance between tracker and the driver being chased
      iVar6 = (driverTarget->posCurr.x >> 8) - inst->matrix.t[0];
      iVar8 = (driverTarget->posCurr.z >> 8) - inst->matrix.t[2];
      tw->distanceToTarget = iVar6 * iVar6 + iVar8 * iVar8;

LAB_800add14:

	  // get direction, given X and Y distance to travel
      sVar3 = ratan2(iVar6,iVar8);
    }

	// if seeking mine
	else
	{
      tw->framesSeekMine--;

	  // if target shot a TNT
      struct Instance* instTNT =
		tw->driverTarget->instTntSend;

	  if (instTNT != 0)
	  {
		// Get X and Y differences between two instances
        iVar6 = instTNT->matrix.t[0] - inst->matrix.t[0];
        iVar8 = instTNT->matrix.t[1] - inst->matrix.t[2];
        goto LAB_800add14;
      }

	  // if target never used a TNT
      sVar3 = tw->rotY;
      tw->framesSeekMine = 0;
    }

	if (
			(modelID == DYNAMIC_BOMB) ||
			(modelID == DYNAMIC_SHIELD)
		)
	{
      tw->rotY =
		DECOMP_RB_Hazard_InterpolateValue(
			tw->rotY,(int)sVar3,4);

	  tw->vel[0] = (DECOMP_MATH_Sin(tw->rotY) * 3) >> 7;
	  tw->vel[2] = (DECOMP_MATH_Cos(tw->rotY) * 3) >> 7;

	  // if bomb is rolled backwards
	  if ((tw->flags & 0x20) != 0)
	  {
        tw->vel[2] = -tw->vel[2];
        tw->vel[0] = -tw->vel[0];
      }
    }

	// if 0x29 (MISSILE)
    else
	{
	  // if 10 wumpa were not used
      if ((tw->flags & 1) == 0)
	  {
		tw->rotY =
			DECOMP_RB_Hazard_InterpolateValue(
				tw->rotY,(int)sVar3,0x40);

		tw->vel[0] = (DECOMP_MATH_Sin(tw->rotY) * 5) >> 8;
		tw->vel[2] = (DECOMP_MATH_Cos(tw->rotY) * 5) >> 8;
      }

	  // if 10 wumpa were used
      else
	  {
		tw->rotY =
			DECOMP_RB_Hazard_InterpolateValue(
				tw->rotY,(int)sVar3,0x80);

		tw->vel[0] = (DECOMP_MATH_Sin(tw->rotY) * 3) >> 7;
		tw->vel[2] = (DECOMP_MATH_Cos(tw->rotY) * 3) >> 7;
      }

      tw->dir[0] = 0;
      tw->dir[2] = 0;
      tw->dir[1] = tw->rotY;

	   // convert 3 rotation shorts into rotation matrix
      ConvertRotToMatrix(&inst->matrix,&tw->dir);
    }
  }

  sVar3 = inst->animFrame;
  iVar8 = DECOMP_INSTANCE_GetNumAnimFrames(inst,0);

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

#ifndef REBUILD_PS1
  if (
		// if missile
		(modelID == DYNAMIC_ROCKET) &&

		// numPlyrCurrGame < 2
		(sdata->gGT->numPlyrCurrGame < 2)
	 )
  {
	// Make Instane in Particle Pool
	struct Particle* p;
	p = Particle_Init(0,gGT->iconGroup[0],0x800b2ae4);

	if(p!=0)
	{
		p->axis[0].startVal = inst->matrix.t[0] << 8;
		p->axis[1].startVal = inst->matrix.t[1] << 8;
		p->axis[2].startVal = inst->matrix.t[2] << 8;
	}
  }
#endif

  int elapsedTime = gGT->elapsedTimeMS;
  inst->matrix.t[0] += (((int)tw->vel[0] * elapsedTime) >> 5);
  inst->matrix.t[1] += (((int)tw->vel[1] * elapsedTime) >> 5);
  inst->matrix.t[2] += (((int)tw->vel[2] * elapsedTime) >> 5);

  // If this is bomb
  if (modelID == 0x3b)
  {
	// if bomb is forwards
	if ((tw->flags & 0x20) == 0)
	{
	  tw->dir[0] += FPS_HALF(0x200);
    }

	// if bomb is backwards
	else
	{
	  tw->dir[0] -= FPS_HALF(0x200);
    }

	 // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&inst->matrix,&tw->dir);
  }

  posA[0] = inst->matrix.t[0];
  posA[1] = inst->matrix.t[1] + -0x40;
  posA[2] = inst->matrix.t[2];

  posB[0] = inst->matrix.t[0];
  posB[1] = inst->matrix.t[1] + 0x100;
  posB[2] = inst->matrix.t[2];

#ifndef REBUILD_PC
  struct ScratchpadStruct* sps = 0x1f800108;

  sps->Union.QuadBlockColl.searchFlags = 0x41;
  sps->Union.QuadBlockColl.qbFlagsWanted = 0x1040;
  sps->Union.QuadBlockColl.qbFlagsIgnored = 0;

  if (gGT->numPlyrCurrGame < 3) {
    sps->Union.QuadBlockColl.searchFlags = 0x43;
  }

  sps->ptr_mesh_info = gGT->level1->ptr_mesh_info;

  COLL_SearchTree_FindQuadblock_Touching(&posA,&posB,sps,0);

  RB_MakeInstanceReflective(sps,inst);

  if ((*(int*)&sps->dataOutput[0] & 4) != 0)
  {
	// move backward one frame
	tw->vel[0] = -tw->vel[0];
    tw->vel[1] = -tw->vel[1];
    tw->vel[2] = -tw->vel[2];

    inst->matrix.t[0] += ((int)tw->vel[0] * elapsedTime) >> 5;
	inst->matrix.t[1] += ((int)tw->vel[1] * elapsedTime) >> 5;
	inst->matrix.t[2] += ((int)tw->vel[2] * elapsedTime) >> 5;

	DECOMP_RB_MovingExplosive_Explode(t,inst,tw);
    return;
  }

  if (sps->boolDidTouchHitbox == 0)
  {
    if (sps->boolDidTouchQuadblock == 0)
	{
	  // if no quadblock is under this item,
	  // look again for another quadblock LOWER

      inst->vertSplit = 0;
      posA[0] = inst->matrix.t[0];
      posA[1] = inst->matrix.t[1] - 0x900;
      posA[2] = inst->matrix.t[2];

      COLL_SearchTree_FindQuadblock_Touching(&posA,&posB,sps,0);

	  // if still nothing, then explode
      if (sps->boolDidTouchQuadblock == 0)
			goto LAB_800ae42c;

	  // if quadblock under,
	  // then set fall rate and fall

      int iVar8 = elapsedTime << 2;

	  // if missile
      if (modelID == 0x29)
	  {
        iVar8 = elapsedTime << 3;
      }

	  tw->vel[1] -= (iVar8 >> 5);

	  if (tw->vel[1] < -0x60)
	  {
		  tw->vel[1] = -0x60;
	  }
    }

	// if hit quadblock
    else
	{
      tw->vel[1] = 0;

	  // DYNAMIC_ROCKET
      if (modelID == 0x29)
	  {
        VehPhysForce_RotAxisAngle(
			&inst->matrix,
			&sps->unk4C[0x24], // normalVec
			tw->rotY);
      }

	  // position
      inst->matrix.t[0] = sps->Union.QuadBlockColl.hitPos[0];
      inst->matrix.t[1] = sps->Union.QuadBlockColl.hitPos[1] + 0x30;
      inst->matrix.t[2] = sps->Union.QuadBlockColl.hitPos[2];
    }
  }
  else
  {
    sps->Input1.modelID = modelID;

	int ret;
    ret = RB_Hazard_CollLevInst(sps,t);

	// if hit bsp hitbox
	if (ret == 1)
	{
	  struct InstDef* instDef;
	  struct BSP* bspHitbox = sps->bspHitbox;

	  // copy/paste from Potion_InAir
      if (
			(
				((bspHitbox->flag & 0x80) != 0) &&
				(
					instDef = bspHitbox->data.hitbox.instDef,
					instDef != 0
				)
			) &&

			(
				(
					(instDef->ptrInstance != 0) &&
					(instDef->modelID == 0x70)
				)
			)
		)
	  {
        DECOMP_RB_Teeth_OpenDoor(instDef->ptrInstance);
      }
      goto LAB_800ae42c;
    }
  }

#endif

  struct Instance* hitInst;

  hitInst = DECOMP_RB_Hazard_CollideWithDrivers(
	inst,
	tw->frameCount_DontHurtParent,
	0x2400,
	tw->instParent);

  // if no driver hit
  if (hitInst == 0)
  {
	// check Mine threadbucket
    hitInst = DECOMP_RB_Hazard_CollideWithBucket(
		inst, t,
		gGT->threadBuckets[MINE].thread,
        tw->frameCount_DontHurtParent,
		0x2400,
		tw->instParent);

	// if mine was not hit
	if (hitInst == 0)
	{
	  // instance -> model -> modelID is not bomb
	  if (modelID != 0x3b) {
LAB_800ae440:
        if (tw->frameCount_DontHurtParent != 0)
			tw->frameCount_DontHurtParent--;

        return;
      }

	  // === Assume Bomb ===

	  // check Tracking threadbucket
	  hitInst = DECOMP_RB_Hazard_CollideWithBucket(
		inst, t,
		gGT->threadBuckets[TRACKING].thread,
        tw->frameCount_DontHurtParent,
		0x2400,
		tw->instParent);

	  // if no collision
	  if (hitInst == 0) {
        if ((tw->flags & 2) == 0) goto LAB_800ae440;
      }

	  // if bomb collides with Tracker
	  else
	  {
		// not a missile
        if (hitInst->model->id != 0x29)
		{
		  // quit, warpball collisions dont matter
          return;
        }

		// === missile ===
		struct Thread* hitTh =
			hitInst->thread;

		hitTh->funcThCollide(hitTh);
      }
    }

	// if mine was hit
	else
	{
		struct Thread* hitTh =
			hitInst->thread;

		hitTh->funcThCollide(hitTh);
    }
  }

  // if driver was hit
  else
  {
	struct Thread* hitTh =
		hitInst->thread;

	struct Driver* hitD =
		hitTh->object;

	hitD->damageColorTimer = 0x1e;

    if (hitD == tw->driverTarget)
	{
	  // flags
      tw->flags |= 0x10;
    }
  }
LAB_800ae42c:

  DECOMP_RB_MovingExplosive_Explode(t,inst,tw);
  return;
}
