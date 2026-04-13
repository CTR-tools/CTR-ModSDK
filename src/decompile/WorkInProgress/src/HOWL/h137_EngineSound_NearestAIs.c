#include <common.h>

void DECOMP_EngineSound_NearestAIs(void)
{
  struct GameTracker *gGT;
  struct PushBuffer* pb;
  struct Driver *robot;
  struct Driver* player;
  struct Thread *t;
  VECTOR v;
  short sVar1;
  int dist;
  int distX;
  int distY;
  int distZ;
  long lVar5;
  int volume;
  int *piVar9;
  int iVar10;
  int params[4];
  short local_38[4];

  gGT = sdata->gGT;

  // This function is only executed if number
  // of AIs is not zero, so this check here
  // is mildly redundant

  // If number of AIs is not zero
  if (gGT->numBotsNextGame)
  {

    params[0] = 0;
    params[1] = 0;
    params[2] = 0x7fffffff;
    params[3] = 0x7fffffff;

    t = gGT->threadBuckets[ROBOT].thread;

    while (t != NULL)
    {
      robot = t->object;
      // if numPlyrCurrGame is not zero
      if (gGT->numPlyrCurrGame)
      {
        // loop for number of players (max 2)
        for (iVar10 = 0; iVar10 < 2; iVar10++)
        {
          // pushBuffer
          pb = gGT->pushBuffer[iVar10];

          // Subtract robotcar position from pushBuffer position
          distX = pb->pos[0] - (short)robot->posCurr.x;
          distY = pb->pos[1] - (short)robot->posCurr.y;
          distZ = pb->pos[2] - (short)robot->posCurr.z;

          // Distance formula in 3D
          dist = SquareRoot0(distX * distX + distY * distY + distZ * distZ);

          // find which robotcar is closest and farthest?

          sVar1 = local_38[0];
          distX = params[0];

          if (dist < params[2])
          {
            // set loop index
            local_38[0] = iVar10;
            params[3] = params[2];
            params[2] = distY;

            // robotcar Driver object
            params[0] = robot;

            local_38[1] = sVar1;
            params[1] = distX;
          }
          else
          {
            if (distY < params[3])
            {
              local_38[1] = iVar10;
              params[3] = distY;

              // robotcar Driver object
              params[1] = robot;
            }
          }
        }
      }

      // robotcar->next
      t = t->siblingThread;
    }

    // loop twice, max of 2 players
    // can hear AI audio
    for (sVar1 = 0; sVar1 < 2;sVar1++)
    {
      robot = params[sVar1];
      if (robot != NULL)
      {
        player = gGT->cameraDC[local_38[sVar1]].driverToFollow;

        // param1 - matrix
        // param2 - driver
        // param3 - return vector
        GTE_AudioLR_Driver(gGT->pushBuffer[local_38[sVar1]].matrix_Camera, robot, v);

        // direction X and Z from previous function
        lVar5 = ratan2(v.vx, -v.vz);

        iVar10 = (lVar5 + 0x800) * -0x100000 >> 0x17;
        if (iVar10 < 0x81)
        {
          distX = -0x100;
          if (iVar10 < -0x80)
            goto LAB_8003014c;
        }
        else
        {
          distX = 0x100;
        LAB_8003014c:
          iVar10 = distX - iVar10;
        }

		char* arr3 = &sdata->audioDefaults[4];
        volume = EngineSound_VolumeAdjust(iVar10 + 0x80, arr3[sVar1], 10);
        arr3[sVar1] = volume;

        piVar9 = params[sVar1] + 2;

		char* arr2 = &sdata->audioDefaults[2];
        EngineSound_AI(robot, player, sVar1, *piVar9, *piVar9 - arr2[sVar1], volume);
        arr2[sVar1] = *piVar9;
      }
    }
  }
  return;
}
