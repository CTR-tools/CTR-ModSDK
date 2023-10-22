#include <common.h>

void COLL_PerQuadblock_CheckTriangles_Touching(struct QuadBlock *ptrQuad, struct ScratchpadStruct *searchResult)
{
    // ??? used to write to quadBlocksRendered ???
    // "at + 100 = 80096404" from 226 ? which is quadblocksrendered
    (struct QuadBlock *)(searchResult->unk4C[0x18]) = ptrQuad;

    if (
        (
            (
                // quadblock flags
                ((searchResult->Union.QuadBlockColl.searchFlags & ptrQuad->quadFlags) != 0) &&

                // quadblock flags
                ((searchResult->Union.QuadBlockColl.unk28 & ptrQuad->quadFlags) == 0)) &&

            ((ptrQuad->bbox.min[0] >> 0x10) - searchResult->bbox.max[1] < 1)) &&

        ((
            (
                ptrQuad->bbox.min[0] - searchResult->bbox.max[0] < 1 &&

                (searchResult->bbox.min[0] - (ptrQuad->bbox.min[2] >> 0x10) < 1)) &&

            ((
                ptrQuad->bbox.min[2] - searchResult->bbox.max[2] < 1 &&

                (searchResult->bbox.min[2] - (ptrQuad->bbox.max[1] >> 0x10) < 1))))))
    {
        if (searchResult->bbox.min[1] - ptrQuad->bbox.max[1] < 1)
        {
            // if 3P or 4P mode,
            // then use low-LOD quadblock collision (two triangles)
            if ((searchResult->Union.QuadBlockColl.unk22 & 2) == 0)
            {
                COLL_TestQuadblock_TwoTris(searchResult, ptrQuad);

                // call COLL_TestTriangle_FindAny two times, one per triangle

                COLL_TestTriangle_FindAny(0x1f800108, 0x1f8001f8, 0x1f80020c, 0x1f800220); // 0,1,2
                if (ptrQuad->index[2] >> 0x10 != (ptrQuad->index[2] & 0xffff))
                {
                    COLL_TestTriangle_FindAny(0x1f800108, 0x1f80020c, 0x1f800234, 0x1f800220); // 1,3,2
                }
            }
            else
            {
                if ((searchResult->Union.QuadBlockColl.unk22 & 8) == 0)
                {
                    COLL_TestQuadblock_EightTris(searchResult, ptrQuad);
                }

                // call COLL_TestTriangle_FindAny eight times, one per triangle

                // all values are offset 0x10 from what they should be, for some reason?

                COLL_TestTriangle_FindAny(0x1f800118, 0x1f8002a8, 0x1f800280, 0x1f800294); // 8, 6, 7
                COLL_TestTriangle_FindAny(0x1f800118, 0x1f800294, 0x1f800244, 0x1f8002a8); // 7, 3, 8
                COLL_TestTriangle_FindAny(0x1f800118, 0x1f80021c, 0x1f800294, 0x1f800280); // 1, 7, 6
                COLL_TestTriangle_FindAny(0x1f800118, 0x1f800230, 0x1f800280, 0x1f8002a8); // 2, 6, 8
                if (ptrQuad->index[2] >> 0x10 != (ptrQuad->index[2] & 0xffff))
                {
                    COLL_TestTriangle_FindAny(0x1f800118, 0x1f800208, 0x1f800258, 0x1f80026c); // 0, 4, 5
                    COLL_TestTriangle_FindAny(0x1f800118, 0x1f800258, 0x1f800280, 0x1f80026c); // 4, 6, 5
                    COLL_TestTriangle_FindAny(0x1f800118, 0x1f800280, 0x1f800258, 0x1f80021c); // 6, 4, 1
                    COLL_TestTriangle_FindAny(0x1f800118, 0x1f80026c, 0x1f800280, 0x1f800230); // 5, 6, 2
                    return;
                }
            }
        }
    }
}