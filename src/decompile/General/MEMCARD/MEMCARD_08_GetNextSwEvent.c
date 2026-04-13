#include <common.h>

uint8_t DECOMP_MEMCARD_GetNextSwEvent(void)
{
	// IOE = IO End, meaning "finished without error"
    if (TestEvent(sdata->SwCARD_EvSpIOE))	return MC_RETURN_IOE;
	if (TestEvent(sdata->SwCARD_EvSpERROR))	return MC_RETURN_TIMEOUT;
	if (TestEvent(sdata->SwCARD_EvSpTIMOUT))return MC_RETURN_NOCARD;
	if (TestEvent(sdata->SwCARD_EvSpNEW))	return MC_RETURN_NEWCARD;
    
	return MC_RETURN_PENDING;
}
