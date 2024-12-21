#include <common.h>

void DECOMP_RECTMENU_DrawRwdTriangle(short* position,char* color,u_long* otMem,struct PrimMem* primMem)
{
  POLY_G4 *p;
  void *primmemCurr;

  primmemCurr = primMem->curr;
  p = 0;
  
  if (primmemCurr <= primMem->endMin100) 
  {
    p = primmemCurr;
    primMem->curr = p+1;
  }
  
  if (p != 0) 
  {
	// RGB
	*(int*)&p->r0 = *(int*)&color[0x0];
	*(int*)&p->r1 = *(int*)&color[0x4];
	*(int*)&p->r2 = *(int*)&color[0x0];
	*(int*)&p->r3 = *(int*)&color[0x8];
	
	// rest of the primitive (four xy)
    short x0 = position[0];
    short y0 = position[1] - 1;
	
    short y2 = position[1];

    p->x0 = position[0];
    p->y0 = position[1] - 1;
    
	*(int*)&p->x1 = *(int*)&position[2];
	*(int*)&p->x2 = *(int*)&position[0];
    *(int*)&p->x3 = *(int*)&position[4];
	
	setPolyG4(p);
    AddPrim(otMem,p);
  }
  return;
}