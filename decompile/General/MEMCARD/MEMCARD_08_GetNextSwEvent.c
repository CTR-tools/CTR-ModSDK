#include <common.h>

uint8_t DECOMP_MEMCARD_GetNextSwEvent(void)
{
    if (TestEvent(sdata->SwCARD_EvSpIOE))	return MC_EVENT_DONE;
	if (TestEvent(sdata->SwCARD_EvSpERROR))	return MC_EVENT_BAD_CARD;
	if (TestEvent(sdata->SwCARD_EvSpTIMOUT))return MC_EVENT_NO_CARD;
	if (TestEvent(sdata->SwCARD_EvSpNEW))	return MC_EVENT_NEW_CARD;
    
	return MC_EVENT_NONE;
}
