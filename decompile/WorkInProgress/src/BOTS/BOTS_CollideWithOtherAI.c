#include <common.h>

void DECOMP_BOTS_CollideWithOtherAI(struct Driver *robot_1, struct Driver *robot_2)
{
  int iVar1;
  struct Driver *temp;
  uint uVar3;
  int iVar4;
  short pos[3];

  // first determine which driver bumps forward and which bumps backwards
  temp = robot_1;

  // if driver 1 is ahead in the race of driver 2
  if (robot_1->driverRank < robot_2->driverRank)
  {
    // swap driver 1 and driver 2 pointers
    robot_1 = robot_2;
    robot_2 = temp;
  }

  iVar4 = robot_1->estimatePos[0];
  if ((robot_1->botFlags & 1) == 0)
  {
    // nav path index
    iVar1 = robot_1->botPath;

    // pointer to navFrame
    iVar4 = robot_1->botNavFrame;

    // add 0x14 to next navFrame
    uVar3 = iVar4 + 0x14;

    // if you go out of bounds
    if (sdata->NavPath_ptrHeader[iVar1]->last <= uVar3)
    {
      // loop back to first navFrame
      uVar3 = sdata->NavPath_ptrNavFrameArray[iVar1];
    }
  }
  else
  {
    // pointer to nav frame
    uVar3 = robot_1->botNavFrame;
  }

  // position of one driver
  pos[0] = (short)(robot_1->posCurr.x >> 8);
  pos[1] = (short)(robot_1->posCurr.y >> 8);
  pos[2] = (short)(robot_1->posCurr.z >> 8);

  // two navFrame structs, and position pointer
  iVar1 = CAM_MapRange_PosPoints(uVar3, iVar4, &pos);

  // position of other driver
  pos[0] = (short)(robot_2->posCurr.x >> 8);
  pos[1] = (short)(robot_2->posCurr.y >> 8);
  pos[2] = (short)(robot_2->posCurr.z >> 8);

  // two navFrame structs, and position pointer
  iVar4 = CAM_MapRange_PosPoints(uVar3, iVar4, &pos);

  // reduce speed of one AI,
  // the AI that is closer to the previous nav point,
  // who therefore is the driver in the back of the collision

  if (iVar1 < iVar4)
  {
    // reduce AI speed
    iVar4 = *(int *)(robot_2 + 0x5d4) + -3000;
    // can't go negative
    if (iVar4 < 0)
    {
      iVar4 = 0;
    }
    *(int *)(robot_1 + 0x5d4) = iVar4;
  }
  else
  {
    // reduce AI speed
    iVar4 = *(int *)(robot_1 + 0x5d4) + -3000;
    // can't go negative
    if (iVar4 < 0)
    {
      iVar4 = 0;
    }
    *(int *)(robot_2 + 0x5d4) = iVar4;
  }
  return;
}