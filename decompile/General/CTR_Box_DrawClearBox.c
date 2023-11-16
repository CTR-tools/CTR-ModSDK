#include <common.h>

void DECOMP_CTR_Box_DrawClearBox(RECT* r, u_int* colorPtr, int transparency, u_long* ot, struct PrimMem* primMem)
{
	typedef struct
	{
		u_int tag;
		u_int tpage;
		POLY_F4 f4;
	} multiCmdPacket;

	void* primMem_curr = primMem->curr;
	multiCmdPacket* p = 0;

	if (primMem_curr <= primMem->endMin100)
	{
		primMem->curr = (void *)((int)primMem_curr + 0x20);
		p = (multiCmdPacket*)primMem_curr;
	}
	if (p != 0)
	{
		setlen(p, 7);
		p->tpage = (transparency << 5) | 0xe1000a00;

		*(int*)&p->f4.tag = 0;
		*(int*)&p->f4.r0 = *colorPtr;
		p->f4.code = 0x2A;

		short rightX = r->x + r->w;
		short bottomY = r->y + r->h;

		p->f4.x0 = r->x, 	p->f4.y0 = r->y;
		p->f4.x1 = rightX,	p->f4.y1 = r->y;
		p->f4.x2 = r->x, 	p->f4.y2 = bottomY;
		p->f4.x3 = rightX,	p->f4.y3 = bottomY;

		AddPrim(ot, p);
	}
}