#include <common.h>

void DECOMP_MM_ResetAllMenus(void)
{
    for (int i = 0; i < 9; i++)
    {
        struct RectMenu* menu = D230.arrayMenuPtrs[i];

        // Close menu
        menu->state |= 8;
        menu->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);

        // Reset ptrNext and ptrPrev
        menu->ptrNextBox_InHierarchy = 0;
        menu->ptrPrevBox_InHierarchy = 0;
    }

    sdata->framesRemainingInMenu = 0xF;
}