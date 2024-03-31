#include <common.h>

void DECOMP_PushBuffer_SetDrawEnv_Normal(
		void* ot, struct PushBuffer* pb, struct DB* backBuffer,
		DRAWENV* copyDrawEnvNULL, int isbg)
{
	DRAWENV newDrawEnv;
	
	int* dst = &newDrawEnv;
	int* src = &backBuffer->drawEnv;
	
	for(int i = 0; i < sizeof(DRAWENV)/4; i++)
		dst[i] = src[i];
	
	// always?
	if(copyDrawEnvNULL == 0)
	{
		newDrawEnv.clip.x += pb->rect.x;
		newDrawEnv.clip.y += pb->rect.y;
		newDrawEnv.clip.w = pb->rect.w;
		newDrawEnv.clip.h = pb->rect.h;
		newDrawEnv.ofs[0] += pb->rect.x;
		newDrawEnv.ofs[1] += pb->rect.y;
	}
	
	// never?
	else
	{
		// OG game has stuff here
		while(1) {}
	}
	
	newDrawEnv.isbg = isbg;
	
	void* p = backBuffer->primMem.curr;
	if(p <= backBuffer->primMem.endMin100)
	{
		backBuffer->primMem.curr = (unsigned int)backBuffer->primMem.curr + 0x40;
		
		SetDrawEnv(p, &newDrawEnv);

		// This doesn't really draw a primitive,
		// it links the ptrOT from the camera,
		// into the ptrOT of backBuffer DB, allowing
		// this camera's primitives to draw
		AddPrim(ot, p);
	}
}