#include <common.h>

void DECOMP_CTR_CycleTex_LEV(struct AnimTex *animtex, int timer)
{
	struct AnimTex *psVar1;
	int iVar2;
	int iVar3;
	struct AnimTex *psVar4;
	int currentFrame;
	
	psVar1 = animtex->ptrNext;
	psVar4 = animtex;
	while (psVar1 != animtex)
	{
		iVar2 = (int)psVar4->idk;
		iVar3 = timer + psVar4->shrug >> ((int)psVar4->lottashortshuh & 0x1fU);
		currentFrame = iVar3 % iVar2;
		psVar4->frameIndex = (u_short)currentFrame;
		psVar4->ptrNext = *(struct AnimTex **)((int)psVar4->ptrarray + ((currentFrame << 0x10) >> 0xe));
		psVar4 = (struct AnimTex *)(psVar4->ptrarray + psVar4->idk);
		psVar1 = psVar4->ptrNext;
	}
	return;
}