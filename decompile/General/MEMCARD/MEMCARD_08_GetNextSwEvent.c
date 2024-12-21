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

/*
MC_EVENT_NONE = 0
MC_EVENT_BAD_CARD = 1
MC_EVENT_NO_CARD = 2
MC_EVENT_NEW_CARD = 3
MC_EVENT_NOT_FORMATTED = 4
MC_EVENT_FILE_NOT_EXISTS = 5
MC_EVENT_FILE_ALREADY_EXISTS = 6
MC_EVENT_BLOCKS_FULL = 7
*/