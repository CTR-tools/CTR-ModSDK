#include <common.h>

void DECOMP_VehBirth_EngineAudio_AllPlayers(void)
{
  struct Thread* th;
  struct GameTracker* gGT;
  gGT = sdata->gGT;

  for(
		th = gGT->threadBuckets[PLAYER].thread;
		th != 0;
		th = th->siblingThread
	)
  {
	struct Driver* d = th->object;
	
	#ifdef USE_ONLINE
	d = gGT->drivers[0];
	#endif
	
    u_char driverID = d->driverID;

	int engine = data.MetaDataCharacters
		[data.characterIDs[driverID]].engineID;

	#ifndef REBUILD_PS1
    EngineAudio_InitOnce((engine * 4) + driverID, 0x8080);
	#endif

	#ifdef USE_ONLINE
	return;
	#endif
  }
}
