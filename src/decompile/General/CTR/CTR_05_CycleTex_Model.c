#include <common.h>

void DECOMP_CTR_CycleTex_Model(struct AnimTex* animtex, int timer)
{
	int frameCurr;
	struct AnimTex* curAnimTex = animtex;
	
	// Termination is determined by pointer to First AnimTex
	while (*(int*)curAnimTex != (int)animtex)
	{
		// which texture to draw this frame
		frameCurr = FPS_HALF(timer) + curAnimTex->frameOffset; 
		
		// allow frames to skip updating (like 60fps hacks)
		frameCurr = frameCurr >> curAnimTex->frameSkip;
		
		// loop back to index[0] after finished cycle
		frameCurr = frameCurr % curAnimTex->numFrames;
		
		// save result
		curAnimTex->frameCurr = frameCurr;
		
		struct IconGroup4** ptrArray = ANIMTEX_GETARRAY(curAnimTex);
		
		// Save new frame
		// For Model, this is a pointer to a pointer
		*curAnimTex->ptrActiveTex = (int)ptrArray[frameCurr];
		
		// Go to next AnimTex, which comes after this AnimTex's ptrarray
		curAnimTex = (struct AnimTex*)&ptrArray[curAnimTex->numFrames];
	}
}