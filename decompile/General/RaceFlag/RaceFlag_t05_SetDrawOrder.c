#include <common.h>

void DECOMP_RaceFlag_SetDrawOrder(int drawOrder)
{
    sdata->RaceFlag_DrawOrder = (drawOrder != 0) ? 1 : -1;
}