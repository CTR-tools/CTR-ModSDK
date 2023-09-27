#include <common.h>

void DECOMP_TileView_SetDrawEnv_Normal(
		void* ot, struct TileView* tileView, struct DB* backBuffer,
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
		newDrawEnv.clip.x += tileView->rect.x;
		newDrawEnv.clip.y += tileView->rect.y;
		newDrawEnv.clip.w = tileView->rect.w;
		newDrawEnv.clip.h = tileView->rect.h;
		newDrawEnv.ofs[0] += tileView->rect.x;
		newDrawEnv.ofs[1] += tileView->rect.y;
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