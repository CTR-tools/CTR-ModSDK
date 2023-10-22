#include <common.h>

void DECOMP_CS_Garage_ZoomOut(char param_1)
{
    // if just entered garage
    if (param_1 == 0)
    {
        // use no frames,
        // just use default zoomed out position
        *(short *)0x800b863c = 0;

        Garage_Init();

        Garage_Enter(sdata->advCharSelectIndex_curr);

        Audio_SetState_Safe(8);
    }
    else
    {
        // number of frames to zoom in, or out,
        // when selecting or cancelling OSK
        *(short *)0x800b863c = *(short *)0x800b85cc;
    }

    *(short *)0x800b8638 = 0;
    *(short *)0x800b863e = 0;
    OVR_233.hasSelectedChar = 0;

    *(short *)0x800b863a = *(short *)0x800b863c;

    sdata->gGT->gameMode2 &= 0xfffdffff;
}