#include <common.h>

void DECOMP_MainFreeze_IfPressStart(void)
{
    struct GameTracker* gGT = sdata->gGT;

    // Check conditions for pausing the game
    if (
        (DECOMP_TitleFlag_IsFullyOnScreen() == 0) &&

        // if you are not drawing loading screen (after fully off screen)
        ((gGT->renderFlags & 0x1000) == 0) &&

        (sdata->AkuAkuHintState == 0) &&
        (sdata->ptrActiveMenuBox == 0) &&
		((gGT->gameMode1 & (END_OF_RACE | PAUSE_ALL | GAME_CUTSCENE)) == 0) &&
        (gGT->levelID != MAIN_MENU_LEVEL) &&
		(gGT->boolDemoMode == 0) &&
		((u_int)(gGT->levelID - OXIDE_ENDING) > 1) &&
		(sdata->load_inProgress == 0) &&
		((gGT->gameMode2 & 4) == 0)
	   )
    {
        // pause the game
        gGT->gameMode1 |= PAUSE_1;

        // set row selected to the top row
        struct MenuBox *mb = DECOMP_MainFreeze_GetMenuBox();
        mb->rowSelected = 0;

        DECOMP_MENUBOX_Show(mb);

        // pause audio
        DECOMP_MainFrame_TogglePauseAudio(1);

        DECOMP_OtherFX_Play(1, 1);

        DECOMP_ElimBG_Activate(gGT);
    }
}
