#include <common.h>

void DECOMP_TitleFlag_SetDrawOrder(int drawOrder)
{
    sdata->TitleFlag_DrawOrder = (drawOrder != 0) ? 1 : -1;
}