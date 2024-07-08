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
  char bVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short jumpForce;
  int iVar8;
  u_int uVar9;
  int setY;
  int iVar11;
  VECTOR movement;
  struct GameTracker *gGT = sdata->gGT;
  short approxSpd = d->speedApprox;
  short baseSpeed = d->baseSpeed;
  gte_SetRotMatrix(&d->matrixMovingDir.m[0][0]);

  // if driver is not drifting
  if (((d->kartState != KS_DRIFTING) &&

       // if driver is not using mask weapon
       ((d->actionsFlagSet & 0x800000) == 0)) &&

      // no reserves
      (d->reserves == 0))
  {
    short ampTurnState = (short)d->ampTurnState >> 8;
    if (ampTurnState < 0)
    {
      ampTurnState = -ampTurnState;
    }

    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    int turnSpeed = DECOMP_VehCalc_MapToRange(ampTurnState, 0, d->const_BackwardTurnRate, 0, d->const_TurnDecreaseRate);
    if (baseSpeed < 0)
    {
      baseSpeed = -baseSpeed;
    }
    if (baseSpeed < turnSpeed)
    {
      turnSpeed = baseSpeed;
    }
    turnSpeed = (baseSpeed < 0) ? turnSpeed : -turnSpeed;
    d->baseSpeed += turnSpeed;
  }

  // if rubbing on wall now, or recently
  if (d->set_0xF0_OnWallRub)
  {
    if (d->scrubMeta8 < baseSpeed)
    {
      baseSpeed = d->scrubMeta8;
    }
    if (baseSpeed < -d->scrubMeta8)
    {
      baseSpeed = -d->scrubMeta8;
    }
    d->baseSpeed = baseSpeed;
  }

  movement.vx = d->velocityXYZ[0];
  movement.vy = d->velocityXYZ[1];
  movement.vz = d->velocityXYZ[2];

  // if driver is not on quadblock, or if not forced to jump (via GOTO)
  if ((d->actionsFlagSet & 1) == 0)
  {
  CHECK_FOR_ANY_JUMP:
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

        // const_Jump * 9
        jumpForce = d->const_JumpForce * 9;

        // always true
        if (jumpForce < 0)
        {
          // add 3
          jumpForce += 3;
        }

        // jump_InitialVelY = big jump from spring
        d->jump_InitialVelY = (short)(jumpForce >> 2);

        // spring weapon sound
        OtherFX_Play_Echo(9, 1, d->actionsFlagSet & 0x10000);

        d->jump_unknown = 0x180;
        goto PROCESS_JUMP;
      }
      d->noItemTimer = 0;
    }

    // if not being forced to jump (turtles), this should cause the tiny jumps on top of walls.
    if (d->forcedJump_trampoline == 0)
    {
      // if driver left quadblock more than 0.16s ago
      if (((d->jump_CoyoteTimerMS == 0) ||

           // if haven't jumped in last 10 frames
           (d->jump_TenBuffer == 0)) ||

          // jump_CooldownMS not over (so can't jump again)
          (d->jump_CooldownMS != 0))
      {
        // if player is touching ground
        if ((((d->actionsFlagSet & 1) != 0) &&

             // if player is over a quadblock
             (d->underDriver != 0)) &&
            (
                iVar3 = d->underDriver->speedImpact,
                iVar3 != 0))
        {
          // player speed
          if (approxSpd < 0)
          { // change sign of player speed
            approxSpd = -approxSpd;
          }

          gte_ldVXY0((iVar3 * approxSpd >> 8) << 0x10);
          gte_ldVZ0(0);
          gte_rtv0();
          read_mt(iVar3, iVar2, iVar8);

          movement.vx += iVar3;
          movement.vy += iVar8;
          movement.vz += iVar2;
        }
        goto NOT_JUMPING;
      }

      // implied "else",
      // if (jump_cooldownMS is over) &&
      // 	(haven't left quadblock || no jump in over 10 frames)

      // force driver to jump
      d->jump_ForcedMS = 0xa0;

      // increment jump counter
      d->numberOfJumps++;

      d->jump_InitialVelY = d->const_JumpForce;

      // play jump sound
      OtherFX_Play_Echo(8, 1, d->actionsFlagSet & 0x10000);
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
        OtherFX_Play(0x7e, 1);
      }

      // currently forced airborne
      d->jump_ForcedMS = 0xa0;

      jumpForce = d->const_JumpForce * 3;

      // if big force jump (turtles)
      if (d->forcedJump_trampoline == 2)
      {
        d->jump_unknown = 0x180;
        d->jump_InitialVelY = jumpForce;
      }

      // if small force jump (turtles)
      else
      {
        d->jump_InitialVelY = (jumpForce >> 1);
      }

      // remove force jump (turtles)
      d->forcedJump_trampoline = 0;
    }
  }

  // if driver is on a quadblock
  else
  {
    short accel;
    // if driver is not on any turbo pad
    if (((d->stepFlagSet & 3) == 0) ||
        (baseSpeed < 1))
    {
      // driving backwards?
      if (baseSpeed != 0)
      {
        // terrain related
        if ((((d->terrainMeta1->flags & 4) == 0) ||
             (baseSpeed < 1)) ||
            (-1 < approxSpd))
        {
          iVar2 = approxSpd;
          if (iVar2 < 0)
          {
            iVar2 = -approxSpd;
          }
          if (((0x2ff < iVar2) && ((baseSpeed < 1 || (approxSpd < 1)))) &&
              ((-1 < baseSpeed || (-1 < approxSpd))))
            goto PROCESS_ACCEL;
        }

        // const_accel_noReserves + driver-specific acceleration
        accel = d->const_Accel_ClassStat + (d->accelConst << 5) / 5;

        // if you're not on any turbo pad
        if ((d->stepFlagSet & 3) == 0)
        {
          // if reserves are not zero
          if ((d->reserves != 0) &&
              (0 < baseSpeed))
          {
            accel = d->const_Accel_Reserves;
          }

          // driver -> terrain meta -> slowUntilSpeed,
          // if 0, driver will slow down until completely stuck
          iVar2 = d->terrainMeta1->slowUntilSpeed;

          if ((iVar2 != 0x100) &&

              // if driver is not using mask weapon
              ((d->actionsFlagSet & 0x800000) == 0))
          {
            accel = (accel * iVar2) >> 8;
          }
        }
        else
        {
          if (0 < baseSpeed)
            goto SET_HIGH_ACCEL;
        }
      }
    }
    // if driver is on a turbo pad
    else
    {
    SET_HIGH_ACCEL:
      // high acceleration
      accel = 8000;
    }
  PROCESS_ACCEL:
    accel = (accel * gGT->elapsedTimeMS) >> 5;

    gte_ldVXY0(0);
    gte_ldVZ0(accel & 0xffff);
    gte_rtv0();
    read_mt(sVar4, sVar5, sVar6);

    if (baseSpeed < 0)
    {
      d->unk_offset3B2 = -accel;
      iVar3 = -accel;
      iVar2 = -iVar2;
      iVar8 = -approxSpd;
      d->unkVectorX = -sVar4;
      d->unkVectorY = -sVar5;
      d->unkVectorZ = -sVar6;
    }
    else
    {
      d->unk_offset3B2 = accel;
      d->unkVectorX = sVar4;
      d->unkVectorY = sVar5;
      d->unkVectorZ = sVar6;
    }
    movement.vz += iVar2;
    movement.vy += iVar8;
    movement.vx += iVar3;

    // sqrt(x2+y2+z2 << 0x10)
    iVar11 = VehCalc_FastSqrt(movement.vx * movement.vx + movement.vy * movement.vy + movement.vz * movement.vz, 0x10);

    iVar11 = (iVar11 >> 8) - baseSpeed;
    bVar1 = (accel < iVar11);

    if (iVar11 < 0)
    {
      iVar11 = 0;
      bVar1 = (accel < 0);
    }

    if (bVar1)
    {
      iVar11 = accel;
    }

    // if not on quadblock, or if not forced to jump
    if (((d->actionsFlagSet & 1) == 0) || (d->jump_ForcedMS == 0))
      goto CHECK_FOR_ANY_JUMP;

    if (d->jump_unknown != 0)
    {
      d->jump_unknown = 0x180;
    }

    // If you're "blasted", flipping around after hit by missile, bomb, etc
    if (d->kartState == KS_BLASTED)
    {
      GAMEPAD_ShockFreq(d, 8, 0);
      GAMEPAD_ShockForce1(d, 8, 0x7f);
    }
  }

