#include <common.h>

void DECOMP_BOTS_Driver_Convert(struct Driver *d) {
  struct GameTracker *gGT = sdata->gGT;
  char validPath;
  short numPoints;
  int i, pathIndex;
  unsigned int navFrame;
  unsigned int actionFlag;

  // if this racer is not an AI (player)
  if ((d->actionFlagsSet & 0x100000) == 0) {

    UI_RaceEnd_GetDriverClock(d);

    // nav path index of this driver
    pathIndex = sdata->driver_pathIndexIDs[d->driverID];

    validPath = 0;

    // number of nav points on this path
    numPoints = sdata->NavPath_ptrHeader[pathIndex]->numPoints);

    // ============

    // same as BOTS_Driver_Init
    // check if nav path data exists

    // ============

    // if invalid path
    if (numPoints == 0) {
      // check all paths
      for (i = 0; i < 3; i++) {
        // quit loop when found
        if (sdata->NavPath_ptrHeader[i]->numPoints != 0) {
          // valid path data was found
          validPath = 1;
          break;
        }
      }
    }

  LAB_800173e4:

    // if valid path data was found
    if (validPath) {
      // 0x94 chunk in driver struct?
      memset(*(int *)(d + 0x598), 0, 0x94);

      // path index
      pathIndex = i * 4;

      *(int *)(d + 0x5d0) = d->ySpeed;

      // nav path index
      *(short *)(d + 0x5b8) = pathIndex;

      // AI speed
      *(int *)(d + 0x5d4) = d->speedApprox;

      // pointer to first navFrame on path
      navFrame = sdata->NavPath_ptrNavFrameArray[pathIndex];

      *(int *)(d + 0x5a8) = 0;
      d->unknownDimension2Curr = 0;
      d->multiDrift = 0;
      d->ampTurnState = 0;
      d->set_0xF0_OnWallRub = 0;

      // current navFrame
      *(int *)(d + 0x5a4) = navFrame;

      // driver -> instance -> thread -> funcThTick =
      d->instSelf->thread->funcThTick = BOTS_ThTick_Drive;

      // if you are in battle mode
      if ((gGT->gameMode1 & 0x20) != 0) {
        // pointer to each AI Path Header
        piVar8 = &sdata->NavPath_ptrHeader[iVar10];

        // set the X, Y, and Z positions
        d->posCurr[0] = (int)piVar8->frame->pos[0] << 8;
        d->posCurr[1] = (int)piVar8->frame->pos[1] << 8;
        d->posCurr[2] = (int)piVar8->frame->pos[2] << 8;
      }

      // (free or taken?)
      LIST_AddFront(&DAT_8008daf8[pathIndex], *(int *)(d + 0x598));

      BOTS_SetRotation(d, 0);

      GAMEPAD_Vib_2(d, 0, 0);

      actionFlag = d->actionFlagsSet;

      // player becomes AI, drop bits for button holding
      d->actionFlagsSet &= 0xfffffff3 | 0x100000;

      // if previous value of actions flag set had 26th flag on (means racer
      // finished the race)
      if ((actionFlag & 0x2000000) != 0) {
        CAM_EndOfRace(gGT->cameraDC[d->driverID], d);
      }

      // Kart state:
      switch (d->kartState) {
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