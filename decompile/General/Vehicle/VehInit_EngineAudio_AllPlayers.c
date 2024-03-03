#include <common.h>

void DECOMP_VehInit_EngineAudio_AllPlayers(void)
{
  struct Thread* th;

  for(
		th = sdata->gGT->threadBuckets[PLAYER].thread;
		th != 0;
		th = th->siblingThread
	)
  {
    u_char driverID = ((struct Driver *)th->object)->driverID;

#ifndef REBUILD_PS1
    EngineAudio_InitOnce(

        4*data.MetaDataCharacters
			[data.characterIDs[driverID]].engineID
		+ driverID,

        0x8080);
#endif
  }
}
