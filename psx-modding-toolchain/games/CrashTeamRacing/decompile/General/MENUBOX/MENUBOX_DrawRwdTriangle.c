#include <common.h>

void DECOMP_MENUBOX_DrawRwdTriangle(short* position,char* color,u_long* otMem,struct PrimMem* primMem)
{
  POLY_G4 *p;
  void *primmemCurr;

  primmemCurr = primMem->curr;
  p = 0;
  if (primmemCurr <= primMem->endMin100) {
    primMem->curr = (void *)((int)primmemCurr + 0x24);
    p = primmemCurr;
  }
  if (p != 0) {
    
	((P_TAG*)p)->len = 8;
    p->code = 0x38;
	
    /* this might look too much, 
    but it saves over 100 bytes. 
    There's probably a better way to do this */

	// RGB
    char r0 = *color;
    char g0 = *(color + 1);
    char b0 = *(color + 2);
    char r1 = *(color + 4);
    char g1 = *(color + 5);
    char b1 = *(color + 6);
    char r3 = *(color + 8);
    char g3 = *(color + 9);
    char b3 = *(color + 10);

    p->r0 = r0;
    p->g0 = g0;
    p->b0 = b0;
    p->r1 = r1;
    p->g1 = g1;
    p->b1 = b1;
    p->r2 = r0;
    p->g2 = g0;
    p->b2 = b0;
    p->r3 = r3;
    p->g3 = g3;
    p->b3 = b3;
	
	// rest of the primitive (four xy)
    short x0 = *position;
    short y0 = position[1] - 1;
    short x1 = position[2];
    short y1 = position[3];
    short y2 = position[1];
    short x3 = position[4];
    short y3 = position[5];

    p->x0 = x0;
    p->y0 = y0;
    p->x1 = x1;
    p->y1 = y1;
    p->x2 = x0;
    p->y2 = y2;
    p->x3 = x3;
    p->y3 = y3;
	
    AddPrim(otMem,p);
  }
  return;
}