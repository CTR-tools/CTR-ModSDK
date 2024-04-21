#include <common.h>

void DECOMP_COLL_PerBspLeaf_CheckQuadblocks_NearPlayer(struct BSP *node, struct ScratchpadStruct *sps)
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
        COLL_PerQuadblock_CheckTriangles_NearPlayer(ptrQuad++, sps);
    }

    if ((sps->Union.QuadBlockColl.searchFlags & 1) != 0)
    {
        COLL_PerBspLeaf_CheckInstances(node, sps);
    }
}
