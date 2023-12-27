#include <common.h>

void DECOMP_UI_DrawSpeedNeedle(short posX, short posY, struct Driver * driver)

{
  struct GameTracker* gGT;
  short needle;
  int angle1;
  int angle2;
  u_long*primmemCurr;
  struct DB* backDB;
  int scale;
  int length;
  int ratio;
  int minRange;
  int maxRange;
  int minScale;
  int maxScale;
  int speed;
  int iVar9;
  POLY_G3* p;

  gGT = sdata->gGT;
  backDB = gGT->backBuffer;

  scale = driver->const_SpeedometerScale_ClassStat;
  iVar9 = scale << 0x10;
  maxScale = scale + driver->const_SacredFireSpeed >> 8;
  speed = driver->unk36E << 0x10; // is this actually speed?
  minScale = 0;
  iVar9 = iVar9 >> 0x18;
  if (scale < speed >> 0x10) {
    maxRange = 0x700;
    minRange = 0x980;
    minScale = (iVar9 * 0x1a5e0) / 64000;
  } else {
    maxRange = 0x980;
    minRange = 0xd90;
    maxScale = iVar9;
  }

#ifndef REBUILD_PC
  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  needle = MapToRange(((speed >> 0x18) * 0x1a5e0) / 64000, minScale, (maxScale * 0x1a5e0) / 64000, minRange, maxRange);
#else
  needle = 0;
#endif

  angle1 = needle;
  angle2 = angle1 + 0x400;

  // PrimMem ptrCurrent
  primmemCurr = backDB->primMem.curr;
  p = 0;

  // trigonometry lookup table
  int cos[2] = {DECOMP_MATH_Cos(angle1), DECOMP_MATH_Cos(angle2)};
  int sin[2] = {DECOMP_MATH_Sin(angle1), DECOMP_MATH_Sin(angle2)};

  // if there is room for more
  if (primmemCurr <= (u_long*) backDB->primMem.endMin100) {
    // increment prim pointer
    backDB->primMem.curr = primmemCurr + 7;
    p = (POLY_G3*) primmemCurr;
  }

  if (p == 0) return;
    
  setPolyG3(p);
  setRGB0(p, 0x5b, 0x5b, 0);
  setRGB1(p, 0x32, 0x2b, 1);
  setRGB2(p, 0xff, 0xbb, 0);

  ratio = ((cos[1] << 2) >> 0xb) * 0x140;
  if (ratio < 0) {
    ratio += 0x1ff;
  }
  p->x2 = posX + (sin[1] * 3 >> 0xb) + 0x41;
  p->y2 = posY + (ratio >> 9) + 0x29;

  ratio = (cos[0] * 3 >> 0xb) * 0x140;
  if (ratio < 0) {
    ratio += 0x1ff;
  }
  p->x1 = posX - ((sin[0] * 3 >> 0xb) + -0x41);
  p->y1 = posY - ((ratio >> 9) + -0x29);

  ratio = (cos[0] * 0x1e >> 0xb) * 0x140;
  if (ratio < 0) {
    ratio += 0x1ff;
  }
  p->x0 = posX + (sin[0] * 0x1e >> 0xb) + 0x41;
  p->y0 = posY + (ratio >> 9) + 0x29;

  // pointer to OT memory
  primmemCurr = gGT->tileView_UI.ptrOT;

  *(int *)p = *primmemCurr | 0x6000000;
  *primmemCurr = (u_int) p & 0xffffff;

  // PrimMem ptrCurrent
  primmemCurr = backDB->primMem.curr;
  p = 0;

  // if there is room for more
  if (primmemCurr <= (u_long*) backDB->primMem.endMin100) {
    // increment prim pointer
    backDB->primMem.curr = primmemCurr + 7;
    p = (POLY_G3*) primmemCurr;
  }

  if (p == 0) return;
  setPolyG3(p);
  setRGB0(p, 0xff, 0xff, 0xff);
  setRGB1(p, 0x9c, 0x69, 0);
  setRGB2(p, 0xff, 0xff, 0);

  ratio = ((cos[1] << 2) >> 0xb) * 0x140;
  if (ratio < 0) {
    ratio += 0x1ff;
  }
  p->x2 = posX - ((sin[1] * 3 >> 0xb) + -0x41);
  p->y2 = posY - ((ratio >> 9) + -0x29);

  ratio = (cos[0] * 3 >> 0xb) * 0x140;
  if (ratio < 0) {
    ratio += 0x1ff;
  }
  p->x1 = posX - ((sin[0] * 3 >> 0xb) + -0x41);
  p->y1 = posY - ((ratio >> 9) + -0x29);

  ratio = (cos[0] * 0x1e >> 0xb) * 0x140;
  if (ratio < 0) {
    ratio += 0x1ff;
  }
  p->x0 = posX + ((sin[0] * 0x1e >> 0xb) + 0x41);
  p->y0 = posY + ((ratio >> 9) + 0x29);

  // pointer to OT memory
  primmemCurr = gGT->tileView_UI.ptrOT;

  *(int *)p = *primmemCurr | 0x6000000;
  *primmemCurr = (u_int) p & 0xffffff;

  return;
}