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
  int letterX = 6;

  uVar6 = screenPosX + 7;
  uVar4 = (screenPosY + 7) * 0x10000;

  p = (POLY_FT4*)gGT->backBuffer->primMem.curr;
  ot = (unsigned int*)gGT->tileView_UI.ptrOT;
  gGT->backBuffer->primMem.curr = p + 1;

  *(int*)&p->r0 = 0x2e000000;
  *(int*)&p->x0 = screenPosX | screenPosY << 0x10;
  *(int*)&p->x3 = uVar6 | uVar4;
  *(int*)&p->x1 = uVar6 | screenPosY << 0x10;
  *(int*)&p->x2 = screenPosX | uVar4;

  // each character is 7 pixels wide
  // and 7 pixels tall

  // '0' is 6th character in 2nd row,
  // Get X value of pixel
  // This is the bottom of two bytes
  uVar4 = sdata->debugFont.pixelX + letterX * 7;

  // Get Y value for top of the quad
  // bit shift to top byte
  uVar6 = (sdata->debugFont.pixelY + 7) * 0x100;

  // Get Y value for bottom of the quad
  // bit shift to top byte
  uVar5 = uVar6 + 7 * 0x100;

  *(int*)&p->u0 = uVar4 | uVar6;
  *(int*)&p->u1 = uVar4 + 7 | uVar6;
  *(int*)&p->u2 = uVar4 | uVar5;
  *(int*)&p->u3 = uVar4 + 7 | uVar5;

  p->clut = sdata->debugFont.clut;
  p->tpage = sdata->debugFont.tpage;

  *(int*)p = *ot | 0x9000000;
  *ot = (unsigned int)p & 0xffffff;
}