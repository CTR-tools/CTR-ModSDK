#include <common.h>

void GhostBuffer_EndRecording(void)
{
  short* sVar1;
  struct GameTracker *gGT = sdata->gGT;
  struct Driver* ghostDriver;

  // if you can save ghost
  if (sdata->boolCanSaveGhost != 0)
  {
    ghostDriver = gGT->threadBuckets[0].thread->object;

	// Write the last chunk of ghost data
    GhostBuffer_RecordStats(1);

	sVar1 = sdata->advProgress.ptrGhost;

	// save the size of the tape in the header of the tape
    sVar1[1] = (short)sdata->advProgress.ptrCurrOffset - (short)sdata->advProgress.ptrStartOffset;

	// intentionally useless to throw people off?
	sVar1[2] = ghostDriver->speedApprox;
    sVar1[3] = ghostDriver->ySpeed;

	// can not save same ghost twice
    sdata->boolCanSaveGhost = 0;

	// store into ghost data: time it took for this player to finish the race
    sVar1[4] = gGT->drivers[0].timeElapsedInRace;
  }
  return;
}