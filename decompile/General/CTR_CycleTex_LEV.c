#include <common.h>

void DECOMP_CTR_CycleTex_LEV(struct AnimTex* animtex, int timer)
{
	int frameIndex;
	struct AnimTex* curAnimTex = animtex;
	
	// iterate over All AnimTex's in a row,
	// last one loops back to the beginning, could've also just been a null terminator
	while (*(int*)curAnimTex != animtex)
	{
		frameIndex = timer + curAnimTex->frameDuration >> 
						((int)curAnimTex->shiftFactor & 0x1fU);
						
		frameIndex = frameIndex % curAnimTex->numFrames;
		curAnimTex->frameIndex = frameIndex;
		curAnimTex->ptrActiveTex = curAnimTex->ptrarray[frameIndex];
		
		// Go to next AnimTex, which comes after this AnimTex's ptrarray
		curAnimTex = &curAnimTex->ptrarray[curAnimTex->numFrames];
	}
}