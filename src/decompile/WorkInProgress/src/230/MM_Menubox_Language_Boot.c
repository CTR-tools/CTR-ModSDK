#include <common.h>

// This menu and func only found in EurRetail
void MM_MenuProc_LanguageBoot(struct RectMenu* menu)
{
    struct GameTracker* gGT = sdata->gGT;

    if (menu->unk1e == 1) // player input flag?
    {
        // if anyone move the menu cursor
        if (sdata->gGamepads->anyoneHeldCurr != 0)
        {
            // reset menu timer
            D230.langMenuTimer = 900;
        }

        D230.langMenuTimer--;

        // if the timer ran out, 
        // automatically choose current selection (do the rest of the func)
        if (-1 < D230.langMenuTimer)
        {
            return;
        }
    }
    
    // Language change flag
    gGT->gameMode2 |= 0x10000000;  

    //langIndex on PAL gGT
    gGT[0x1D58] = D230.fileIndexLngBoot[menu->rowSelected]; // why need a separate index array???

    // always goes to main menu after lang chosen
    sdata->ptrDesiredMenu = &D230.menuMainMenu; 

    // tell game not to call this menu again
    sdata->boolLangChosen = 1; 

    menu->ptrPrevBox_InHierarchy->state &= ~(DRAW_NEXT_MENU_IN_HIERARCHY | ONLY_DRAW_TITLE);
}
