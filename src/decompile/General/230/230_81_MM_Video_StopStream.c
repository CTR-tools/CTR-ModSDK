#include <common.h>

void DECOMP_MM_Video_StopStream(void)
{
    int iVar1;

    iVar1 = CdDiskReady(1);
    if (iVar1 == 2)
    {
        do
        {
            // 9 = CdlPause
            iVar1 = CdControl(9, 0, 0);

        } while (iVar1 == 0);
    }

    StClearRing();

    StSetMask(1, 0, 0);

    CdDataCallback(0);

    CdReadyCallback(0);

    // Discontinue current decoding,
    // does not affect internal states (libref)
    DecDCTReset(1);

    V230.drawNextFrame = 0;
}
