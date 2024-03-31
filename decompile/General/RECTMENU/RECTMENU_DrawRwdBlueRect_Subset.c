#include <common.h>

void DECOMP_RECTMENU_DrawRwdBlueRect_Subset(short *pos, int *color, u_long *ot, struct PrimMem *primMem)
{
  POLY_G4 *p = (POLY_G4 *)primMem->curr;

  if (p <= primMem->endMin100)
  {
    primMem->curr = p + 1;

	*(int*)&p->r0 = color[0] & 0xffffff;
    *(int*)&p->r1 = color[1] & 0xffffff;
    *(int*)&p->r2 = color[2] & 0xffffff;
    *(int*)&p->r3 = color[3] & 0xffffff;
	
	p->code = 0x38;
     
	*(int*)&p->x0 = *(int*)&pos[0];
    *(int*)&p->x1 = (pos[0] + pos[2]) 	| (pos[1] << 16);
    *(int*)&p->x2 = pos[0] 				| ((pos[1] + pos[3]) << 16);
    *(int*)&p->x3 = (pos[0] + pos[2]) 	| ((pos[1] + pos[3]) << 16);
	
    *(int*)p = (*(int*)ot & 0xffffff) | 0x8000000;
    *(int*)ot = (int)p & 0xffffff;
  }
}