#include <common.h>

void COLL_PerQuadblock_CheckTriangles_Touching(struct QuadBlock *ptrQuad, struct ScratchpadStruct *sps)
{
	struct BspSearchVertex* bsv = &sps->bspSearchVert[0];
	
    *(int*)&sps->unk4C[0x18] = quad;

    if (
        ((sps->Union.QuadBlockColl.searchFlags & quad->quadFlags) != 0) &&
		((sps->Union.QuadBlockColl.unk28 & quad->quadFlags) == 0) &&
		(quad->bbox.min[0] < sps->bbox.max[0]) &&
		(quad->bbox.min[1] < sps->bbox.max[1]) &&
		(quad->bbox.min[2] < sps->bbox.max[2]) &&
        (sps->bbox.min[0] < quad->bbox.max[0]) &&
        (sps->bbox.min[1] < quad->bbox.max[1]) &&
        (sps->bbox.min[2] < quad->bbox.max[2])
		)
    {
        // if 3P or 4P mode,
        // then use low-LOD quadblock collision (two triangles)
        if ((sps->Union.QuadBlockColl.unk22 & 2) == 0)
        {
            COLL_TestQuadblock_TwoTris(sps, ptrQuad);

            COLL_TestTriangle_FindAny(sps, 0x1f8001f8, 0x1f80020c, 0x1f800220); // 0,1,2
            
			// If this is a quad instead of a triangle
			if (ptrQuad->index[2] != ptrQuad->index[3])
            {
                COLL_TestTriangle_FindAny(sps, 0x1f80020c, 0x1f800234, 0x1f800220); // 1,3,2
            }
        }
        else
        {
            if ((sps->Union.QuadBlockColl.unk22 & 8) == 0)
            {
                COLL_TestQuadblock_EightTris(sps, ptrQuad);
            }

            COLL_TestTriangle_FindAny(0x1f800118, 0x1f8002a8, 0x1f800280, 0x1f800294); // 8, 6, 7
            COLL_TestTriangle_FindAny(0x1f800118, 0x1f800294, 0x1f800244, 0x1f8002a8); // 7, 3, 8
            COLL_TestTriangle_FindAny(0x1f800118, 0x1f80021c, 0x1f800294, 0x1f800280); // 1, 7, 6
            COLL_TestTriangle_FindAny(0x1f800118, 0x1f800230, 0x1f800280, 0x1f8002a8); // 2, 6, 8
			
			// If this is a quad instead of a triangle
            if (ptrQuad->index[2] != ptrQuad->index[3])
            {
                COLL_TestTriangle_FindAny(0x1f800118, 0x1f800208, 0x1f800258, 0x1f80026c); // 0, 4, 5
                COLL_TestTriangle_FindAny(0x1f800118, 0x1f800258, 0x1f800280, 0x1f80026c); // 4, 6, 5
                COLL_TestTriangle_FindAny(0x1f800118, 0x1f800280, 0x1f800258, 0x1f80021c); // 6, 4, 1
                COLL_TestTriangle_FindAny(0x1f800118, 0x1f80026c, 0x1f800280, 0x1f800230); // 5, 6, 2
            }
        }
    }
}