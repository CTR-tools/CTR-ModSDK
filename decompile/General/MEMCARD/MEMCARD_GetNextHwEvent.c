#include <common.h>

// TODO: Use enum, see MEMCARD_GetNextSwEvent
uint8_t DECOMP_MEMCARD_GetNextHwEvent(void)
{
    if (TestEvent(sdata->HwCARD_EvSpIOE))
    {
        return 0; // processing done
    }
    else if (TestEvent(sdata->HwCARD_EvSpERROR))
    {
        return 1; // bad card
    }
    else if (TestEvent(sdata->HwCARD_EvSpTIMOUT))
    {
        return 2; // no card
    }
    else if (TestEvent(sdata->HwCARD_EvSpNEW))
    {
        return 3; 
    }
    else
    {
        return 7; 
    }
}