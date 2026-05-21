// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "COLL.h"

void fun_80020334(int param_1, int param_2, struct ScratchpadStructExtended* sps)
{
    int uVar1;
    int flagScrub;
    int iVar3;
    int* piVar4;
    int iVar5;
    int offset;

    // offsets 0xE and 0x22 fall inside the QuadBlockColl union region
    // of ScratchpadStruct; not split out as named fields here.
    uVar1 = *((short*)((char*)sps + 0x22));
    if (param_1 == 0)
    {
        *((u16*)((char*)sps + 0x22)) = uVar1 & 0xffdf;
        *((short*)((char*)sps + 0xe)) = 0;
        sps->numTriangles = 0;
        return;
    }

    iVar3 = sps->numTriangles + (-1);
    if ((-1) < iVar3)
    {
        flagScrub = uVar1 | 0x20;
        iVar5 = (iVar3 * 0xc) + 0x20c;
        do
        {
            piVar4 = (int*)((char*)sps + iVar5);
            if (((*piVar4) == param_1) && (piVar4[1] == param_2))
            {
                iVar3 = piVar4[2];
                if (iVar3 < 0x401)
                {
                    iVar3 = iVar3 + 0x100;
                    piVar4[2] = iVar3;
                }
                *((u16*)((char*)sps + 0x22)) = flagScrub;
                *((short*)((char*)sps + 0xe)) = (short)iVar3;
                return;
            }
            iVar3 = iVar3 + (-1);
            iVar5 = iVar5 + (-0xc);
        }
        while ((-1) < iVar3);
    }

    offset = (sps->numTriangles * 0xc) + 0x20c;
    piVar4 = (int*)((char*)sps + offset);
    *piVar4 = param_1;
    piVar4[1] = param_2;
    piVar4[2] = 0;
    *((u16*)((char*)sps + 0x22)) = uVar1 & 0xffdf;
    *((short*)((char*)sps + 0xe)) = 0;
    sps->numTriangles = sps->numTriangles + 1;
}
