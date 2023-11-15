#include <common.h>

void DECOMP_MM_Scrapbook_Init(void)
{
    D230.scrapbookState = 0;

    // change checkered flag
    DECOMP_TitleFlag_SetDrawOrder(1);

    // clear gamepad input (for menus)
    MENUBOX_ClearInput();
}
