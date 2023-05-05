#include <common.h>

// TODO: Use enum
uint8_t MEMCARD_GetNextHwEvent(void)
{
    uint8_t result;

    // (processing done)
    result = 0;
    if (TestEvent(sdata->HwCARD_EvSpIOE) != 1)
    {
        // (bad card)
        result = 1;
        if (TestEvent(sdata->HwCARD_EvSpERROR) != 1)
        {
            // (no card)
            if (TestEvent(sdata->HwCARD_EvSpTIMOUT) == 1)
            {
                result = 2;
            }
            else
            {
                result = 3;
                if (TestEvent(sdata->HwCARD_EvSpNEW) != 1)
                {
                    result = 7;
                }
            }
        }
    }
    return result;
}