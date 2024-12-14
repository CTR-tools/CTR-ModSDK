#include <common.h>

void DECOMP_DebugFont_DrawNumbers(int index, int screenPosX, int screenPosY)
{
// Deperate for byte budget
#if 0
  PolyFT4 * p;
  GetPrimMem(p);
  if (p == nullptr) { return; }

  const int fontWidth = WIDE_34(7);
  const int fontHeight = 7;

  const PrimCode primCode = { .poly = { .renderCode = RenderCode_Polygon, .quad = 1, .textured = 1, .semiTransparency = 1 } };
  p->colorCode = MakeColorCode(0, 0, 0, primCode);

  s16 topX = screenPosX;
  s16 bottomX = topX + fontWidth;
  s16 topY = screenPosY;
  s16 bottomY = topY + fontHeight;
  p->v[0].pos.x = topX;
  p->v[0].pos.y = topY;
  p->v[1].pos.x = bottomX;
  p->v[1].pos.y = topY;
  p->v[2].pos.x = topX;
  p->v[2].pos.y = bottomY;
  p->v[3].pos.x = bottomX;
  p->v[3].pos.y = bottomY;

  /* Each character is 7x7 pixels,
     '0' is 6th character on 2nd row */
  u8 topU = sdata->debugFont.u + 7 * 5 + index * 7;
  u8 bottomU = topU + 7;
  u8 topV = sdata->debugFont.v + 7;
  u8 bottomV = topV + 7;
  p->v[0].texCoords.u = topU;
  p->v[0].texCoords.v = topV;
  p->v[1].texCoords.u = bottomU;
  p->v[1].texCoords.v = topV;
  p->v[2].texCoords.u = topU;
  p->v[2].texCoords.v = bottomV;
  p->v[3].texCoords.u = bottomU;
  p->v[3].texCoords.v = bottomV;
  p->polyClut.self = sdata->debugFont.clut;
  p->polyTpage.self = sdata->debugFont.tpage;

  AddPrimitive(p, sdata->gGT->pushBuffer_UI.ptrOT);
#endif
  
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
  ot = (unsigned int*)gGT->pushBuffer_UI.ptrOT;
  gGT->backBuffer->primMem.curr = p + 1;

  *(int*)&p->r0 = 0x2e000000;
  *(int*)&p->x0 = screenPosX | uVar5;
  *(int*)&p->x3 = uVar6      | uVar4;
  *(int*)&p->x1 = uVar6      | uVar5;
  *(int*)&p->x2 = screenPosX | uVar4;

  // Each character is 7x7 pixels,
  // '0' is 6th character on 2nd row
  uVar4 = (short)(*(short*)&sdata->debugFont.u) + 5*7 + 0x700;

  *(int*)&p->u0 = uVar4 + (index+0)*7;
  *(int*)&p->u1 = uVar4 + (index+1)*7;
  *(int*)&p->u2 = uVar4 + (index+0)*7 + 0x700;
  *(int*)&p->u3 = uVar4 + (index+1)*7 + 0x700;

  p->clut = sdata->debugFont.clut;
  p->tpage = sdata->debugFont.tpage;

  *(int*)p = *ot | 0x9000000;
  *ot = (unsigned int)p & 0xffffff;
}