#include <common.h>

void MM_JumpTo_Title_Returning(void)
{
  // return to main menu
  sdata->ptrDesiredMenuBox = &OVR_230.menubox_mainMenu;
  
  // return to main menu from another menu
  OVR_230.MM_State = 3;
  
  OVR_230.countMeta0xD = OVR_230.title_OtherStuff[0];
  return;
}

void MM_JumpTo_Title_FirstTime(void)
{
  struct GameTracker *gGT = sdata->gGT;
  
  // MainMenu_ResetAllMenuBoxes
  MM_ResetAllMenus();
  
  // MainStats_ClearBattleVS
  MainStats_ClearBattleVS();
  
  // return to main menu
  sdata->ptrActiveMenuBox = &OVR_230.menubox_mainMenu;
  
  OVR_230.unkTimerMM = 0;
  
  // first time in main menu
  // (play crash trophy anim)
  OVR_230.MM_State = 0;
  
  // reset countdown clock for battle or crystal challenge
  gGT->originalEventTime = 0x2a300;
  
  OVR_230.menubox_mainMenu.state &= 0xfffffbfb | 0x20;
  
  // distance to screen (perspective)
  gGT->tileView[0].distanceToScreen_PREV = 0x100;
  gGT->tileView[0].distanceToScreen_CURR = 0x100;
  
  gGT->gameMode1 &= 0xfffdffff;
  
  return;
}

void MM_JumpTo_BattleSetup(void)
{
  // Go to battle setup
  sdata->ptrActiveMenuBox = &OVR_230.menubox_battleWeapons;
  
  OVR_230.menubox_battleWeapons.state &= 0xfffffffb;
  
  MM_Battle_Init();
  return;
}

void MM_JumpTo_TrackSelect(void)
{
  // return to track selection
  sdata->ptrActiveMenuBox = &OVR_230.menubox_trackSelect;
  
  OVR_230.menubox_trackSelect.state &= 0xfffffffb;
  
  // MM_TrackSelect_Init
  MM_TrackSelect_Init();
  return;
}


void MM_JumpTo_Characters(void)
{
  // return to character selection
  sdata->ptrActiveMenuBox = &OVR_230.menubox_characterSelect;
  
  OVR_230.menubox_characterSelect.state &= 0xfffffffb;
  
  MM_Characters_RestoreIDs();
  return;
}

void MM_JumpTo_Scrapbook(void)
{
  // go to scrapbook
  sdata->ptrActiveMenuBox = &OVR_230.menubox_scrapbook;
  
  OVR_230.menubox_scrapbook.state &= 0xfffffffb;
  
  MM_Scrapbook_Init();
  return;
}