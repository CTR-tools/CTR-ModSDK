#include <common.h>

uint8_t MEMCARD_WaitForHwEvent(void)
{
    while (1)
    {
		// IOE = IO End, meaning "finished without error"
		if (TestEvent(sdata->HwCARD_EvSpIOE))	return MC_RETURN_IOE;
		if (TestEvent(sdata->HwCARD_EvSpERROR))	return MC_RETURN_TIMEOUT;
		if (TestEvent(sdata->HwCARD_EvSpTIMOUT))return MC_RETURN_NOCARD;
		if (TestEvent(sdata->HwCARD_EvSpNEW))	return MC_RETURN_NEWCARD;
	
		// Not allowed to return PENDING, the goal is to 
		// wait until the memcard is not PENDING anymore
		// return MC_RETURN_PENDING;
    }
}