#include <common.h>

void DECOMP_CAM_StartLine_FlyIn(int *param_1, int maxFrames, int frame, short *desiredPos, short *desiredRot)
{
  struct Level *lev = sdata->gGT->level1;
  short sVar1;
  long x;
  int iVar2;
  short *psVar3;
  int index;
  u_int uVar5;
  short *psVar6;
  short sVar7;
  int frameRatio;
  SVECTOR local_78;
  SVECTOR local_70;
  MATRIX MStack104;
  short rot[3];
  short pos[3];
  short local_30;
  short local_2e;
  short local_2c;
  long alStack40[2];

  // frame index
  index = (frame << 0x10) >> 4;

  // divide by total number of frames
  frameRatio = index / maxFrames;

  iVar2 = (int)*(short *)(param_1 + 2);
  sVar7 = *(short *)((int)param_1 + 10);

  if (*(short *)((int)param_1 + 10) < iVar2)
  {
    sVar7 = *(short *)(param_1 + 2);
  }

  sVar1 = (short)(sVar7 * frameRatio >> 0xc);
  if ((int)sVar1 < iVar2 + -1)
  {
    psVar6 = (short *)(param_1[0] + (int)sVar1 * 6);
    index = frameRatio;
  }
  else
  {
    index = 0;
    psVar6 = (short *)(param_1[0] + iVar2 * 6 + -0xc);
  }
  if ((int)sVar1 < (int)*(short *)((int)param_1 + 10) + -1)
  {
    psVar3 = (short *)(param_1[1] + (int)sVar1 * 6);
  }
  else
  {
    frameRatio = 0;
    psVar3 = (short *)(param_1[1] + (int)*(short *)((int)param_1 + 10) * 6 + -0xc);
  }
  uVar5 = sVar7 * index & 0xfff;

  local_78.vx = psVar6[0] + (short)((int)(((int)psVar6[3] - (int)psVar6[0]) * uVar5) >> 0xc);
  local_78.vy = psVar6[1] + (short)((int)(((int)psVar6[4] - (int)psVar6[1]) * uVar5) >> 0xc);
  local_78.vz = psVar6[2] + (short)((int)(((int)psVar6[5] - (int)psVar6[2]) * uVar5) >> 0xc);

  uVar5 = sVar7 * frameRatio & 0xfff;
  local_70.vx = psVar3[0] + (short)((int)(((int)psVar3[3] - (int)psVar3[0]) * uVar5) >> 0xc);
  local_70.vy = psVar3[1] + (short)((int)(((int)psVar3[4] - (int)psVar3[1]) * uVar5) >> 0xc) + -0x60;
  local_70.vz = psVar3[2] + (short)((int)(((int)psVar3[5] - (int)psVar3[2]) * uVar5) >> 0xc);

  // rotation data
  rot[0] = lev->DriverSpawn[0].rot[0];
  rot[1] = lev->DriverSpawn[0].rot[1] + 0x400;
  rot[2] = lev->DriverSpawn[0].rot[2];

  // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(&MStack104, &rot);

  // overwrites Y variables that are
  // used later in MStack104.t[1]

  CAM_StartLine_FlyIn_FixY(&lev->DriverSpawn[1]);
  CAM_StartLine_FlyIn_FixY(&lev->DriverSpawn[2]);
  CAM_StartLine_FlyIn_FixY(&lev->DriverSpawn[5]);

  // get midpoint between driver[1] and driver[2],
  // make matrix from that for camera
  MStack104.t[0] =
      (int)lev->DriverSpawn[1].pos[0] +
      ((int)lev->DriverSpawn[2].pos[0] - (int)lev->DriverSpawn[1].pos[0]) / 2;
  MStack104.t[1] =
      (int)lev->DriverSpawn[1].pos[1] +
      ((int)lev->DriverSpawn[2].pos[1] - (int)lev->DriverSpawn[1].pos[1]) / 2 + 0x40;
  MStack104.t[2] =
      (int)lev->DriverSpawn[1].pos[2] +
      ((int)lev->DriverSpawn[2].pos[2] - (int)lev->DriverSpawn[1].pos[2]) / 2;

  SetRotMatrix(&MStack104);
  SetTransMatrix(&MStack104);

  RotTrans(&local_78, (VECTOR *)pos, alStack40);

  // camera TransitionTo pos
  desiredPos[0] = pos[0];
  desiredPos[1] = pos[1];
  desiredPos[2] = pos[2];

  RotTrans(&local_70, (VECTOR *)pos, alStack40);

  local_30 = desiredPos[0] - pos[0];
  local_2e = desiredPos[1] - pos[1];
  local_2c = desiredPos[2] - pos[2];

  // Camera Y rotation
  x = ratan2((int)(desiredPos[0] - pos[0]),
             (int)(desiredPos[2] - pos[2]));
             
  desiredRot[1] = (short)x;

  x = SquareRoot0((int)local_30 * (int)local_30 + (int)local_2c * (int)local_2c);

  // Camera X rotation
  x = ratan2((int)local_2e, x);
  desiredRot[0] = 0x800 - (short)x;

  // Camera Z rotation
  desiredRot[2] = 0;
  return;
}
