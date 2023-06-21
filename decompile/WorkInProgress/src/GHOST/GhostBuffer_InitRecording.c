#include <common.h>

void GhostBuffer_InitRecording(void)
{
  int *puVar1;
  struct Driver* ghostDriver;
  struct GameTracker* gGT = sdata->gGT;

  // pointer to start of ghost tape
  puVar1 = sdata->advProgress.ptrGhost;

  // pointer to first Player thread, -> object
  ghostDriver = gGT.threadbuckets[0]->thread->object;

  // Save level ID in the header of the ghost tape
  *(short *)(sdata->advProgress.ptrGhost + 4) = gGT->levelID;

  *puVar1 = 0xfc;
  puVar1[1] = 0xff;

  sdata->boolGhostTooBigToSave = 0;

  sdata->ghostOverflowTextTimer = 0;

  // bool canSaveGhost
  sdata->boolCanSaveGhost = 1;

  // Player / AI structure + 0x4a shows driver index (0-7)

  *(short *)(puVar1 + 6) = data.characterIDs[ghostDriver->driverID];

  // set offset of ghost recording to start of ghost recording
  sdata->GhostRecording.ptrCurrOffset = sdata->GhostRecording.ptrStartOffset;

  // Frame counter
  sdata->GhostRecording.countEightFrames = 0;

  // Frame counter
  sdata->GhostRecording.countSixteenFrames = 0;

  // time of last 0x80 ghost buffer
  sdata->GhostRecording.timeOfLast80buffer = 0;

  // Timer to measure amount of milliseconds in a race
  sdata->GhostRecording.timeElapsedInRace = 0;

  // Frames since last ghost writting,
  // limits writing to every 0x1e frames
  sdata->GhostRecording.framesSinceLastGhostWritting1E = 0;

  // Velocity X, Y, Z
  sdata->GhostRecording.VelX = 0;
  sdata->GhostRecording.VelY = 0;
  sdata->GhostRecording.VelZ = 0;

  // set animation ID and animation frame
  // being recorded for ghosts, to -1,
  // and set instance flags to zero
  sdata->GhostRecording.animationID = 0xffffffff;
  sdata->GhostRecording.animationFrame = 0xffffffff;
  sdata->GhostRecording.instanceFlags = 0;

  return;
}