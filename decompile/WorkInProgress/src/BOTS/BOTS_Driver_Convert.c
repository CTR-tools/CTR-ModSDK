#include <common.h>

// Budget: 584/692 bytes

void DECOMP_BOTS_Driver_Convert(struct Driver *d)
{
  u_char validPath;
  short numPoints;
  int i, damageType;
  struct NavFrame *frame;
  unsigned int actionFlag;
  struct GameTracker *gGT = sdata->gGT;

  // if this racer is not an AI (player)
  if ((d->actionsFlagSet & 0x100000) == 0)
  {
    UI_RaceEnd_GetDriverClock(d);

    validPath = false;

    // nav path index of this driver
    i = sdata->driver_pathIndexIDs[d->driverID];

    // number of nav points on this path
    numPoints = sdata->NavPath_ptrHeader[i]->numPoints;

    // ============

    // same as BOTS_Driver_Init
    // check if nav path data exists

    // ============

    // if invalid path
    if (numPoints == 0)
    {
      // check all paths
      for (i = 0; i < 3; i++)
      {
        // quit loop when found
        if (sdata->NavPath_ptrHeader[i]->numPoints != 0)
        {
          // valid path data was found
          validPath = true;
          break;
        }
      }
    }

    // if valid path data was found
    if (!validPath) return;

    // 0x94 chunk in driver struct?
    memset(&d->unk598, 0, 0x94);

    *(int*)((int)d + 0x540) = d->ySpeed;

    // nav path index
    d->botPath = i;

    // AI speed
    *(int *)((int)d  + 0x5d4) = d->speedApprox;

    // pointer to first navFrame on path
    d->botNavFrame = sdata->NavPath_ptrNavFrameArray[i];

    d->unk5a8 = 0;
    d->turnAngleCurr = 0;
    d->multDrift = 0;
    d->ampTurnState = 0;
    d->set_0xF0_OnWallRub = 0;

    d->instSelf->thread->funcThTick = BOTS_ThTick_Drive;

    // if you are in battle mode
    if ((gGT->gameMode1 & BATTLE_MODE))
    {
      // pointer to each AI Path Header
      frame = NAVHEADER_GETFRAME(sdata->NavPath_ptrHeader[i]);

      // set the X, Y, and Z positions
      d->posCurr.x = (int)frame[i].pos[0] << 8;
      d->posCurr.y = (int)frame[i].pos[1] << 8;
      d->posCurr.z = (int)frame[i].pos[2] << 8;
    }

    // (free or taken?)
    LIST_AddFront(&sdata->unk_NavRelated[i], (struct Item *)d->unk598);

    BOTS_SetRotation(d, 0);

    GAMEPAD_JogCon2(d, 0, 0);

    actionFlag = d->actionsFlagSet;

    // remove flags for pressing L1|R1|Square and becomes AI
    d->actionsFlagSet = ((actionFlag & ~(0x4 | 0x8)) | 0x100000);

    // if previous value of actions flag set had 26th flag on
    // (racer finished the race)
    if ((actionFlag & 0x2000000) != 0)
    {
      CAM_EndOfRace(&gGT->cameraDC[d->driverID], d);
    }

    // Kart state:
    switch (d->kartState)
    {
    case KS_SPINNING:
      damageType = 1;
      break;
    case KS_BLASTED:
      damageType = 2;
      break;
    default:
      return;
    }
    BOTS_ChangeState(d, damageType, 0, 0);
  }
}