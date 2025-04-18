#include <common.h>

void DECOMP_COLL_FIXED_BSPLEAF_TestQuadblocks(struct BSP *node, struct ScratchpadStruct *sps)
{
    u_int numQuads;
    struct QuadBlock* ptrQuad;

    // if bsp flag is water
    if ((node->flag & 2) != 0)
    {
        *(int*)&sps->dataOutput[0] |= 0x8000;
    }

    numQuads = node->data.leaf.numQuads;
    ptrQuad = node->data.leaf.ptrQuadBlockArray;

    // loop through all quadblocks
    while (numQuads-- != 0)
    {
        COLL_FIXED_QUADBLK_TestTriangles(ptrQuad++, sps);
    }

    if ((sps->Union.QuadBlockColl.searchFlags & 1) != 0)
    {
        COLL_FIXED_BSPLEAF_TestInstance(node, sps);
    }
}
