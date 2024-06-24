#include <common.h>

void DECOMP_SelectProfile_QueueLoadHub_MenuProc(struct RectMenu* menu)
{
  struct GameTracker* gGT = sdata->gGT;

  // set level ID to main menu
  gGT->levelID = MAIN_MENU_LEVEL;

  // change character ID to icon ID
  data.characterIDs[0] = sdata->advProgress.characterID;

  // Load AdvHub LEV depending on new profile
  MainRaceTrack_RequestLoad(gGT->currLEV);

  // make Menu invisible
  RECTMENU_Hide(mb);
}