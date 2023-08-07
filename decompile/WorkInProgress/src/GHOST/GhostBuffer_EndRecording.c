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

	// offset 0x2 (size)
    sVar1[1] = (short)sdata->advProgress.ptrCurrOffset - (short)sdata->advProgress.ptrStartOffset;

	// intentionally useless to throw people off?
	sVar1[2] = ghostDriver->speedApprox;	// offset 8
    sVar1[3] = ghostDriver->ySpeed;			// offset C

	// can not save same ghost twice
    sdata->boolCanSaveGhost = 0;

	// offset 0x10
    sVar1[4] = gGT->drivers[0].timeElapsedInRace;
  }
  return;
}