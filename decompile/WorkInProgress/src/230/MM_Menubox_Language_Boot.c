#include <common.h>

// This menubox and func only found in EurRetail
void MM_MENUBOX_LanguageBoot(struct MenuBox *mb)
{
    struct GameTracker* gGT = sdata->gGT;

    if (mb->unk1e == 1) // player input flag?
    {
        // if anyone move the menu cursor
        if (sdata->gGamepads->anyoneHeldCurr != 0)
        {
            // reset menu timer
            OVR_230.langMenuTimer = 900;
        }

        OVR_230.langMenuTimer--;

        // if the timer ran out, 
        // automatically choose current selection (do the rest of the func)
        if (-1 < OVR_230.langMenuTimer)
        {
            return;
        }
    }
    
    // Language change flag
    gGT->gameMode2 |= 0x10000000;  

    //langIndex on PAL gGT
    gGT[0x1D58] = OVR_230.langIndex_Boot[mb->rowSelected]; // why need a separate index array???

    // always goes to main menu after lang chosen
    sdata->ptrDesiredMenuBox = &OVR_230.menubox_mainMenu; 

    // tell game not to call this menu again
    sdata->boolLangChosen = 1; 

    mb->ptrPrevBox_InHierarchy->state &= ~(DRAW_NEXT_MENU_IN_HIERARCHY | ONLY_DRAW_TITLE);
}
