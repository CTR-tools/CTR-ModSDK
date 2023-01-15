#include <common.h>

void DECOMP_CTR_Box_DrawSolidBox(RECT* r, u_int rgb, u_long* otMem, struct PrimMem* primMem)
{
	struct PrimMem* primbuffer = (struct PrimMem*)primMem->curr;
	POLY_F4* p = 0;
	
	if (primbuffer <= (struct PrimMem*)primMem->endMin100)
	{
		primMem->curr = (void*)((int)primbuffer + 24);
		p = (POLY_F4*)primbuffer;
	}

	if (p)
	{
		*(u_int*)&p->r0 = rgb & 0xffffff | 0x28000000;
		*(u_int*)&p->x0 = *(u_int*)&r->x;
		*(u_int*)&p->x1 = (int)(short)*(u_short *)&r->x + (int)(short)*(u_short *)&r->w & 0xffffU | (int)(short)*(u_short *)&r->y << 0x10;
		*(u_int*)&p->x2 = (u_int)*(u_short *)&r->x | ((int)(short)*(u_short *)&r->y + (int)(short)*(u_short *)&r->h) * 0x10000;
		*(u_int*)&p->x3 = (int)(short)*(u_short *)&r->x + (int)(short)*(u_short *)&r->w & 0xffffU | ((int)(short)*(u_short *)&r->y + (int)(short)*(u_short *)&r->h) * 0x10000;

		p->tag = *otMem & 0xffffff | 0x5000000;
		*otMem = (u_int)p & 0xffffff;
	}
	return;
}