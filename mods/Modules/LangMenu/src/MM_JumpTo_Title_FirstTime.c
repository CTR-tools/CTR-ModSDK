#include <common.h>

void MM_JumpTo_Title_FirstTime(void)
{
    struct GameTracker *gGT = sdata->gGT;

    MM_ResetAllMenus();

    MainStats_ClearBattleVS();

    sdata->ptrActiveMenuBox = MM_Menubox_LanguageBoot(gGT);

    D230.timerInTitle = 0;

    // first time in main menu
    // (play crash trophy anim)
    D230.MM_State = 0;

    // reset countdown clock for battle or crystal challenge
    gGT->originalEventTime = 0x2a300;

    D230.menubox_mainMenu.state &= ~(EXECUTE_FUNCPTR | ONLY_DRAW_TITLE);
    D230.menubox_mainMenu.state |= DISABLE_INPUT_ALLOW_FUNCPTRS;

    // distance to screen (perspective)
    gGT->tileView[0].distanceToScreen_PREV = 0x100;
    gGT->tileView[0].distanceToScreen_CURR = 0x100;
    gGT->gameMode1 &= ~(TIME_TRIAL);
}