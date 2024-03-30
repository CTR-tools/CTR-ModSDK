#include <common.h>

void DECOMP_MM_Video_KickCD(CdlLOC *location)
{
    int iVar1;
    int CdlMode;
    u_char local_18[8];

    if ((location != NULL) && (V230.ptrCdLoc != &V230.cdLocation2))
    {
        V230.field12_0x20 = 0;
        V230.ptrCdLoc = location;
    }

    if (V230.field12_0x20 != 1)
    {
        if (1 < V230.field12_0x20)
        {
            if (V230.field12_0x20 == 2)
            {
                V230.field12_0x20 = 3;
                return;
            }

            if (V230.field12_0x20 != 3)
                return;

            // CdlModeStream2|CdlModeSpeed
            CdlMode = 0x1a0;

            // scrapbook
            // if video contains audio
            if ((V230.flags & 2) != 0)
            {
                // CdlModeStream2|CdlModeSpeed|CdlModeRT
                CdlMode = 0x1e0;
            }

            V230.field12_0x20 = 0;

            iVar1 = CdRead2(CdlMode);
            if (iVar1 == 0) return;

            V230.ptrCdLoc = 0;
            return;
        }

        if (V230.field12_0x20 != 0)
            return;

        // 2 = CdlSetloc
        iVar1 = CdControl(2, V230.ptrCdLoc, 0);
        if (iVar1 == 0) return;

        V230.field12_0x20 = 1;
    }

    // CdlModeSpeed
    local_18[0] = 0x80;

    // 0xe = CdlSetmode
    iVar1 = CdControl(0xe, local_18, 0);

    if (iVar1 != 0)
    {
        V230.field12_0x20 = 2;
    }
}
