#include <common.h>

void GhostBuffer_InitRecording(void)
{
  struct GhostHeader* gh;
  struct Driver* d;
  struct GameTracker* gGT = sdata->gGT;
  
  d = gGT->drivers[0];

  gh = sdata->GhostRecording.ptrGhost;
  gh->magic = 0xFFFC;
  gh->levelID = gGT->levelID;
  gh->characterID = data.characterIDs[d->driverID];

  sdata->GhostRecording.VelX = 0;
  sdata->GhostRecording.VelY = 0;
  sdata->GhostRecording.VelZ = 0;

  sdata->GhostRecording.timeElapsedInRace = 0;
  sdata->boolGhostTooBigToSave = 0;
  sdata->ghostOverflowTextTimer = 0;
  sdata->boolCanSaveGhost = 1;
  
  sdata->GhostRecording.ptrCurrOffset = sdata->GhostRecording.ptrStartOffset;
  
  sdata->GhostRecording.countEightFrames = 0;
  sdata->GhostRecording.countSixteenFrames = 0;
  sdata->GhostRecording.timeOfLast80buffer = 0;
  sdata->GhostRecording.boostCooldown1E = 0;

  sdata->GhostRecording.animFrame = -1;
  sdata->GhostRecording.animIndex = -1;
  sdata->GhostRecording.instanceFlags = 0;

  return;
}