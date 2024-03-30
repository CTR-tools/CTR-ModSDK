#include <common.h>

u_int DECOMP_MM_Video_CheckIfFinished(int param_1)
{
    char bVar1;
    u_int uVar2;
    int iVar3;
    int local_20;
    int local_1c;

    local_20 = 40000;
    local_1c = 0x28;

    bVar1 = false;

    if (V230.drawNextFrame == 0)
    {
        uVar2 = 0;
    }
    else
    {

        do
        {
            if ((param_1 == 1) && (local_1c--, local_1c == 0))
            {
                iVar3 = CdDiskReady(1);
                
                if (iVar3 == 0x10)
                {
                    bVar1 = true;
                    V230.isDone = 1;
                }
                else
                {
                    local_1c = 0x28;
                }
            }

            local_20--;

            if (local_20 == 0)
            {
                V230.isDone = 1;
            }

        } while (!V230.isDone);

        do
        {
            iVar3 = IsIdleGPU(10000);

        } while (iVar3 != 0);

        V230.isDone = 0;

        V230.drawNextFrame = 0;

        if ((!bVar1) && (V230.frameCounter != V230.totalFrames))
        {
            // Discontinue current decoding,
            // does not affect internal states (libref)
            DecDCTReset(1);
        }

        // end of scrapbook
        uVar2 = (u_int)V230.field8_0x18;
    }
    return uVar2;
}
