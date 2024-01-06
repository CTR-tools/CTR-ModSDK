#include <common.h>

void DECOMP_COLL_StartSearch_AI(short *posCurr, short *posPrev, struct ScratchpadStruct* sps)
{
    char i;
    short radius = sps->Input1.hitRadius;
    int sqrRadius = radius * radius;
    short deltaCurr;
    short deltaPrev;

    sps->Input1.hitRadiusSquared = sqrRadius;
    sps->Union.QuadBlockColl.hitRadiusSquared = sqrRadius;
    sps->Union.QuadBlockColl.hitRadius = radius;

    for (i = 0; i < 3; i++) 
	{
        sps->Input1.pos[i] = posCurr[i];
        sps->Union.QuadBlockColl.hitPos[i] = posCurr[i];
        sps->Union.QuadBlockColl.pos[i] = posPrev[i];
		
        deltaCurr = posCurr[i] - radius;
        deltaPrev = posPrev[i] - radius;
        sps->bbox.min[i] = (deltaCurr < deltaPrev) ? deltaCurr : deltaPrev;

        deltaCurr = posCurr[i] + radius;
        deltaPrev = posPrev[i] + radius;
        sps->bbox.max[i] = (deltaCurr > deltaPrev) ? deltaCurr : deltaPrev;
    }

    sps->unk3C = 0;
    sps->boolDidTouchHitbox = 0;

    *(u_int *)&sps->unk4C[0x38] = 0x1000;
    *(u_int *)&sps->unk4C[0x78] = 0; // 0xC4 arraySize
    *(u_int *)&sps->dataOutput[0] = 0;

    COLL_SearchTree_FindX(sps->ptr_mesh_info->bspRoot, &sps->bbox, COLL_PerBspLeaf_CheckInstances, sps);
}
