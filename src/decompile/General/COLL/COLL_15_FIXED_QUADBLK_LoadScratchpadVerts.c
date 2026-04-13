#include <common.h>

void DECOMP_COLL_FIXED_QUADBLK_LoadScratchpadVerts(struct ScratchpadStruct* sps)
{
	// rigged to $t8/$t9 by naughty dog
	register int t8 asm("t8");
	register int t9 asm("t9");
	
	struct LevVertex* ptrVert = t8;
	struct QuadBlock* ptrQuad = t9;
	struct BspSearchVertex* bsv;
	struct LevVertex* vertCurr;
	short* index;
	
	bsv = &sps->bspSearchVert[0];
	
	for (
			index = &ptrQuad->index[0]; 
			index < &ptrQuad->index[9];
			index++, bsv++
		)
	{
		vertCurr = &ptrVert[*index];
		bsv->pLevelVertex = vertCurr;
		*(int*)&bsv->pos[0] = *(int*)&vertCurr->pos[0];
		*(int*)&bsv->pos[2] = *(int*)&vertCurr->pos[2];
	}
	
	t8 = ptrVert;
	t9 = ptrQuad;
}