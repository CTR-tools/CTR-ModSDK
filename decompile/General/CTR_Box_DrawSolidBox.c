#include <common.h>

void DECOMP_CTR_Box_DrawSolidBox(RECT* r, u_int* colorPtr, u_long* otMem, struct PrimMem* primMem)
{
	struct PrimMem* primmemCurr = (struct PrimMem*)primMem->curr;
	POLY_F4* p = NULL;
	
	if (primmemCurr <= (struct PrimMem*)primMem->endMin100)
	{
		p = (POLY_F4*)primmemCurr;
		primMem->curr = p + 1;
	}

	if (p == NULL) return;

    *(int*)&p->r0 = *colorPtr;
	p->code = 0x28;
	
    p->x0 = r->x;
    p->y0 = r->y;

    p->x1 = (r->x + r->w);
    p->y1 =  r->y;

    p->x2 = r->x;
    p->y2 = (r->y + r->h);

    p->x3 = (r->x + r->w);
    p->y3 = (r->y + r->h);

	p->tag = *otMem & 0xffffff | 0x5000000;
    *otMem = (u_int)p & 0xffffff;
}