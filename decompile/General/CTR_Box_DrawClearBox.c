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

		*(int*)&p->f4.x0 = r->x | (r->y<<16);
		*(int*)&p->f4.x1 = rightX | (r->y<<16);
		*(int*)&p->f4.x2 = r->x | (bottomY<<16);
		*(int*)&p->f4.x3 = rightX | (bottomY<<16);

		AddPrim(ot, p);
	}
}