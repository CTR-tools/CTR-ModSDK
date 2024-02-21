#include <common.h>

void DECOMP_CS_Garage_ZoomOut(char zoomState)
{
    // if just entered garage
    if (zoomState == 0)
    {
        // use no frames,
        // just use default zoomed out position
        *(short *)0x800b863c = 0;

        DECOMP_CS_Garage_Init();

		// howl
        Garage_Enter(sdata->advCharSelectIndex_curr);

        DECOMP_Audio_SetState_Safe(8);
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

    sdata->gGT->gameMode2 &= ~(GARAGE_OSK);
}