#include <common.h>

void DECOMP_RB_MakeInstanceReflective(struct ScratchpadStruct* sps, struct Instance* inst)
{
    u_short quadFlags;
    struct GameTracker* gGT = sdata->gGT;

    if ((sps->boolDidTouchQuadblock == 0) || (sps->boolDidTouchHitbox != 0))
    {
        inst->bitCompressed_NormalVector_AndDriverIndex = 0x4000;
    }
    else
    {
        inst->bitCompressed_NormalVector_AndDriverIndex =
            (u_int)(sps->Set2.normalVec[0] >> 6) & 0xff |
            ((u_int)sps->Set2.normalVec[1] & 0x3fc0) << 2 |
            ((u_int)(sps->Set2.normalVec[2] >> 6) & 0xff) << 0x10;

        // quit if more than one player
        if (1 < gGT->numPlyrCurrGame)
            return;

        // if there is one player
        quadFlags = ((struct QuadBlock *)sps->Set2.ptrQuadblock)->quadFlags;

        if ((quadFlags & 0x2000) == 0)
        {
            // visible?
            if ((quadFlags & 1) != 0)
            {
                // make instance reflective
                inst->flags |= REFLECTIVE;
                inst->vertSplit = gGT->level1->splitLines[2];

                return;
            }

            // reflective (ice)
            if ((quadFlags & 4) != 0)
            {
                // make instance reflective
                inst->flags |= REFLECTIVE;
                inst->vertSplit = gGT->level1->splitLines[0];

                return;
            }
        }
    }

    // instance is not reflective
    inst->flags &= ~(REFLECTIVE);
}