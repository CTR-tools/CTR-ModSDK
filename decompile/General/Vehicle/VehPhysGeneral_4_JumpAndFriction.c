#include <common.h>

#define gte_ldVXY0(r0) __asm__ volatile("mtc2   %0, $0" \
                                        :               \
                                        : "r"(r0))
#define gte_ldVZ0(r0) __asm__ volatile("mtc2   %0, $1" \
                                       :               \
                                       : "r"(r0))
#define read_mt(r0, r1, r2) __asm__ volatile( \
    "mfc2   %0, $25;"                         \
    "mfc2   %1, $26;"                         \
    "mfc2   %2, $27;"                         \
    :                                         \
    : "r"(r0), "r"(r1), "r"(r2))

void DECOMP_VehPhysGeneral_JumpAndFriction(struct Thread *t, struct Driver *d)
{
  char uVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  unsigned int uVar10;
  unsigned int uVar11;
  unsigned int uVar12;
  int iVar13;
  unsigned int uVar14;
  int param_1;
  int param_2;
  int param_3;
  VECTOR movement;
  int jumpForce;
  
  uVar12 = d;
  gte_SetRotMatrix(&d->matrixMovingDir);
    
  if (
		(d->kartState != KS_DRIFTING) &&
		((d->actionsFlagSet & 0x800000) == 0) &&
		(d->reserves == 0)
	 )
  {
    short ampTurnState = (short)d->ampTurnState >> 8;
    if (ampTurnState < 0)
    {
      ampTurnState = -ampTurnState;
    }
	
    param_1 = DECOMP_VehCalc_MapToRange(ampTurnState, 0, d->const_BackwardTurnRate, 0, d->const_TurnDecreaseRate);
    
	param_3 = d->baseSpeed;
    
	iVar9 = param_3;
    if (param_3 < 0) {
      iVar9 = -param_3;
    }
    if (iVar9 < param_1) {
      param_1 = iVar9;
    }
    sVar7 = (short)param_1;
    sVar3 = -sVar7;
    if (param_3 < 0) {
      param_1 = -param_1;
      sVar3 = sVar7;
    }
    d->baseSpeed = d->baseSpeed + sVar3;
  }
  
  if (d->set_0xF0_OnWallRub != 0) 
  {
    if (d->baseSpeed > d->scrubMeta8)
		d->baseSpeed = d->scrubMeta8;

	if (d->baseSpeed < -d->scrubMeta8) 
		d->baseSpeed = -d->scrubMeta8;
  }
  
  movement.vx = d->velocity.x;
  movement.vy = d->velocity.y;
  movement.vz = d->velocity.z;
  
  uVar14 = 0;
  iVar9 = 0;
  
  if ((d->actionsFlagSet & 1) == 0) 
  {

CHECK_FOR_ANY_JUMP:

// UNUSED Spring Weapon
#if 0
    // If you want to fire a weapon
    if (((d->actionsFlagSet & 0x8000) != 0) &&

        // If that weapon is a spring
        (d->heldItemID == 5))
    {      
	  // Remove the request to fire a weapon, since we will use it now
      d->actionsFlagSet &= ~(0x8000);
	  
      // if coyoteTimerMS has not expired, and cooldownMS is over
      if ((d->jump_CoyoteTimerMS != 0) && (d->jump_CooldownMS == 0))
	  {
        // driver is now forced to jump
        d->jump_ForcedMS = 0xa0;
		
		// const 2.25x
        jumpForce = d->const_JumpForce * 9;
        d->jump_InitialVelY = (short)(jumpForce >> 2);
		
		// spring weapon sound
        OtherFX_Play_Echo(9, 1, d->actionsFlagSet & 0x10000);
		
		d->jump_unknown = 0x180;
        goto PROCESS_JUMP;
      }
      d->noItemTimer = 0;
    }
#endif
	
    // if not being forced to jump (turtles), this should cause the tiny jumps on top of walls.
    if (d->forcedJump_trampoline == 0)
    {
      if (
			// if driver left quadblock more than 0.16s ago
			(d->jump_CoyoteTimerMS == 0) ||

			// if haven't jumped in last 10 frames
			(d->jump_TenBuffer == 0) ||

			// jump_CooldownMS not over (so can't jump again)
			(d->jump_CooldownMS != 0)
		  )
      {
        if ((d->actionsFlagSet & 1) != 0) 
		{
          if (
				(d->underDriver != 0) &&
				(
					iVar9 = d->underDriver->mulNormVecY, 
					iVar9 != 0
				)
			 ) 
		  {
            iVar13 = (int)d->speedApprox;
            if (iVar13 < 0) {
              iVar13 = -iVar13;
            }
            gte_ldVXY0((iVar9 * iVar13 >> 8) << 0x10);
            gte_ldVZ0(0);
            gte_rtv0();
			
			int temp;
            read_mt(iVar9,temp,param_3);
            movement.vx += iVar9;
            movement.vy += temp;
            movement.vz += param_3;
          }
        }
        goto NOT_JUMPING;
      }
	  
      // force driver to jump
      d->jump_ForcedMS = 0xa0;

      // increment jump counter
      d->numberOfJumps++;

	  // const 1.0x
      d->jump_InitialVelY = d->const_JumpForce;

      // play jump sound
      DECOMP_OtherFX_Play_Echo(8, 1, d->actionsFlagSet & 0x10000);
    }
    
	// if being forced to jump (by turtles)
	else 
	{
      // if first frame (basically)
      if (
          // if not currently airborne from forced jump
          (d->jump_ForcedMS == 0) ||

          // if jump_InitialVelY was just now set to const_jump
          (d->jump_InitialVelY == d->const_JumpForce))
      {
        DECOMP_OtherFX_Play(0x7e,1);
      }
	        
	  // currently forced airborne
      d->jump_ForcedMS = 0xa0;
	  
	  jumpForce = d->const_JumpForce * 3;
	  
      // if big force jump (turtles)
      if (d->forcedJump_trampoline == 2)
      {
		d->jump_unknown = 0x180;
		
		// const 3.0x
		d->jump_InitialVelY = jumpForce;
      }
	  
      else 
	  {
		// const 1.5x
        d->jump_InitialVelY = jumpForce >> 1;
      }
	  
      // remove force jump (turtles)
      d->forcedJump_trampoline = 0;
    }
  }
  
  // ((d->actionsFlagSet & 1) == 1)
  else {
    if (((d->stepFlagSet & 3) == 0) || (d->baseSpeed < 1)) 
	{
      if (d->baseSpeed != 0) 
	  {
        if ((((d->terrainMeta1->flags & 4) == 0) ||
            (d->baseSpeed < 1)) || (-1 < d->speedApprox)) 
		{
          iVar8 = (int)d->speedApprox;
          iVar13 = iVar8;
          if (iVar8 < 0) {
            iVar13 = -iVar8;
          }
          if (((0x2ff < iVar13) && ((d->baseSpeed < 1 || (iVar8 < 1)))) &&
             ((-1 < d->baseSpeed || (-1 < iVar8)))) goto PROCESS_ACCEL;
        }
		
        iVar9 = d->const_Accel_ClassStat + ((int)d->accelConst << 5) / 5;
		
        if ((d->stepFlagSet & 3) == 0) 
		{
          if ((d->reserves != 0) && (0 < d->baseSpeed)) 
		  {
            iVar9 = d->const_Accel_Reserves;
          }
          
		  param_1 = d->terrainMeta1->slowUntilSpeed;
          if ((param_1 != 0x100) && ((d->actionsFlagSet & 0x800000) == 0)) 
		  {
            iVar9 = param_1 * iVar9 >> 8;
          }
        }
        else if (0 < d->baseSpeed) goto SET_HIGH_ACCEL;
      }
    }
    else {
SET_HIGH_ACCEL:
      iVar9 = 8000;
    }
PROCESS_ACCEL:
    uVar10 = (iVar9 * sdata->gGT->elapsedTimeMS) >> 5;
    gte_ldVXY0(0);
    gte_ldVZ0(uVar10 & 0xffff);
    gte_rtv0();
    read_mt(param_1,param_2,param_3);
	
    if (d->baseSpeed < 0) {
      d->unk_offset3B2 = -(short)uVar10;
	  
	  movement.vx -= param_1;
	  movement.vy -= param_2;
	  movement.vz -= param_3;
	  
	  // unused?
	  #if 0
      d->unkVectorX = -(short)param_1;
      d->unkVectorY = -(short)param_2;
      d->unkVectorZ = -(short)param_3;
	  #endif
    }
    else {
      d->unk_offset3B2 = (short)uVar10;
	  
	  movement.vx += param_1;
	  movement.vy += param_2;
	  movement.vz += param_3;
	  
	  // unused?
	  #if 0
      d->unkVectorX = (short)param_1;
      d->unkVectorY = (short)param_2;
      d->unkVectorZ = (short)param_3;
	  #endif
	}

	uVar14 = VehCalc_FastSqrt(
		movement.vx * movement.vx +
        movement.vy * movement.vy +
        movement.vz * movement.vz, 0x10);
    
	iVar9 = (int)d->baseSpeed;
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
    uVar14 = (uVar14 >> 8) - iVar9;
    bVar2 = (int)uVar10 < (int)uVar14;
    if ((int)uVar14 < 0) {
      uVar14 = 0;
      bVar2 = (int)uVar10 < 0;
    }
    if (bVar2) {
      uVar14 = uVar10;
    }
	
    if (((d->actionsFlagSet & 1) == 0) || (d->jump_ForcedMS == 0))
		goto CHECK_FOR_ANY_JUMP;
    
	if (d->jump_unknown != 0)
		d->jump_unknown = 0x180;

    if (d->kartState == KS_BLASTED) 
	{
      DECOMP_GAMEPAD_ShockFreq(d,8,0);
      DECOMP_GAMEPAD_ShockForce1(d,8,0x7f);
    }
  }

// PROCESS_JUMP
PROCESS_JUMP:

  d->jump_TenBuffer = 0;
  d->jump_CooldownMS = 0x180;
  d->actionsFlagSet |= 0x480;
  
// UNUSED LOOP
// Take largest jump calculation based on separate AxisAngle vectors
#if 0

  iVar9 = 0;
  iVar13 = 0;

  do {
  
  iVar4 = DECOMP_VehPhysGeneral_JumpGetVelY(&d->AxisAngle4_normalVec[0],&movement);
  
  // Abs Value of Jump, from Given AxisAngle
  iVar6 = iVar4;
  if (iVar4 < 0) {
   iVar6 = -iVar4;
  }
  
  // Compare to largest Jump from AxisAngle(s)
  iVar5 = iVar9;
  if (iVar9 < 0) {
    iVar5 = -iVar9;
  }

  // If new-largest jump from AxisAngle, save it
  if (iVar5 < iVar6) {
    iVar9 = iVar4;
  }

    //iVar13 ++
    //iVar8 ++ (next angleAxis)
  } while (iVar13 < 1)

#else
	
  iVar9 = DECOMP_VehPhysGeneral_JumpGetVelY(&d->AxisAngle4_normalVec[0],&movement);

#endif


  // AxisAngle
  short* axisAngle = &d->AxisAngle1_normalVec;
  if ((d->actionsFlagSet & 1) == 0) {
    axisAngle = &d->AxisAngle2_normalVec;
  }
  
  iVar8 = DECOMP_VehPhysGeneral_JumpGetVelY(axisAngle,&movement);
  
  // jump
  iVar13 = iVar8;
  if (iVar8 < 0) {
    iVar13 = -iVar8;
  }
  
  // ramp
  iVar6 = iVar9;
  if (iVar9 < 0) {
    iVar6 = -iVar9;
  }
  
  // ramp OR jump
  iVar4 = iVar9 * iVar9;
  if (iVar6 < iVar13) {
    iVar4 = iVar8 * iVar8;
    iVar9 = iVar8;
  }
  
  iVar13 = VehCalc_FastSqrt(
			iVar4 + (int)d->jump_InitialVelY * (int)d->jump_InitialVelY >> 8, 8);
						
  // 0 for most tracks, 0x50 for Sewer Speedway
  uVar10 = sdata->gGT->level1->unk_18C << 8;
  if (uVar10 == 0) {
    uVar10 = 0x3700;
  }
  else if (0x5000 < uVar10) {
    uVar10 = 0x5000;
  }
  
  uVar11 = iVar13 - iVar9;
  if ((int)uVar10 < iVar13 - iVar9) {
    uVar11 = uVar10;
  }
  if (movement.vy < (int)uVar11) {
	movement.vy = uVar11;
  }

// [end of the first frame of jump]

// skip here if not jumping
  
NOT_JUMPING:

  VehPhysCrash_ConvertVecToSpeed(d,&movement);
  iVar9 = d->speed - uVar14;
  d->speed = (short)iVar9;
  if (iVar9 * 0x10000 < 0) {
    d->speed = 0;
  }
  
  
  // d->unk36E is related to speedometer needle
  
  
  iVar9 = (int)d->speedApprox;
  if (iVar9 < 0) {
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
    if (iVar9 < 0x100) {
      sVar7 = d->unk36E - (d->unk36E >> 3);
    }
    else {
      sVar7 = (short)(d->unk36E * 0xd +
                      (sdata->gGT->timer & 7) * 0x300 >> 4);
    }
  }
  else {
    sVar7 = (short)(d->unk36E * 0xd + iVar9 * 3 >> 4);
  }
  d->unk36E = sVar7;
  
  
  return;
}