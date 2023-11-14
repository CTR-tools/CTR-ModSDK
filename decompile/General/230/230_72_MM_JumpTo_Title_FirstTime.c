#include <common.h>

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

  OVR_230.timerInTitle = 0;

  // first time in main menu
  // (play crash trophy anim)
  OVR_230.MM_State = 0;

  // reset countdown clock for battle or crystal challenge
  gGT->originalEventTime = 0x2a300;

  OVR_230.menubox_mainMenu.state &= ~(EXECUTE_FUNCPTR | ONLY_DRAW_TITLE);
  OVR_230.menubox_mainMenu.state |= DISABLE_INPUT_ALLOW_FUNCPTRS;
  
  // distance to screen (perspective)
  gGT->tileView[0].distanceToScreen_PREV = 0x100;
  gGT->tileView[0].distanceToScreen_CURR = 0x100;
  gGT->gameMode1 &= ~(TIME_TRIAL);
}
 