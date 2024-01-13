#include <common.h>

void DECOMP_DebugFont_DrawNumbers(int index, int screenPosX, int screenPosY)
{
  unsigned short uVar1;
  POLY_FT4* p;
  unsigned int *ot;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  struct GameTracker* gGT = sdata->gGT;

  uVar6 = screenPosX + WIDE_PICK(7, 5);
  uVar5 = (screenPosY + 0) << 0x10;
  uVar4 = (screenPosY + 7) << 0x10;

  p = (POLY_FT4*)gGT->backBuffer->primMem.curr;
  ot = (unsigned int*)gGT->tileView_UI.ptrOT;
  gGT->backBuffer->primMem.curr = p + 1;

  *(int*)&p->r0 = 0x2e000000;
  *(int*)&p->x0 = screenPosX | uVar5;
  *(int*)&p->x3 = uVar6      | uVar4;
  *(int*)&p->x1 = uVar6      | uVar5;
  *(int*)&p->x2 = screenPosX | uVar4;

  // Each character is 7x7 pixels,
  // '0' is 6th character on 2nd row
  uVar4 = sdata->debugFont.UV + 5*7 + 0x700;

  *(int*)&p->u0 = uVar4 + (index+0)*7;
  *(int*)&p->u1 = uVar4 + (index+1)*7;
  *(int*)&p->u2 = uVar4 + (index+0)*7 + 0x700;
  *(int*)&p->u3 = uVar4 + (index+1)*7 + 0x700;

  p->clut = sdata->debugFont.clut;
  p->tpage = sdata->debugFont.tpage;

  *(int*)p = *ot | 0x9000000;
  *ot = (unsigned int)p & 0xffffff;
}