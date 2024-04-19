#include <common.h>

void DECOMP_VehBirth_EngineAudio_AllPlayers(void)
{
  struct Thread* th;

  for(
		th = sdata->gGT->threadBuckets[PLAYER].thread;
		th != 0;
		th = th->siblingThread
	)
  {
    u_char driverID = ((struct Driver *)th->object)->driverID;

	int engine = data.MetaDataCharacters
		[data.characterIDs[driverID]].engineID;

#ifndef REBUILD_PS1
    EngineAudio_InitOnce((engine * 4) + driverID, 0x8080);
#endif
  }
}
