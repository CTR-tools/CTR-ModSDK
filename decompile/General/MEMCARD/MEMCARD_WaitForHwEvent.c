#include <common.h>
//- only called once, wonder how that doesn't halt the exection. or maybe it does, are there hangs when save/load happens?
uint8_t MEMCARD_WaitForHwEvent(void)
{
    // NOTE: This impl is 8 bytes over budget
    while (1)
    {
        // HwIOE (processing done)
        if (TestEvent(sdata->HwCARD_EvSpIOE))
        {
            return 0;
        }
        // HwERROR (bad card)
        else if (TestEvent(sdata->HwCARD_EvSpERROR))
        {
            return 1;
        }
        // HwTIMEOUT (no card)
        else if (TestEvent(sdata->HwCARD_EvSpTIMOUT))
        {
            return 2;
        }
        // HwNEWCARD
        else if (TestEvent(sdata->HwCARD_EvSpNEW))
        {
            return 3;
        }
    }
}