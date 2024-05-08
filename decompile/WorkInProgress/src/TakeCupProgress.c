#include <common.h>

void DECOMP_TakeCupProgress_MenuProc(struct RectMenu* menu)
{
    if (menu->unk1e == 1)
    {
        // if there is a string to print
        if (sdata->stringIndexSaveCupProgress)
        {
            // print "Save your cup progress?"
            // and optionally "New Battle Arena Opened!"

            DecalFont_DrawMultiLine(
				sdata->lngStrings[sdata->stringIndexSaveCupProgress],
                
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
        short row = menu->rowSelected;
        // choose "yes"
        if (row == 0)
        {
            sdata->unk_saveGame_related = 1;

            // Set Load/Save to "Slot Selected" mode
            SelectProfile_ToggleMode(0x41);

            // Change active Menu to Warning
            sdata->ptrDesiredMenu = &data.menuWarning2;
        }
        else
        {
            // invalid row
            if ((row != -1) || (row != 1)) return;
            
            // Make the menu disappear
            RECTMENU_Hide(mb);
        }
    }
}