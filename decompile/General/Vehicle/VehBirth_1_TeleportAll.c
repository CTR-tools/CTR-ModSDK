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
		#ifndef REBUILD_PS1
		
		// original function for decomp or mods
        VehBirth_TeleportSelf(d, spawnFlags | 1, 0);
		
		#else
		
		// experimental buggy rewrite for PC port
		DECOMP_VehBirth_TeleportSelf(d, spawnFlags | 1, 0);
		
		#endif
    }
	
	#ifdef USE_60FPS
	// needed cause VehBirth_TeleportSelf
	// has not been rewritten yet for decomp
	d->instSelf->animFrame = FPS_DOUBLE(10);
	#endif
  }
}