#include <common.h>

void RB_Warpball_SetTargetDriver(struct TrackerWeapon *tw)
{
  int distance;
  int i, j;
  int local_20;
  int local_1c;

  struct GameTracker *gGT = sdata->gGT;

  // driver being chased
  struct Driver *target = tw->driverTarget;

  // if driver is valid
  if (target == NULL)
    return;

  distance = target->distanceToFinish_curr;

  // path node
  struct CheckpointNode *firstNode = &gGT->level->ptr_restart_points[0];
  struct CheckpointNode *currNode = &first[target->unknown_lap_related];

  // distance is less than path node distance
  while ((distance <= (thisNode->distToFinish << 3) &&

          // path node is not first node
          (currNode != firstNode)))
  {
    currNode = RB_Warpball_NewPathNode(currNode, tw->driverTarget);
  }

  target = NULL;
  local_1c = 0;
  thisNode = tw->ptrNodeCurr;

  if ((tw->flags & 4) == 0)
  {
    for (i = 0; i < 2; i++)
    {
      distance = *(int *)((int)&local_20 + (distance >> 0xe));
      if (distance != 0)
      {
        thisNode = 0;
        for (j = 0; j < 3; j++)
        {
          if (distance == currNode)
          {
            tw->flags = tw->flags & 0xfff7 | 4;
            break;
          }
          if (*(byte *)(distance + 0xb) != 0xff)
          {
            // path node
            local_1c = *(int *)(*(int *)(gGT + 0x160) + 0x14c) +
                       (uint) * (byte *)(distance + 0xb) * 0xc;
          }

          // path node
          distance = *(int *)(*(int *)(gGT + 0x160) + 0x14c) + (uint) * (byte *)(distance + 10) * 0xc;
        }
      }
    }
  }

  // path node
  thisNode = tw->ptrNodeCurr;

  for (i = 0; i < 3; i++)
  {
    if (thisNode == currNode)
    {
      tw->flags = tw->flags & ~(8) | 4;
      return;
    }
    target = RB_Warpball_NewPathNode(target, tw->driverTarget);
  }
}