#include <common.h>

void DECOMP_DebugFont_DrawNumbers(int number, u_int posX, int posY)
{
  POLY_FT4* p;
  u_long* ot;
  u_int uVar4;
  u_int uVar5;
  u_int uVar6;

  uVar6 = posX + 7 & 0xffff;
  uVar4 = (posY + 7) * 0x10000;

  // backBuffer->primMem.curr
  p = (POLY_FT4*)sdata->gGT->backBuffer->primMem.curr;

  // pointer to OT memory
  ot = sdata->gGT->tileView_UI.ptrOT;

  // backBuffer->primMem.curr
  sdata->gGT->backBuffer->primMem.curr = p + 1;

  *(int*)&p->r0 = 0x2e000000;
  p->x0 = posX & 0xffff | posY << 0x10;
  p->x1 = uVar6 | posY << 0x10;
  p->x2 = posX & 0xffff | uVar4;
  p->x3 = uVar6 | uVar4;

  // each character is 7 pixels wide
  // and 7 pixels tall

  // '0' is 6th character in 2nd row,
  // Get X value of pixel
  // This is the bottom of two bytes
  uVar4 = sdata->debugFont.pixelX + (number + 5) * 7;

  // Get Y value for top of the quad
  // bit shift to top byte
  uVar6 = (sdata->debugFont.pixelY + 7) * 0x100;

  // Get Y value for bottom of the quad1
  // bit shift to top byte
  uVar5 = (uVar6 + 7) * 0x100;

  // Top Left corner
  p->u0 = uVar4 | uVar6;

  // Top Right corner
  p->u1 = uVar4 + 7 | uVar6;

  // Bottom Left corner
  p->u2 = uVar4 | uVar5;

  // Bottom Right corner
  p->u3 = uVar4 + 7 | uVar5;

  // color palette
  p->clut = sdata->debugFont.clut;

  // texture page
  p->tpage = sdata->debugFont.tpage;

  *(int*)p = *ot | 0x9000000;
  *ot = (u_int)p & 0xffffff;
  return;
}
 