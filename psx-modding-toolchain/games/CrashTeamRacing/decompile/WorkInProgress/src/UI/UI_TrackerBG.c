#include <common.h>

void DECOMP_UI_TrackerBG(struct Icon* targetIcon,short posX,short posY,struct PrimMem* primMem,u_long *ot, char param_6, short param_7,short param_8,int color)
{
  short sVar1;
  short sVar2;
  short offsY;
  short sVar5;
  short sVar6;
  POLY_FT4 *p;
  int offsX;
  int numPlayer;
  short sVar9;
  short sVar10;

  offsX = ((targetIcon->texLayout.u1 - targetIcon->texLayout.u0) * param_7) >> 0xc;
  sVar1 = posX + offsX;
  param_7 = param_7 >> 0xc;
  sVar10 = sVar1 - param_7;

  // wumpaShineTheta (given to sine)
  sdata->wumpaShineTheta += 0x100;

  offsY = ((targetIcon->texLayout.v2 - targetIcon->texLayout.v0) * param_8) >> 0xc;
  sVar2 = posY + offsY;
  param_8 = param_8 >> 0xc;
  sVar9 = sVar2 - param_8;
  
  // loop 4 times
  for (numPlayer = 0; numPlayer < 4; numPlayer++)
  {
    p = primMem->curr;
    p->r0 = color;
    p->u0 = targetIcon->texLayout.u0;
    p->clut = targetIcon->texLayout.u1;
    p->u2 = targetIcon->texLayout.u2;
    p->u3 = targetIcon->texLayout.u3;
	
    ((P_TAG*)p->tag)->len = 9; // (p + 3)
    p->code = 0x2c;
	
    if (param_6 != 0) {
      p->tpage = p->tpage & 0xff9f | (param_6 - 1) * 0x20;
      p->code |= 2;
    }

	switch (numPlayer) {
        case 0:
            p->x0 = posX;
            p->y0 = posY;

            p->x1 = sVar1;
            p->y1 = posY;
            p->x2 = posX;
            p->y2 = sVar2;
            p->x3 = sVar1;
            p->y3 = sVar2;
            break;

        case 1:
            sVar5 = (posX + (offsX * 2)) - param_7;
            p->x0 = sVar5;
            p->y0 = posY;

            p->x1 = sVar10;
            p->y1 = posY;
            p->x2 = sVar5;
            p->y2 = sVar2;
            p->x3 = sVar10;
            p->y3 = sVar2;
            break;

        case 2:
            sVar5 = (sVar2 * 2) - param_8;
            p->x0 = posX;
            p->y0 = sVar5;

            p->x1 = sVar1;
            p->y1 = sVar5;
            p->x2 = posX;
            p->y2 = sVar9;
            p->x3 = sVar1;
            break;

        case 3:
            sVar6 = (sVar1 * 2) - param_7;
            sVar5 = (sVar2 * 2) - param_8;
            p->x0 = sVar6;
            p->y0 = sVar5;

            p->x1 = sVar10;
            p->y1 = sVar5;
            p->x2 = sVar6;
            p->y2 = sVar9;
            p->x3 = sVar10;
    }
    AddPrim(ot,p);
    primMem->curr = (void*)((int)primMem->curr + 0x28);
  }
  return;
}
