#include <common.h>

void DECOMP_CTR_CycleTex_Model(struct AnimTex* animtex, int timer)
{
	int frameIndex;
	struct AnimTex* curAnimTex = animtex;

	// iterate over All AnimTex's in a row,
	// last one loops back to the beginning, could've also just been a null terminator
	while (*(int*)curAnimTex != animtex)
	{
		frameIndex = FPS_HALF(timer) + curAnimTex->frameDuration >> 
						((int)curAnimTex->shiftFactor & 0x1fU);
						
		frameIndex = frameIndex % curAnimTex->numFrames;
		curAnimTex->frameIndex = frameIndex;
		
		struct IconGroup4** ptrArray = ANIMTEX_GETARRAY(curAnimTex);
		
		// Save new frame
		*curAnimTex->ptrActiveTex = ptrArray[frameIndex];
		
		// Go to next AnimTex, which comes after this AnimTex's ptrarray
		curAnimTex = &ptrArray[curAnimTex->numFrames];
	}
}