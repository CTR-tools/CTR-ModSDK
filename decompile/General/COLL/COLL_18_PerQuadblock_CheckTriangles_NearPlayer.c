#include <common.h>

void DECOMP_COLL_PerQuadblock_CheckTriangles_NearPlayer(struct QuadBlock *quad, struct ScratchpadStruct *sps)
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
	
			sps->unk4C[0x17] = 0;
			COLL_TestTriangle_FindClosest(sps, &bsv[0], &bsv[1], &bsv[2]); // 0, 1, 2

			// If this is a quad instead of a triangle
			if (quad->index[2] != quad->index[3])
			{
				sps->unk4C[0x17] = 1;
				COLL_TestTriangle_FindClosest(sps, &bsv[1], &bsv[3], &bsv[2]); // 1, 3, 2
			}
		}
		else
		{
			if ((sps->Union.QuadBlockColl.searchFlags & 8) == 0)
			{
				COLL_TestQuadblock_EightTris(sps, quad);
			}
	
			sps->unk4C[0x17] = 2;
			COLL_TestTriangle_FindClosest(sps, &bsv[0], &bsv[4], &bsv[5]); // 0, 4, 5
			sps->unk4C[0x17] = 3;
			COLL_TestTriangle_FindClosest(sps, &bsv[4], &bsv[6], &bsv[5]); // 4, 6, 5
			sps->unk4C[0x17] = 4;
			COLL_TestTriangle_FindClosest(sps, &bsv[6], &bsv[4], &bsv[1]); // 6, 4, 1
			sps->unk4C[0x17] = 5;
			COLL_TestTriangle_FindClosest(sps, &bsv[5], &bsv[6], &bsv[2]); // 5, 6, 2

			// If this is a quad instead of a triangle
			if (quad->index[2] != quad->index[3])
			{
				sps->unk4C[0x17] = 6;
				COLL_TestTriangle_FindClosest(sps, &bsv[8], &bsv[6], &bsv[7]); // 8, 6, 7
				sps->unk4C[0x17] = 7;
				COLL_TestTriangle_FindClosest(sps, &bsv[7], &bsv[3], &bsv[8]); // 7, 3, 8
				sps->unk4C[0x17] = 8;
				COLL_TestTriangle_FindClosest(sps, &bsv[1], &bsv[7], &bsv[6]); // 1, 7, 6
				sps->unk4C[0x17] = 9;
				COLL_TestTriangle_FindClosest(sps, &bsv[2], &bsv[6], &bsv[8]); // 2, 6, 8
			}
		}
    }
}
