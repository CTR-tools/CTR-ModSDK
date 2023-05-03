#include <common.h>

//- basically gets index of first triggered event or returns 7, which is no event i guess. 7 is 3 bits.
// TODO: Use an enum instead of returning ints 
uint8_t MEMCARD_GetNextSlot1Event(void)
{
    if (TestEvent(sdata->SwCARD_EvSpIOE) != 1)
    {
        if (TestEvent(sdata->SwCARD_EvSpERROR) != 1)
        {
            if (TestEvent(sdata->SwCARD_EvSpTIMOUT) == 1)
            {
                return 2; // no card
            }
            else if (TestEvent(sdata->SwCARD_EvSpNEW) != 1)
            {
                return 7; // new card
            }
        }
        return 1; // bad card
    }
    return 0; // processing done
}

/*
MC_EVENT_NONE = 0
MC_EVENT_NO_CARD = 1
MC_EVENT_BAD_CARD = 2
MC_EVENT_NEW_CARD = 3
MC_EVENT_NOT_FORMATTED = 4
MC_EVENT_FILE_NOT_EXISTS = 5
MC_EVENT_FILE_ALREADY_EXISTS = 6
MC_EVENT_BLOCKS_FULL = 7
*/