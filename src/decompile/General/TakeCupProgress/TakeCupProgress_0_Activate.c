#include <common.h>

// Only called from 233, when you are at the cup
// podium and you need to save progress
void DECOMP_TakeCupProgress_Activate(short stringIndex)
{
    // string index to print
    sdata->stringIndexSaveCupProgress = stringIndex;

    // Draw the menu
    // for "Save Game", "yes / no"
    DECOMP_RECTMENU_Show(&data.menuSaveGame);
}