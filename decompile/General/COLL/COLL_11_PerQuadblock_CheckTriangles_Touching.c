#include <common.h>

void COLL_PerQuadblock_CheckTriangles_Touching(struct QuadBlock *quad, struct ScratchpadStruct *sps)
{
	struct BspSearchVertex* bsv = &sps->bspSearchVert[0];
	
    *(int*)&sps->unk4C[0x18] = quad;

    if (
        ((sps->Union.QuadBlockColl.qbFlagsWanted & quad->quadFlags) != 0) &&
		((sps->Union.QuadBlockColl.qbFlagsIgnored & quad->quadFlags) == 0) &&
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
        if ((sps->Union.QuadBlockColl.searchFlags & 2) == 0)
        {
            COLL_TestQuadblock_TwoTris(sps, quad);

            COLL_TestTriangle_FindAny(sps, &bsv[0], &bsv[1], &bsv[2]); // 0,1,2
            
			// If this is a quad instead of a triangle
			if (quad->index[2] != quad->index[3])
            {
                COLL_TestTriangle_FindAny(sps, &bsv[1], &bsv[3], &bsv[2]); // 1,3,2
            }
        }
        else
        {
            if ((sps->Union.QuadBlockColl.searchFlags & 8) == 0)
            {
                COLL_TestQuadblock_EightTris(sps, quad);
            }

            COLL_TestTriangle_FindAny((int)sps+0x10, (int)&bsv[8]+0x10, (int)&bsv[6]+0x10, (int)&bsv[7]+0x10); // 8, 6, 7
            COLL_TestTriangle_FindAny((int)sps+0x10, (int)&bsv[7]+0x10, (int)&bsv[3]+0x10, (int)&bsv[8]+0x10); // 7, 3, 8
            COLL_TestTriangle_FindAny((int)sps+0x10, (int)&bsv[1]+0x10, (int)&bsv[7]+0x10, (int)&bsv[6]+0x10); // 1, 7, 6
            COLL_TestTriangle_FindAny((int)sps+0x10, (int)&bsv[2]+0x10, (int)&bsv[6]+0x10, (int)&bsv[8]+0x10); // 2, 6, 8
			
			// If this is a quad instead of a triangle
            if (quad->index[2] != quad->index[3])
            {
                COLL_TestTriangle_FindAny((int)sps+0x10, (int)&bsv[0]+0x10, (int)&bsv[4]+0x10, (int)&bsv[5]+0x10); // 0, 4, 5
                COLL_TestTriangle_FindAny((int)sps+0x10, (int)&bsv[4]+0x10, (int)&bsv[6]+0x10, (int)&bsv[5]+0x10); // 4, 6, 5
                COLL_TestTriangle_FindAny((int)sps+0x10, (int)&bsv[6]+0x10, (int)&bsv[4]+0x10, (int)&bsv[1]+0x10); // 6, 4, 1
                COLL_TestTriangle_FindAny((int)sps+0x10, (int)&bsv[5]+0x10, (int)&bsv[6]+0x10, (int)&bsv[2]+0x10); // 5, 6, 2
            }
        }
    }
}