PROCESS_JUMP:

  d->jump_CooldownMS = 0x180;
  d->jump_TenBuffer = 0;
  d->actionsFlagSet |= 0x480;

  int ramp = VehPhysGeneral_JumpGetVelY(d->AxisAngle4_normalVec[0], &movement);

  if (ramp < 0)
  {
    ramp = -ramp;
  }

  short* axisAngle = &d->AxisAngle1_normalVec.x;
  if ((d->actionsFlagSet & 1) == 0)
  {
    axisAngle = &d->AxisAngle2_normalVec[0];
  }

  int jump = VehPhysGeneral_JumpGetVelY(axisAngle, &movement);

  if (jump < 0)
  {
    jump = -jump;
  }

  // if (ramp < 0)
  // {
  //   ramp = -ramp;
  // }

  ramp = (ramp < jump) ? (jump * jump) : (ramp * ramp);

  // iVar2 = sqrt( "basically" ramp+jump*jump )
  // last byte is cleared cause only 3 bytes in driver->0x2D4
  // are rendered, and the last byte is sub-pixel percision

  // iVar2 = sqrt(ramp+jump*jump)
  iVar2 = VehCalc_FastSqrt(ramp + (d->jump_InitialVelY * d->jump_InitialVelY) , 0);

  // zero in all arcade maps, idk adv, battle, cutscene, or credits
  uVar9 = gGT->level1->unk_18C << 8;

  if (gGT->level1->unk_18C == 0)
  {
    uVar9 = 0x3700;
  }
  else if (0x5000 < uVar9)
  {
    uVar9 = 0x5000;
  }

  setY = iVar2 - jump;
  if (uVar9 < setY)
  {
    setY = uVar9;
  }

  // max value for movementY (on stack)
  if (movement.vy < setY)
  {
    // set movementY to the speed that
    // you should have, on first frame of jump
    movement.vy = setY;
  }

// [end of the first frame of jump]

// skip here if not jumping
NOT_JUMPING:

  VehPhysCrash_ConvertVecToSpeed(d, &movement);

  // decrease speed
  d->speed -= iVar11;

  if (d->speed < 0)
  {
    d->speed = 0;
  }

  if (approxSpd < 0)
  {
    approxSpd = -approxSpd;
    if (approxSpd < 0x100)
    {
      sVar4 = d->unk36E - (d->unk36E >> 3);
    }
    else
    {
      sVar4 = (short)(d->unk36E * 0xd + (gGT->timer & 7) * 0x300 >> 4);
    }
  }
  else
  {
    sVar4 = (short)(d->unk36E * 0xd + approxSpd * 3 >> 4);
  }
  d->unk36E = sVar4;
}
