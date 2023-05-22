#include <common.h>

void DECOMP_CTR_CycleTex_LEV(struct AnimTex *animtex, int timer)
{
	struct AnimTex *psVar1;
	int iVar3;
	struct AnimTex *psVar4;
	int currentFrame;
	
	psVar1 = animtex->ptrNext;
	psVar4 = animtex;
	while (psVar1 != animtex)
	{
		iVar3 = timer + psVar4->shrug >> ((int)psVar4->lottashortshuh & 0x1fU);
		currentFrame = iVar3 % psVar4->numFrames;
		psVar4->frameIndex = (u_short)currentFrame;
		psVar4->ptrNext = psVar4->ptrarray[currentFrame];
		psVar4 = &psVar4->ptrarray[psVar4->numFrames];
		psVar1 = psVar4->ptrNext;
	}
	return;
}