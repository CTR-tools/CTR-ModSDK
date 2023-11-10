#include <common.h>

// Nicolas Noble: this is a composed primitive. aka, there's more than one command in it

// spicyjpeg: most of sony's docs conflate dma packets and actual gpu commands under the term "primitive", but in actual
// fact they are two completely independent things. psyq is written with the expectation that each packet contains exactly
// one command (+ any parameters required for it), but games frequently violated that rule for better efficiency. the gpu
// does not "see" packet headers and boundaries, all it see is a continuous stream of the contents of each packet so you
// can have multiple commands in the same packet, or half of a command in one packet and the other half in the next
// packet, or empty packets with no commands (which is how ordering tables are implemented). the first 4 bytes are your
// usual dma packet header [editor's note: this is referring to p->tag]. the next 4 bytes are the tpage command, which is a
// single 32bit word [editor's note: this is referring to p->tpage]. then there's a nop and then a 0x2a000000 command which
// is a flat shaded, semitransparent quad [editor's note: this is referring to p->nop, and p->f4 as well as the setcode call]

void DECOMP_CTR_Box_DrawClearBox(RECT* r, u_int* colorPtr, int transparency, u_long* ot, struct PrimMem* primMem)
{
	typedef struct
	{
		u_int tag;
		u_int tpage;
		u_int nop;
		POLY_F4_T f4;
	} compoundPrim;

	void* primMem_curr = primMem->curr;
	compoundPrim* p = 0;

	if (primMem_curr <= primMem->endMin100)
	{
		primMem->curr = (void *)((int)primMem_curr + 0x20);
		p = (compoundPrim*)primMem_curr;
	}
	if (p != 0)
	{
		setlen(p, 7);
		setColor0(&p->f4, *colorPtr);
		setcode_T(&p->f4, 0x28);
		setSemiTrans_T(&p->f4, true);

		p->tpage = (transparency << 5) | 0xe1000a00;

		unsigned int rightX = r->x + r->w;
		unsigned int bottomY = r->y + r->h;

		setXY4(&p->f4, r->x, r->y, rightX, r->y, r->x, bottomY, rightX, bottomY);

		AddPrim(ot, p);
	}
}