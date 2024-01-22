#include <common.h>

void DECOMP_VehInit_EngineAudio_AllPlayers(void)
{
  // pointer to first Player thread
  struct Thread* th = sdata->gGT->threadBuckets[PLAYER].thread;

  // while pointer is valid
  while (th != NULL)
  {
    u_char playerID = ((struct Driver *)th->object)->driverID;

    // Initialize car engine sound
    EngineAudio_InitOnce(

        // engineID from metadata, given characterID
        (playerID + data.MetaDataCharacters[data.characterIDs[playerID]].engineID * 4) & 0xFFFF,

        // engine audio flags
        0x8080);

    // go to next Player in linked list
    th = th->siblingThread;
  }
}
