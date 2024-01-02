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
		#ifndef REBUILD_PS1
        BOTS_GotoStartingLine(d);
		#endif
    }
	
    else
    {
		#ifndef REBUILD_PS1
        VehInit_TeleportSelf(d, spawnFlags | 1, 0);
		#endif
    }
  }
}