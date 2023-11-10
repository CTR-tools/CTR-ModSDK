#include <common.h>

void DECOMP_CTR_Box_DrawSolidBox(RECT* r, u_int rgb, u_long* otMem, struct PrimMem* primMem)
{
	struct PrimMem* primmemCurr = (struct PrimMem*)primMem->curr;
	POLY_F4* p = NULL;
	
	if (primmemCurr <= (struct PrimMem*)primMem->endMin100)
	{
		p = (POLY_F4*)primmemCurr;
		primMem->curr = p + 1;
	}

	if (p == NULL) return;

	setPolyF4(p);

	*(u_int*)&p->r0 = rgb;
	*(u_int*)&p->x0 = *(u_int*)&r->x;

	*(u_int*)&p->x1 = (u_int) (r->x + r->w & 0xffffU | r->y << 0x10);
	*(u_int*)&p->x2 = (u_int) (r->x | (r->y + r->h) * 0x10000);
	*(u_int*)&p->x3 = (u_int) (r->x + r->w & 0xffffU | (r->y + r->h) * 0x10000);

	// AddPrim(otMem,p);
	*(int*)p = *otMem & 0xffffff | 0x5000000;
	*otMem = (u_int)p & 0xffffff;
}