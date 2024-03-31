#include <common.h>

void DECOMP_CTR_ErrorScreen(char r, char g, char b)
{
	TILE p;
	int i;

#ifdef REBUILD_PC
	while (1) {}
#endif

	for(i = 0; i < 3; i++)
	{
		DrawSync(0);
		VSync(0);
		DECOMP_DISPLAY_Swap();

		// save a little asm
		if(i == 2) return;

		// prim code = 0 (cause bitshifted),
		// with bit-flag parameter '2'
		p.code = 2;

		// len = 03, addr = 0xffffff,
		// this is the first, and last, primitive
		p.tag = 0x3ffffff;

		p.x0 = sdata->gGT->frontBuffer->drawEnv.clip.x;
		p.y0 = sdata->gGT->frontBuffer->drawEnv.clip.y;
		p.w = sdata->gGT->frontBuffer->drawEnv.clip.w;
		p.h = sdata->gGT->frontBuffer->drawEnv.clip.h;

		p.r0 = r;
		p.g0 = g;
		p.b0 = b;

		DrawOTag((u_long *)&p);
	}
}