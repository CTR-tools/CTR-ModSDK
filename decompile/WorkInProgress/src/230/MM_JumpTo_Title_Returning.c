#include <common.h>

void MM_JumpTo_Title_Returning(void)
{
  // return to main menu
  sdata->ptrDesiredMenuBox = &OVR_230.menubox_mainMenu;

  // return to main menu from another menu
  OVR_230.MM_State = 3;

  OVR_230.countMeta0xD = OVR_230.title_OtherStuff[0];
}

void MM_JumpTo_Title_FirstTime(void)
{
  struct GameTracker *gGT = sdata->gGT;

  MM_ResetAllMenus();

  MainStats_ClearBattleVS();

#if BUILD == EurRetail
  // if you have not chose a language or skipped the language menu
  if (sdata->boolLangChosen == 0)
  {
    sdata->ptrActiveMenuBox = &OVR_230.menubox_lngBoot;
    OVR_230.langMenuTimer = 900; 
  }
  else
  {
    // if not set to normal main menu
    sdata->ptrActiveMenuBox = &OVR_230.menubox_mainMenu;
  }

#else
  // open Main Menu for the first time
  sdata->ptrActiveMenuBox = &OVR_230.menubox_mainMenu;
#endif

  OVR_230.unkTimerMM = 0;

  // first time in main menu
  // (play crash trophy anim)
  OVR_230.MM_State = 0;

  // reset countdown clock for battle or crystal challenge
  gGT->originalEventTime = 0x2a300;

  OVR_230.menubox_mainMenu.state &= ~(EXECUTE_FUNCPTR | ONLY_DRAW_TITLE) | DISABLE_INPUT_ALLOW_FUNCPTRS;

  // distance to screen (perspective)
  gGT->tileView[0].distanceToScreen_PREV = 0x100;
  gGT->tileView[0].distanceToScreen_CURR = 0x100;
  gGT->gameMode1 &= ~(TIME_TRIAL);
}

void MM_JumpTo_BattleSetup(void)
{
  // Go to battle setup
  sdata->ptrActiveMenuBox = &OVR_230.menubox_battleWeapons;

  OVR_230.menubox_battleWeapons.state &= ~(ONLY_DRAW_TITLE);

  MM_Battle_Init();
}

void MM_JumpTo_TrackSelect(void)
{
  // return to track selection
  sdata->ptrActiveMenuBox = &OVR_230.menubox_trackSelect;

  OVR_230.menubox_trackSelect.state &= ~(ONLY_DRAW_TITLE);

  MM_TrackSelect_Init();
}

void MM_JumpTo_Characters(void)
{
  // return to character selection
  sdata->ptrActiveMenuBox = &OVR_230.menubox_characterSelect;

  OVR_230.menubox_characterSelect.state &= ~(ONLY_DRAW_TITLE);

  MM_Characters_RestoreIDs();
}

void MM_JumpTo_Scrapbook(void)
{
  // go to scrapbook
  sdata->ptrActiveMenuBox = &OVR_230.menubox_scrapbook;

  OVR_230.menubox_scrapbook.state &= ~(ONLY_DRAW_TITLE);

  MM_Scrapbook_Init();
}