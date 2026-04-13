#include <common.h>

void DECOMP_BOTS_SetRotation(struct Driver* bot, short param_2)
{
  short uVar1;
  short sVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  short *navPosRot;
  int iVar7;

  // pointer to navFrame
  navPosRot = &bot->botNavFrame->pos;

  *(int *)(bot + 0x5ec) = 0;
  *(int *)(bot + 0x5e8) = 0;
  *(int *)(bot + 0x5e4) = 0;

  // ======== Get Driver Position =============

  bot->estimatePos[0] = (short)(bot->posCurr.x >> 8);
  bot->estimatePos[1] = (short)(bot->posCurr.y >> 8);
  bot->estimatePos[2] = (short)(bot->posCurr.z >> 8);

  // ======== Compare to Nav Position =============

  iVar7 = (int)navPosRot[0] - (int)bot->estimatePos[0];
  iVar4 = (int)navPosRot[1] - (int)bot->estimatePos[1];
  iVar5 = (int)navPosRot[2] - (int)bot->estimatePos[2];

  // ======== Calculate Distance =============

  // uVar1 = XZ Distance from driver to Nav
  uVar1 = SquareRoot0(iVar7 * iVar7 + iVar5 * iVar5);

  bot->distToNextNavXZ = uVar1;

  // uVar1 = XYZ Distance from driver to Nav
  uVar1 = SquareRoot0(iVar7 * iVar7 + iVar4 * iVar4 + iVar5 * iVar5);

  // 0x616 = Save XYZ Distance
  bot->distToNextNavXYZ = uVar1;

  // ======== Calculate Rotation =============

  // lVar3 = atan(Simple Y pos * 0x1000, Simplified XZ distance from Nav Point)
  lVar3 = ratan2(iVar4 * 0x1000, (int)bot->distToNextNavXZ << 0xc);

  // 0x615 = Simplified Y Rotation
  bot->estimateRotCurrY = (char)(lVar3 >> 4);

  bot->unk5a8 = 0;

  // if BOTS_ThTick_Drive or BOTS_Driver_Convert
  if (param_2 == 0)
  {
    // set rotX from nav data
    bot->estimateRotNav[0] = navPosRot[3];

    // lVar3 = atan(-X pos, -Z pos)
    lVar3 = ratan2(-iVar7, -iVar5);

    // set rotY based on direction to next nav
    bot->estimateRotNav[1] = (char)(lVar3 + 0x800 >> 4);

    // set rotZ from nav data
    bot->estimateRotNav[2] = navPosRot[4];
  }

  // if GotoStartLine
  else
  {
    // get rotY from startline
    bot->estimateRotNav[1] = (char)((int)sdata->gGT->level1->DriverSpawn[0].rot[1] + 0x400 >> 4);
  }

  sVar2 = (ushort)param_1->estimateRotNav[1] << 4;

  // All these offsets = Y rotation
  bot->ai_rotY_608 = sVar2;
  bot->angle = sVar2;
  bot->rotCurr.y = sVar2;
  bot->rotPrev.y = sVar2;
  bot->ai_rot4[1] = sVar2;

  bot->botFlags |= 1;
  return;
}