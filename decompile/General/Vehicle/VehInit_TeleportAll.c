#include <common.h>

void DECOMP_VehInit_TeleportAll(struct GameTracker *gGT, u_int spawnFlags)
{
  struct Driver* d;

  for (int i = 0; i < 8; i++)
  {
    d = gGT->drivers[i];

    if (d == NULL) continue;
    
    if (d->instSelf->thread->modelIndex == DYNAMIC_ROBOT_CAR)
    {
        BOTS_GotoStartingLine(d);
    }
	
    else
    {
        VehInit_TeleportSelf(d, spawnFlags | 1, 0);
    }
  }
}