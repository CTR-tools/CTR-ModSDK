#include <common.h>

void DECOMP_SelectProfile_AdvPickMode_MenuProc(struct RectMenu* menu)
{
    // if have not chosen any option
    // if you see current profile, and load/save/delete/exit rows
    if (menu->unk1e != 0)
    {
        SelectProfile_Init((int)menu->drawStyle);
        SelectProfile_DrawAdvProfile(&sdata->advProgress.rewards[0], 0x92, 0x32, 0, 0, 0x10);
        return;
    }

    // only here if you chose one of the rows (save/load/delete/exit)

    // get value of row selected
    short row = menu->rowSelected;

    // if submenu row is less than 3 and not -1
    if (row < 3 && row >= 0)
    {
        // Set Load/Save to "Green" mode, remembering the last selected row
        SelectProfile_ToggleMode((row | 0x20));

        // Set Menu to a menu box that draws four adv profiles
        sdata->ptrDesiredMenu = &data.menuFourAdvProfiles;
        return;
    }

    // if row is not 3, invalid row
    if (row != 3)
    {
        return;
    }

    // make Menu invisible
    RECTMENU_Hide(mb);

    // SelectProfile_Destroy
    SelectProfile_Destroy();
}
