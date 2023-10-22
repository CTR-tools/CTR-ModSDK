#include <common.h>

void DECOMP_CTR_CycleTex_LEV(struct AnimTex* animtex, int timer)
{
	struct AnimTex *ptrNext;
	struct AnimTex *ptrCurr;
	int iVar3;
	int currentFrame;
	
	ptrNext = animtex->ptrNext;
	ptrCurr = animtex;
	while (ptrNext != animtex)
	{
		iVar3 = timer + ptrCurr->shrug >> ((int)ptrCurr->lottashortshuh & 0x1fU);
		currentFrame = iVar3 % ptrCurr->numFrames;
		ptrCurr->frameIndex = currentFrame;
		ptrCurr->ptrNext = ptrCurr->ptrarray[currentFrame]; // wait, this gets overwritten entirely the next line...
		ptrCurr = &ptrCurr->ptrarray[ptrCurr->numFrames];
		ptrNext = ptrCurr->ptrNext;
	}
}