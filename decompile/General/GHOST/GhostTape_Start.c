#include <common.h>

void DECOMP_GhostTape_Start(void)
{
  struct GhostHeader* gh;
  struct Driver* d;
  struct GameTracker* gGT = sdata->gGT;
  
  d = gGT->drivers[0];

  // v1 - PizzaHut (June), Spyro2 (July)
  // v4 - Aug5, Aug14, Sep3, Retail

  gh = sdata->GhostRecording.ptrGhost;
  gh->version = -4;
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