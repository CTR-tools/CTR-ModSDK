#include <common.h>

void DECOMP_MainFreeze_IfPressStart(void)
{
    struct GameTracker *gGT = sdata->gGT;
    u_int gameMode = gGT->gameMode1;

    // Check conditions for pausing the game
    if (
        // if flag is not fully on screen
        (TitleFlag_IsFullyOnScreen() == 0) &&

        // if you are not drawing loading screen (after fully off screen)
        ((gGT->renderFlags & 0x1000) == 0) &&

        (gGT->overlayIndex_Threads != 3) &&

        // if not in a menu, time trial, and not paused yet
        (sdata->ptrActiveMenuBox == 0 && (gGT->gameMode1 & (END_OF_RACE | PAUSE_ALL | GAME_CUTSCENE)) == 0) &&

        // not in Main Menu and not in Demo Mode
        (gGT->levelID != MAIN_MENU_LEVEL && (gGT->boolDemoMode == 0)) &&

        // if game is not loading and not in a cutscene where you can't move
        ((1 < (gGT->levelID - OXIDE_ENDING) && (sdata->load_inProgress == 0 && (!(gGT->gameMode2 & 4)))) == 0))
    {
        // pause the game
        gGT->gameMode1 |= PAUSE_1;

        // set row selected to the top row
        struct MenuBox *mb = MainFreeze_GetMenuBox();
        mb->rowSelected = 0;

        // make menu visible
        MENUBOX_Show(mb);

        // pause audio
        MainFrame_TogglePauseAudio(1);

        // OtherFX_Play to pause
        OtherFX_Play(1, 1);

        // Activate pause menu
        ElimBG_Activate(gGT);
    }
}
