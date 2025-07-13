#include <common.h>

uint8_t DECOMP_MEMCARD_GetNextHwEvent(void)
{
    if (TestEvent(sdata->HwCARD_EvSpIOE))	return MC_EVENT_DONE;
    if (TestEvent(sdata->HwCARD_EvSpERROR))	return MC_EVENT_BAD_CARD;
    if (TestEvent(sdata->HwCARD_EvSpTIMOUT))return MC_EVENT_NO_CARD;
    if (TestEvent(sdata->HwCARD_EvSpNEW))	return MC_EVENT_NEW_CARD;

    return MC_EVENT_NONE;
}