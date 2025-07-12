#include <common.h>

// TODO: Use an enum instead of returning ints
uint8_t DECOMP_MEMCARD_GetNextSwEvent(void)
{
    if (TestEvent(sdata->SwCARD_EvSpIOE))
    {
        return 0; // processing done
    }
    else if (TestEvent(sdata->SwCARD_EvSpERROR))
    {
        return 1; // bad card
    }
    else if (TestEvent(sdata->SwCARD_EvSpTIMOUT))
    {
        return 2; // no card
    }
    else if (TestEvent(sdata->SwCARD_EvSpNEW))
    {
        return 3;
    }
    else
    {
        return 7;
    }
}
