#include <common.h>

uint8_t DECOMP_MEMCARD_GetNextHwEvent(void)
{
	// IOE = IO End, meaning "finished without error"
    if (TestEvent(sdata->HwCARD_EvSpIOE))	return MC_RETURN_IOE;
    if (TestEvent(sdata->HwCARD_EvSpERROR))	return MC_RETURN_TIMEOUT;
    if (TestEvent(sdata->HwCARD_EvSpTIMOUT))return MC_RETURN_NOCARD;
    if (TestEvent(sdata->HwCARD_EvSpNEW))	return MC_RETURN_NEWCARD;

    return MC_RETURN_PENDING;
}