#include <common.h>

struct Driver * DECOMP_BOTS_Driver_Init(char driverId)
{
  char i;
  char valid;
  char navIndex;
  short numPoints;
  int tempPath;
  short copy;
  struct Driver *d;
  struct Thread *t;

  // driver pointer, nullptr
  d = NULL;

  // by default, assume no path found for this driver
  valid = false;

  // nav path index of this driver
  navIndex = sdata->driver_pathIndexIDs[driverId];

  // number of nav points on path
  numPoints = sdata->NavPath_ptrHeader[navIndex << 2]->numPoints;

  // set loop index to path index
  i = navIndex;

  while (true)
  {
    // save copy
    copy = i;

    // reduce path index
    i--;

    // if we found a path with at least one nav point
    if (1 < numPoints)
      break;

    // set new temporary path index
    tempPath = i;

    // if we go below zero
    if (i < 0)
    {
      // set path index back to 2
      i = 2;
      tempPath = 0x20000;
    }

    // save copy
    copy = i;

    // if we looped through all 3 paths and found zero
    // nav points on every path, then return nullptr driver
    if (tempPath == navIndex)
      goto END_SECTION;

    // number of nav points on temporary path index
    numPoints = sdata->NavPath_ptrHeader[tempPath]->numPoints;
  }

  // a good path was found
  valid = true;

END_SECTION:

  // if at least one valid nav path
  // is found, then spawn the AIs
  if (valid)
  {
    t =
        THREAD_BirthWithObject(
            // creation flags
            SIZE_RELATIVE_POOL_BUCKET(
                sizeof(struct Driver), // 0x62c
                NONE,
                LARGE,
                ROBOT),

            BOTS_ThTick_Drive, // behavior
            "robotcar",        // debug name
            0                  // thread relative
        );

    // Grab the pointer to the AI attached to the thread
    d = t->object;

    // robot Driver is 0x62c chars large
    memset(d, 0, 0x62c);

    VehInit_NonGhost(t, driverId);

    // pointer to structure of each player, given param1 car ID
    *(undefined4 *)(sdata->gGT + driverId * 4 + 0x24ec) = t->object;
    ;

    // set thread-> modelIndex to DYNAMIC_ROBOT_CAR
    t->modelIndex = 0x3f;

    // path index of driver
    d->botPath = copy;

    // turn on 21st flag of actions flag set (means racer is an AI)
    d->actionsFlagSet |= 0x100000;

    // set pointer to current navFrame to first on path
    d->botNavFrame = *(undefined4 *)(&DAT_8008dae0 + (int)copy * 4);

    // (free or taken?)
    LIST_AddFront(&DAT_8008daf8 + (int)copy * 0xc, d + 0x598);

    // Increment number of AIs
    sdata->gGT->numBotsNextGame++;

    BOTS_GotoStartingLine(d);
  }
  return d;
}