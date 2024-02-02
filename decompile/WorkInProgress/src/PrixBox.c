#include <common.h>

//  (beta 'Arcade' was Gran Prix)
// Only called from 233, when you are at the cup
// podium and you need to save progress
void DECOMP_PrixSaveBox_Activate(short stringIndex)
{
    // string index to print
    sdata->stringIndexSaveCupProgress = stringIndex;

    // Draw the menu
    // for "Save Game", "yes / no"
    MENUBOX_Show(&data.menuBox_saveGame);
}

void DECOMP_PrixSaveBox_MenuBoxFuncPtr(struct MenuBox *mb)
{
    if (mb->unk1e == 1)
    {
        // if there is a string to print
        if (sdata->stringIndexSaveCupProgress)
        {
            // print "Save your cup progress?"
            // and optionally "New Battle Arena Opened!"

            DecalFont_DrawMultiLine(sdata->lngStrings[sdata->stringIndexSaveCupProgress],
                                //posx  posy 
                                256,    60, 
                                //maxlen, typefont
                                460,    FONT_BIG,
                                //Yellow, text flag
                                (0xffff0000 | JUSTIFY_CENTER));
        }
    }
    else
    {
        short row = mb->rowSelected;
        // choose "yes"
        if (row == 0)
        {
            sdata->unk_saveGame_related = 1;

            // Set Load/Save to "Slot Selected" mode
            LoadSave_ToggleMode(0x41);

            // Change active MenuBox to Warning
            sdata->ptrDesiredMenuBox = &data.menuBox_warning2;
        }
        else
        {
            // invalid row
            if ((row != -1) || (row != 1)) return;
            
            // Make the menu disappear
            MENUBOX_Hide(mb);
        }
    }
}