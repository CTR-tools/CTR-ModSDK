#include <common.h>

void DECOMP_LoadSave_OneProfile_MenuBoxFuncPtr(struct MenuBox *mb)
{
    // if have not chosen any option
    // if you see current profile, and load/save/delete/exit rows
    if (mb->unk1e != 0)
    {
        LoadSave_Init((int)mb->drawStyle);
        LoadSave_DrawAdvProfile(&sdata->advProgress.rewards[0], 0x92, 0x32, 0, 0, 0x10);
        return;
    }

    // only here if you chose one of the rows (save/load/delete/exit)

    // get value of row selected
    short row = mb->rowSelected;

    // if submenu row is less than 3 and not -1
    if (row < 3 && row >= 0)
    {
        // Set Load/Save to "Green" mode, remembering the last selected row
        LoadSave_ToggleMode((row | 0x20));

        // Set MenuBox to a menu box that draws four adv profiles
        sdata->ptrDesiredMenuBox = &data.MENUBOX_DrawSelfFourAdvProfiles;
        return;
    }

    // if row is not 3, invalid row
    if (row != 3)
    {
        return;
    }

    // make MenuBox invisible
    MENUBOX_Hide(mb);

    // LoadSave_Destroy
    LoadSave_Destroy();
}
