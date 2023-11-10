#include <common.h>

void DECOMP_BOTS_Driver_Convert(struct Driver *d)
{
  struct GameTracker *gGT = sdata->gGT;
  char validPath;
  short numPoints;
  int i, pathIndex;
  unsigned int navFrame;
  unsigned int actionFlag;

  // if this racer is not an AI (player)
  if ((d->actionFlagsSet & 0x100000) == 0)
  {

    UI_RaceEnd_GetDriverClock(d);
    
    validPath = 0;

    // nav path index of this driver
    pathIndex = sdata->driver_pathIndexIDs[d->driverID];

    // number of nav points on this path
    numPoints = sdata->NavPath_ptrHeader[pathIndex]->numPoints;

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
          validPath = 1;
          break;
        }
      }
    }

  END_SECTION:

    // if valid path data was found
    if (validPath)
    {
      // 0x94 chunk in driver struct?
      memset(*(int *)(d + 0x598), 0, 0x94);

      // path index
      pathIndex = i;

      *(int *)(d + 0x5d0) = d->ySpeed;

      // nav path index
      d->botPath = pathIndex;

      // AI speed
      *(int *)(d + 0x5d4) = d->speedApprox;

      // pointer to first navFrame on path
      navFrame = sdata->NavPath_ptrNavFrameArray[pathIndex];

      d->unk5a8 = 0;
      d->unknownDimension2Curr = 0;
      d->multiDrift = 0;
      d->ampTurnState = 0;
      d->set_0xF0_OnWallRub = 0;

      // current navFrame
      d->botNavFrame = navFrame;

      d->instSelf->thread->funcThTick = BOTS_ThTick_Drive;

      // if you are in battle mode
      if ((gGT->gameMode1 & BATTLE_MODE) != 0)
      {
        // pointer to each AI Path Header
        struct NavHeader* ptrNav = sdata->NavPath_ptrHeader[pathIndex];

        // set the X, Y, and Z positions
        d->posCurr[0] = (int)ptrNav->frame->pos[0] << 8;
        d->posCurr[1] = (int)ptrNav->frame->pos[1] << 8;
        d->posCurr[2] = (int)ptrNav->frame->pos[2] << 8;
      }

      // (free or taken?)
      LIST_AddFront(sdata->unk_NavRelated[pathIndex], d->unk598);

      BOTS_SetRotation(d, 0);

      GAMEPAD_Vib_2(d, 0, 0);

      actionFlag = d->actionFlagsSet;

      // player becomes AI, drop bits for button holding
      d->actionFlagsSet &= 0xfffffff3 | 0x100000;

      // if previous value of actions flag set had 26th flag on (means racer
      // finished the race)
      if ((actionFlag & 0x2000000) != 0)
      {
        CAM_EndOfRace(gGT->cameraDC[d->driverID], d);
      }

      // Kart state:
      switch (d->kartState)
      {
        // if racer is spinning
      case 3:
        navFrame = 1;
        // if racer is blasted
      case 6:
        navFrame = 2;
        break;
      default:
        return;
      }
      BOTS_ChangeState(d, navFrame, 0, 0);
    }
  }
}