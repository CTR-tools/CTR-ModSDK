#include <common.h>

void DECOMP_BOTS_GotoStartingLine(struct Driver *d)
{
  char spawnPos;
  short accel;
  int accelDuration;
  short rotY;
  ushort extraout_var;

  sdata->unk_counter_upTo450 = 0;

  VehInit_TeleportSelf(d, 3, 0);

  // get position where driver should spawn
  spawnPos = sdata->kartSpawnOrderArray[d->driverID];

  *(int *)(d + 0x5ec) = 0;
  *(int *)(d + 0x5e8) = 0;
  *(int *)(d + 0x5e4) = 0;
  *(int *)(d + 0x5e0) = 0;
  *(int *)(d + 0x5dc) = 0;
  *(int *)(d + 0x5d8) = 0;
  *(int *)(d + 0x5d4) = 0;
  *(int *)(d + 0x5d0) = 0;
  *(int *)(d + 0x5cc) = 0;

  *(int *)(d + 0x5f0) = d->posCurr[0];
  *(int *)(d + 0x5f4) = d->posCurr[1];
  *(int *)(d + 0x5f8) = d->posCurr[2];

  d->unk5a8 = 0;

  // current navFrame pointer, first navFrame on path
  d->botNavFrame = sdata->NavPath_ptrNavFrameArray[d->botPath];

  BOTS_SetRotation(d, 1);

  // time until full acceleration from start
  accelDuration = sdata->AI_timeToFullAccel_0xa0;

  // get acceleration order from spawn order
  accel = sdata->accelerateOrder[spawnPos];

  d->rotCurr.w = 0;
  d->rotPrev.y = 0;
  *(short *)(d + 0x600) = 0;
  d->rotCurr.x = 0;
  d->rotPrev.x = 0;
  *(short *)(d + 0x5fc) = 0;
  
  d->unknownDimension2Curr = 0;

  // turn on 21st flag of actions flag set, means driver is AI
  d->actionsFlagSet |= 0x100000;

  // calculate Y rotation
  rotY = (short)d->estimateRotNav[1] << 4;

  // every possible Y rotation
  *(short *)(d + 0x608) = rotY;
  d->angle = rotY;
  d->rotCurr.y = rotY;
  d->rotPrev.y = rotY;
  *(short *)(d + 0x5fe) = rotY;

  // acceleration from start-line to full speed
  d->botAccel = accelDuration * accel;

  // cooldown before next weapon
  RngDeadCoed(&sdata->const_0x30215400);
  d->weaponCooldown = (extraout_var & 0xff) + 300;

  return;
}