#include <common.h>

void DECOMP_LoadSave_LoadProfileFromHub_MenuBoxFuncPtr(struct MenuBox* mb)
{
  struct GameTracker* gGT = sdata->gGT;

  // set level ID to main menu
  gGT->levelID = 0x27;

  // change character ID to icon ID
  data.characterIDs[0] = sdata->advProgress.characterID;

  // Load AdvHub LEV depending on new profile
  MainRaceTrack_RequestLoad(gGT->currLEV);

  // make MenuBox invisible
  MENUBOX_Hide(mb);
  return;
}