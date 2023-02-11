#include <common.h>

// Animate moving textures: turbo pads, waterfalls, lava, etc
void DECOMP_CTR_CycleTex_LEV(struct AnimTex* animtex, int timer)
{
	struct AnimTex* ptrNext;
	short iVar2;
	int iVar3;
	struct AnimTex* ptrCurr;
	short currentFrame;

	// first texture links to last
	ptrCurr = animtex;
	ptrNext = animtex->ptrNext;
	
	// loop through all
	while (ptrNext != ptrCurr)
	{
		// how many frames until scrolling texture makes full loop
		// (usually ten frames, 1/3 second)
		iVar2 = ptrCurr->idk;

		iVar3 = timer + ptrCurr->shrug >> (ptrCurr->lottashortshuh & 0x1f);

		// get frame in current scroll
		currentFrame = iVar3 % iVar2;

		// frame index
		ptrCurr->frameIndex = currentFrame;

		// get pointer from array, one for each texture frame
		ptrCurr->ptrNext = ptrCurr->ptrarray[currentFrame];

		ptrCurr = ptrCurr->ptrarray[ptrCurr->idk];

		// go to next
		ptrNext = ptrCurr->ptrNext;
	}
	return;
}