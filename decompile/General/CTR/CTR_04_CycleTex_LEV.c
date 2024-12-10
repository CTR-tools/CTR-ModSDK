#include <common.h>

void DECOMP_CTR_CycleTex_LEV(struct AnimTex* animtex, int timer)
{
	int frameIndex;
	struct AnimTex* curAnimTex = animtex;
	
	// iterate over All AnimTex's in a row,
	// last one loops back to the beginning, could've also just been a null terminator
	while (*(int*)curAnimTex != (int)animtex)// I feel like this should just be a do/while with `(int)curAnimText != (int)animtex`, but idk
	{
		frameIndex = FPS_HALF(timer) + curAnimTex->frameDuration >> 
						((int)curAnimTex->shiftFactor & 0x1fU);
						
		frameIndex = frameIndex % curAnimTex->numFrames;
		curAnimTex->frameIndex = frameIndex;
		
		struct IconGroup4** ptrArray = ANIMTEX_GETARRAY(curAnimTex);
		
		// Save new frame
		curAnimTex->ptrActiveTex = (int*)ptrArray[frameIndex]; //why is this line slightly different than CTR_CycleTex_Model.c?
		
		// Go to next AnimTex, which comes after this AnimTex's ptrarray
		curAnimTex = (struct AnimTex*)&ptrArray[curAnimTex->numFrames];
	}
}