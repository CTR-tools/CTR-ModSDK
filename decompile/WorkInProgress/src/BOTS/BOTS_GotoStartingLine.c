#include <common.h>

void DECOMP_BOTS_GotoStartingLine(struct Driver *d)
{
  char spawnPos;
  short accel;
  int accelDuration;
  short rotY;

  sdata->unk_counter_upTo450 = 0;

  VehBirth_TeleportSelf(d, 3, 0);

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

  d->ai_posBackup[0] = d->posCurr.x;
  d->ai_posBackup[1] = d->posCurr.y;
  d->ai_posBackup[2] = d->posCurr.z;

  d->unk5a8 = 0;

  // current navFrame pointer, first navFrame on path
  d->botNavFrame = sdata->NavPath_ptrNavFrameArray[d->botPath];

  BOTS_SetRotation(d, 1);

  // time until full acceleration from start
  accelDuration = sdata->AI_AccelFrameCount;

  // get acceleration order from spawn order
  accel = sdata->accelerateOrder[spawnPos];

  d->rotCurr.w = 0;
  d->rotPrev.y = 0;
  d->ai_rot4[0] = 0;
  d->ai_rot4[2] = 0;
  d->rotCurr.x = 0;
  d->rotPrev.x = 0;

  d->turnAngleCurr = 0;

  // turn on 21st flag of actions flag set, means driver is AI
  d->actionsFlagSet |= 0x100000;

  // calculate Y rotation
  rotY = (short)d->estimateRotNav[1] << 4;

  // every possible Y rotation
  d->ai_rotY_608 = rotY;
  d->angle = rotY;
  d->rotCurr.y = rotY;
  d->rotPrev.y = rotY;
  d->ai_rot4[1] = rotY;

  // acceleration from start-line to full speed
  d->botAccel = accelDuration * accel;

  // cooldown before next weapon
  int rng = RngDeadCoed(&sdata->const_0x30215400);
  d->weaponCooldown = (rng & 0xff) + 300;
}