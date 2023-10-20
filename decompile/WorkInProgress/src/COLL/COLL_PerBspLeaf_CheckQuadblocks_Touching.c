#include <common.h>

void DECOMP_COLL_PerBspLeaf_CheckQuadblocks_Touching(struct BSP *node, struct ScratchpadStruct *sps)
{
    u_int numQuads;
    struct QuadBlock* ptrQuad;

    // if bsp flag is water
    if ((node->flag & 2) != 0)
    {
        sps->dataOutput[0] |= 0x8000;
    }

    numQuads = node->data.leaf.numQuads;

    ptrQuad = node->data.leaf.ptrQuadBlockArray;

    // loop through all quadblocks
    while (numQuads--)
    {
        COLL_PerQuadblock_CheckTriangles_Touching(ptrQuad, sps);
        ptrQuad++ // next quadblock
    };

    if ((sps->Union.QuadBlockColl.unk22 & 1) != 0)
    {
        COLL_PerBspLeaf_CheckInstances(node, sps);
    }
}
