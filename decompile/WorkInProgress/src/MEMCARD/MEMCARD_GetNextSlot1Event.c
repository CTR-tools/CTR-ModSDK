#include <common.h>

//- basically gets index of first triggered event or returns 7, which is no event i guess. 7 is 3 bits.
uint8_t MEMCARD_GetNextSlot1Event(void)
{
    uint8_t result;

    // (processing done)
    result = 0;
    if (TestEvent(sdata->SwCARD_EvSpIOE) != 1)
    {
        // (bad card)
        result = 1;
        if (TestEvent(sdata->SwCARD_EvSpERROR) != 1)
        {
            // (no card)
            if (TestEvent(sdata->SwCARD_EvSpTIMOUT) == 1)
            {
                result = 2;
            }
            else
            {
                result = 3;
                if (TestEvent(sdata->SwCARD_EvSpNEW) != 1)
                {
                    result = 7;
                }
            }
        }
    }
    return result;
}