#include <common.h>

void DECOMP_RB_MakeInstanceReflective(struct ScratchpadStruct* param_1, struct Instance* inst)
{
    u_short quadFlags;
    struct GameTracker* gGT = sdata->gGT;

    if ((*(short *)(param_1 + 0x3e) == 0) || (*(short *)(param_1 + 0x42) != 0))
    {
        inst->bitCompressed_NormalVector_AndDriverIndex = 0x4000;
    }
    else
    {
        inst->bitCompressed_NormalVector_AndDriverIndex =
            (u_int)(*(short *)(param_1 + 0x70) >> 6) & 0xff |
            ((u_int) * (short *)(param_1 + 0x72) & 0x3fc0) << 2 |
            ((u_int)(*(short *)(param_1 + 0x74) >> 6) & 0xff) << 0x10;

        // quit if more than one player
        if (1 < gGT->numPlyrCurrGame)
        {
            return;
        }

        // if there is one player
        quadFlags = ((struct QuadBlock *)param_1 + 0x80)->quadFlags;

        if ((quadFlags & 0x2000) == 0)
        {
            // visible?
            if ((quadFlags & 1) != 0)
            {
                // make instance reflective
                inst->flags |= 0x4000;
                inst->vertSplit = gGT->level1->splitLines[2];

                return;
            }

            // reflective (ice)
            if ((quadFlags & 4) != 0)
            {
                // make instance reflective
                inst->flags |= 0x4000;
                inst->vertSplit = gGT->level1->splitLines[0];

                return;
            }
        }
    }

    // instance is not reflective
    inst->flags &= 0xffffbfff;

    return;
}