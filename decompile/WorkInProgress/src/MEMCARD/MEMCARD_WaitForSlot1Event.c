#include <common.h>
//- only called once, wonder how that doesn't halt the exection. or maybe it does, are there hangs when save/load happens?
uint8_t MEMCARD_WaitForSlot1Event(void)
{
    // // NOTE: This impl is 8 bytes over budget
    // int result;
    // for (;;)
    // {
    //     // HwIOE (processing done)
    //     if ((result = TestEvent(sdata->HwCARD_EvSpIOE)) == 1)
    //     {
    //         return 0;
    //     }
    //     // HwERROR (bad card)
    //     if ((result = TestEvent(sdata->HwCARD_EvSpERROR)) == 1)
    //     {
    //         return 1;
    //     }
    //     // HwTIMEOUT (no card)
    //     if ((result = TestEvent(sdata->HwCARD_EvSpTIMOUT)) == 1)
    //     {
    //         return 2;
    //     }
    //     // HwNEWCARD
    //     if ((result = TestEvent(sdata->HwCARD_EvSpNEW)) == 1)
    //     {
    //         return 3;
    //     }
    // }

    int result;
    do
    {
        result = TestEvent(sdata->HwCARD_EvSpIOE);
        if (result) return result-1;
        result = TestEvent(sdata->HwCARD_EvSpERROR);
        if (result) return result;
        result = TestEvent(sdata->HwCARD_EvSpTIMOUT);
        if (result) return result+1;
        result = TestEvent(sdata->HwCARD_EvSpNEW);
    } while (!result);
    return result+2;
}