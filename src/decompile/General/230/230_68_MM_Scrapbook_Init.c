#include <common.h>

void DECOMP_MM_Scrapbook_Init(void)
{
    D230.scrapbookState = 0;

    // change checkered flag
    DECOMP_RaceFlag_SetDrawOrder(1);

    // clear gamepad input (for menus)
    DECOMP_RECTMENU_ClearInput();
}
