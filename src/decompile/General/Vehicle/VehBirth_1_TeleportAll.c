#include <common.h>

void DECOMP_VehBirth_TeleportAll(struct GameTracker *gGT, u_int spawnFlags)
{
  struct Driver* d;

  for (int i = 0; i < 8; i++)
  {
    d = gGT->drivers[i];

    if (d == NULL) continue;
    
	// desperate for byte budget here
    //if (d->instSelf->thread->modelIndex == DYNAMIC_ROBOT_CAR)
	if((d->actionsFlagSet & 0x00100000) != 0)
    {
		#ifndef REBUILD_PS1
        BOTS_GotoStartingLine(d);
		#endif
    }
	
    else
    {
		DECOMP_VehBirth_TeleportSelf(d, spawnFlags | 1, 0);
	}
  }
}