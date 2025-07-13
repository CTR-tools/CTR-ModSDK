#include <common.h>

uint8_t MEMCARD_WaitForHwEvent(void)
{
    while (1)
    {
		if (TestEvent(sdata->HwCARD_EvSpIOE))	return MC_EVENT_DONE;
		if (TestEvent(sdata->HwCARD_EvSpERROR))	return MC_EVENT_BAD_CARD;
		if (TestEvent(sdata->HwCARD_EvSpTIMOUT))return MC_EVENT_NO_CARD;
		if (TestEvent(sdata->HwCARD_EvSpNEW))	return MC_EVENT_NEW_CARD;
	
		// Not allowed to return NONE,
		// the goal is to keep going until "something" important happens
		// return MC_EVENT_NONE;
    }
}