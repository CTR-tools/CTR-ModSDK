#include <common.h>

void DECOMP_UI_DrawSpeedNeedle(short posX, short posY, struct Driver * driver)

{
  struct GameTracker* gGT;
  short sVar2;
  int angle1;
  int angle2;
  u_long*primmemCurr;
  int iVar6;
  struct DB* backDB;
  int length;
  u_int uVar8;
  int iVar9;
  POLY_G3* p;
  int local_28;

  gGT = sdata->gGT;
  backDB = gGT->backBuffer;

  iVar6 = driver->const_SpeedometerScale_ClassStat;
  iVar9 = iVar6 << 0x10;
  angle1 = iVar6 + driver->const_SacredFireSpeed >> 8;
  angle2 = driver->unk36E << 0x10;
  length = 0;
  iVar9 = iVar9 >> 0x18;
  if (iVar6 < angle2 >> 0x10) {
    local_28 = 0x700;
    uVar8 = 0x980;
    length = (iVar9 * 0x1a5e0) / 64000;
  } else {
    local_28 = 0x980;
    uVar8 = 0xd90;
    angle1 = iVar9;
  }

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  sVar2 = MapToRange(((angle2 >> 0x18) * 0x1a5e0) / 64000, length, (angle1 * 0x1a5e0) / 64000, uVar8, local_28);
  angle1 = sVar2;
  angle2 = angle1 + 0x400;

  // PrimMem ptrCurrent
  primmemCurr = backDB->primMem.curr;
  p = 0;

  // if there is room for more
  if (primmemCurr <= (u_long*) backDB->primMem.endMin100) {
    // increment prim pointer
    backDB->primMem.curr = primmemCurr + 7;
    p = (POLY_G3*) primmemCurr;
  }

  if (p != 0) {
    *(u_int *)&p->r0 = 0x30005b5b;
    *(u_int *)&p->r1 = 0x30012b32;
    *(u_int *)&p->r2 = 0x3000bbff;

    // Sine(angle)
    length = MATH_Sin(angle2);

    p->x2 = posX + ((length) * 3 >> 0xb) + 0x41;

    // Cosine(angle)
    length = MATH_Cos(angle2);

    length = ((length << 2) >> 0xb) * 0x140;
    if (length < 0) {
      length += 0x1ff;
    }
    p->y2 = posY + (length >> 9) + 0x29;

    // Sine(angle)
    length = MATH_Sin(angle1);

    p->x1 = posX - ((length * 3 >> 0xb) + -0x41);

    // Cosine(angle)
    length = MATH_Cos(angle1);

    length = (length * 3 >> 0xb) * 0x140;
    if (length < 0) {
      length += 0x1ff;
    }
    p->y1 = posY - ((length >> 9) + -0x29);

    // Sine(angle)
    length = MATH_Sin(angle1);

    p->x0 = posX + (length * 0x1e >> 0xb) + 0x41;

    // Cosine(angle)
    length = MATH_Cos(angle1);

    length = (length * 0x1e >> 0xb) * 0x140;
    if (length < 0) {
      length += 0x1ff;
    }
    p->y0 = posY + (length >> 9) + 0x29;

    // pointer to OT memory
    primmemCurr = gGT->tileView_UI.ptrOT;

    *(int *)p = *primmemCurr | 0x6000000;
    *primmemCurr = (u_int) p & 0xffffff;

    p = 0;

    // if there is room for more
    if (primmemCurr <= (u_long*) backDB->primMem.endMin100) {
      // increment prim pointer
      backDB->primMem.curr = primmemCurr + 7;
      p = (POLY_G3*) primmemCurr;
    }

    if (p != 0) {
      *(u_int *)&p->r0 = 0x30ffffff;
      *(u_int *)&p->r1 = 0x3000699c;
      *(u_int *)&p->r2 = 0x3000ffff;

      // Sine(angle)
      length = MATH_Sin(angle2);

      p->x2 = posX - ((length * 3 >> 0xb) + -0x41);

      // Cosine(angle)
      length = MATH_Cos(angle2);

      length = ((length << 2) >> 0xb) * 0x140;
      if (length < 0) {
        length += 0x1ff;
      }
      p->y2 = posY - ((length >> 9) + -0x29);

      // Sine(angle)
      length = MATH_Sin(angle1);

      p->x1 = posX - ((length * 3 >> 0xb) + -0x41);

      // Cosine(angle)
      length = MATH_Cos(angle1);

      length = (length * 3 >> 0xb) * 0x140;
      if (length < 0) {
        length += 0x1ff;
      }
      p->y1 = posY - ((length >> 9) + -0x29);

      // Sine(angle)
      length = MATH_Sin(angle1);

      p->x0 = posX + ((length * 0x1e >> 0xb) + 0x41);

      // Cosine(angle)
      length = MATH_Cos(angle1);

      length = (length * 0x1e >> 0xb) * 0x140;
      if (length < 0) {
        length += 0x1ff;
      }
      p->y0 = posY + ((length >> 9) + 0x29);

      // pointer to OT memory
      primmemCurr = gGT->tileView_UI.ptrOT;

      *(int *)p = *primmemCurr | 0x6000000;
      *primmemCurr = (u_int) p & 0xffffff;
    }
  }
  return;
}