// =============================================================
// Base score 1460 (NTSC-U/926), needs types analysis/replacement
// =============================================================

#include "Vehicle.h"

extern struct GameTracker *D_8008D2AC;

void VehPhysGeneral_JumpAndFriction(struct Thread *t, struct Driver *d)
{
  char uVar1;
  bool bVar2;
  short sVar3;
  short new_var2;
  int iVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  unsigned int uVar10;
  unsigned int uVar11;
  int iVar13;
  unsigned int uVar14;
  int param_1;
  int param_2;
  int param_3;
  VECTOR movement;
  int new_var3;
  struct GameTracker **new_var;
  int jumpForce;
  int temp;
  short *axisAngle;
  gte_SetRotMatrix(&d->matrixMovingDir);
  if (((d->kartState != 2) && ((d->actionsFlagSet & 0x800000) == 0)) && (d->reserves == 0))
  {
    int ampTurnState = ((short) d->ampTurnState) >> 8;
    iVar9 = d->const_TurnDecreaseRate;
    if (ampTurnState < 0)
    {
      ampTurnState = -ampTurnState;
    }

    param_1 = func_80058F9C(ampTurnState, 0, d->const_BackwardTurnRate, 0, iVar9);
    new_var = &D_8008D2AC;
    param_3 = (iVar9 = d->baseSpeed);
    if (param_3 < 0)
    {
      iVar9 = -param_3;
    }
    if (iVar9 < param_1)
    {
      param_1 = iVar9;
    }
    if (param_3 < 0)
    {
      param_1 = -param_1;
    }
    d->baseSpeed = (short) (((unsigned short) d->baseSpeed) - param_1);
  }
  if (d->set_0xF0_OnWallRub != 0)
  {
    if (d->baseSpeed > d->scrubMeta8)
    {
      d->baseSpeed = d->scrubMeta8;
    }
    if (d->baseSpeed < (-d->scrubMeta8))
    {
      d->baseSpeed = -d->scrubMeta8;
    }
  }
  movement.vx = d->velocity.v[0];
  movement.vy = d->velocity.v[1];
  movement.vz = d->velocity.v[2];
  uVar14 = 0;
  iVar9 = 0;
  iVar8 = d->actionsFlagSet;
  if ((iVar8 & 1) == 0)
  {
    iVar13 = iVar8;
    goto CHECK_FOR_ANY_JUMP;
  }
  if ((d->stepFlagSet & 3) != 0)
  {
    if (0 < d->baseSpeed)
    {
      goto SET_HIGH_ACCEL;
    }
  }
  if (d->baseSpeed != 0)
  {
    if ((((d->terrainMeta1->flags & 4) == 0) || (d->baseSpeed < 1)) || ((-1) < d->speedApprox))
    {
      ;
      if (((int) d->speedApprox) < 0)
      {
        iVar13 = -iVar8;
      }
      bVar2 = (int) d->speedApprox;
      if (((0x2ff < iVar13) && ((d->baseSpeed < 1) || (((int) d->speedApprox) < 1))) && (((-1) < d->baseSpeed) || ((-1) < bVar2)))
      {
        goto PROCESS_ACCEL;
      }
    }
    iVar9 = d->const_Accel_ClassStat + ((((int) d->accelConst) << 5) / 5);
    if ((d->stepFlagSet & 3) != 0)
    {
      if (d->baseSpeed <= 0)
      {
        goto PROCESS_ACCEL;
      }
      SET_HIGH_ACCEL:
      iVar9 = 8000;
    }
    else
    {
      if ((d->reserves != 0) && (0 < d->baseSpeed))
      {
        iVar9 = d->const_Accel_Reserves;
      }
      param_1 = d->terrainMeta1->slowUntilSpeed;
      if ((param_1 != 0x100) && ((d->actionsFlagSet & 0x800000) == 0))
      {
        iVar9 = (param_1 * iVar9) >> 8;
      }
    }
  }
  PROCESS_ACCEL:
  uVar10 = (iVar9 * (*new_var)->elapsedTimeMS) >> 5;

  gte_ldVXY0(0);
  temp = uVar10 & 0xffff;
  gte_ldVZ0(temp);
  gte_rtv0();
  gte_stMAC1(param_1);
  gte_stMAC2(param_3);
  gte_stMAC3(param_2);
  if (d->baseSpeed < 0)
  {
    d->unk_offset3B2 = -((short) uVar10);
    movement.vx -= param_1;
    movement.vy -= param_2;
    movement.vz -= param_3;
    d->unkVectorX = -((short) param_1);
    d->unkVectorY = -((short) param_3);
    d->unkVectorZ = -((short) param_2);
  }
  else
  {
    d->unk_offset3B2 = (short) uVar10;
    movement.vx += param_1;
    movement.vy += param_2;
    movement.vz += param_3;
    d->unkVectorX = (short) param_1;
    d->unkVectorY = (short) param_3;
    d->unkVectorZ = (short) param_2;
  }
  uVar14 = func_80059070(((movement.vx * movement.vx) + (movement.vy * movement.vy)) + (movement.vz * movement.vz), 0x10);
  uVar14 = uVar14 >> 8;
  uVar14 = d->baseSpeed;
  ;
  if (((int) (new_var2 = uVar14)) < 0)
  {
    iVar9 = -iVar9;
  }
  uVar14 = uVar14 - iVar9;
  bVar2 = ((int) uVar10) < ((int) uVar14);
  if (((int) uVar14) < 0)
  {
    uVar14 = 0;
    ;
  }
  if (((int) uVar10) < ((int) uVar14))
  {
    uVar14 = uVar10;
  }

  if ((d->actionsFlagSet & 1) == 0)
  {
    goto CHECK_FOR_ANY_JUMP;
  }
  if (d->jump_ForcedMS == 0)
  {
    goto CHECK_FOR_ANY_JUMP;
  }
  if (d->jump_unknown != 0)
  {
    d->jump_unknown = 0x180;
  }
  if (d->kartState == 6)
  {
    func_80026440(d, 8, 0);
    func_800264C0(d, 8, 0x7f);
  }
  goto PROCESS_JUMP;
  CHECK_FOR_ANY_JUMP:
  if (((d->actionsFlagSet & 0x8000) != 0) && (d->heldItemID == 5))
  {
    d->actionsFlagSet &= ~0x8000;
    if ((d->jump_CoyoteTimerMS != 0) && (d->jump_CooldownMS == 0))
    {
      d->jump_ForcedMS = 0xa0;
      jumpForce = d->const_JumpForce * 9;
      d->jump_InitialVelY = (short) (jumpForce / 4);
      func_80028494(9, 1, ((unsigned short *) (&d->actionsFlagSet))[1] & 1);
      d->jump_unknown = 0x180;
      goto PROCESS_JUMP;
    }
    d->noItemTimer = 0;
  }

  if (d->forcedJump_trampoline != 0)
  {
    if ((d->jump_ForcedMS == 0) || (d->jump_InitialVelY == d->const_JumpForce))
    {
      func_80028468(0x7e, 1);
    }
    d->jump_ForcedMS = 0xa0;
    if (d->forcedJump_trampoline == 2)
    {
      d->jump_unknown = 0x180;
      d->jump_InitialVelY = (short) (((int) d->const_JumpForce) * 3);
    }
    else
    {
      d->jump_InitialVelY = (short) ((((int) d->const_JumpForce) * 3) / 2);
    }
    d->forcedJump_trampoline = 0;
  }
  else
  {
    if (d->jump_CoyoteTimerMS == 0)
    {
      goto NOT_JUMPING_COLD;
    }
    if (d->jump_TenBuffer == 0)
    {
      goto NOT_JUMPING_COLD;
    }
    if (d->jump_CooldownMS != 0)
    {
      goto NOT_JUMPING_COLD;
    }
    d->jump_ForcedMS = 0xa0;
    d->numberOfJumps++;
    d->jump_InitialVelY = d->const_JumpForce;
    uVar11 = ((unsigned short *) (&d->actionsFlagSet))[1];
    func_80028494(8, 1, uVar11 & 1);
  }
  PROCESS_JUMP:
  iVar9 = 0;
  iVar13 = iVar9;
  d->jump_CooldownMS = 0x180;
  d->jump_TenBuffer = 0;
  d->actionsFlagSet |= 0x480;
  iVar8 = 0x378;
  do
  {
    iVar4 = func_800605A0((short *) (((char *) d) + iVar8), &movement);
    iVar6 = iVar4;
    if (iVar4 < 0)
    {
      iVar6 = -iVar4;
    }
    iVar5 = iVar9;
    if (iVar9 < 0)
    {
      iVar5 = -iVar9;
    }
    if (iVar5 < iVar6)
    {
      iVar9 = iVar4;
    }
    iVar13++;
    iVar8 += 8;
  }
  while (iVar13 <= 0);
  axisAngle = &d->AxisAngle1_normalVec.v[0];
  if ((d->actionsFlagSet & 1) == 0)
  {
    axisAngle = &d->AxisAngle2_normalVec[0];
  }
  iVar8 = (param_1 = (iVar13 = func_800605A0(axisAngle, &movement)));
  if (iVar8 < 0)
  {
    iVar13 = -iVar8;
  }
  iVar6 = iVar9;
  if (iVar9 < 0)
  {
    iVar6 = -iVar9;
  }
  if (iVar6 < iVar13)
  {
    iVar9 = iVar8;
  }
  iVar4 = iVar9 * iVar9;

  iVar13 = func_80059070(((((int) d->jump_InitialVelY) * ((int) d->jump_InitialVelY)) + iVar4) >> 8, 8);
  uVar10 = D_8008D2AC->level1->unk_18C << 8;
  temp = iVar13 - iVar9;
  if (uVar10 == 0)
  {
    uVar10 = 0x3700;
  }
  else
    if (0x5000 < ((int) uVar10))
  {
    uVar10 = 0x5000;
  }
  uVar11 = temp;
  if (((int) uVar10) < temp)
  {
    uVar11 = uVar10;
  }
  if (movement.vy < ((int) uVar11))
  {
    movement.vy = uVar11;
  }
  new_var3 = 4;
  goto NOT_JUMPING;
  NOT_JUMPING_COLD:
  if ((d->actionsFlagSet & 1) != 0)
  {
    if ((d->underDriver != 0) && ((iVar9 = d->underDriver->mulNormVecY, iVar9 != 0)))
    {
      iVar13 = (int) d->speedApprox;
      if (iVar13 < 0)
      {
        iVar13 = -iVar13;
      }
      temp = ((iVar9 * iVar13) >> 8) << 0x10;
      gte_ldVXY0(temp);
      gte_ldVZ0(0);
      gte_rtv0();
      gte_stMAC1(iVar9);
      gte_stMAC2(temp);
      gte_stMAC3(param_3);
      movement.vx += iVar9;
      movement.vy += temp;
      movement.vz += param_3;
    }
  }

  NOT_JUMPING:
  func_8005CD1C(d, &movement, 0);

  iVar9 = ((unsigned short) d->speed) - uVar14;
  d->speed = (short) iVar9;
  if ((iVar9 * 0x10000) < 0)
  {
    d->speed = 0;
  }

  iVar9 = (int) d->speedApprox;
  if (iVar9 < 0)
  {
    if (iVar9 < 0)
    {
      iVar9 = -iVar9;
    }
    if (iVar9 < 0x100)
    {
      sVar7 = d->unk36E - (d->unk36E >> 3);
    }
    else
    {
      int unk13 = ((int) d->unk36E) * 0xd;
      int timer7 = (int) (D_8008D2AC->timer & 7);
      int timer768 = (timer7 << 8) + (timer7 << 9);
      sVar7 = (short) (((unsigned int) (unk13 + timer768)) >> 4);
    }
  }
  else
  {
    sVar7 = (short) (((d->unk36E * 0xd) + (iVar9 * 3)) >> new_var3);
  }
  d->unk36E = sVar7;

  return;
}
