#include <common.h>

// This executes our mod each frame
void AddPrim_RunUpdateHook()
{
	// This is how CTR draws dividing
	// lines in multiplayer

	POLY_F4* p = (POLY_F4*)sdata->gGT->backBuffer->primMem.curr;

	// set size at offset 3
	// set code at offset 7,
    setPolyF4(p);

	// RGB
	p->r0 = 255;
	p->g0 = 128;
	p->b0 = 0;

	// Make four (x,y) coordinates
	p->x0 = 0x10;
    p->y0 = 0x5a;

    p->x1 = 0x1F0;
    p->y1 = 0x5a;

    p->x2 = 0x10;
    p->y2 = 0x7e;

    p->x3 = 0x1F0;
    p->y3 = 0x7e;

	// Draw a bar from left to right,
	// dividing the screen in half on top and bottom
    AddPrim(&sdata->gGT->pushBuffer_UI.ptrOT[3], p);

	// advance the primitive buffer
    sdata->gGT->backBuffer->primMem.curr = p + 1;
}
