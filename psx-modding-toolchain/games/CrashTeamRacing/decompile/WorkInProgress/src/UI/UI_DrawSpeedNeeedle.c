#include <common.h>

void DECOMP_UI_DrawSpeedNeedle(short posX,short posY,struct Driver* driver)

{
  struct GameTracker *gGT;
  short sVar2;
  int iVar3;
  int iVar1;
  u_long *primmemCurr;
  int iVar6;
  struct DB* backDB;
  u_int uVar8;
  int iVar9;
  POLY_G3 *p;
  int local_28;

  // gGT->backBuffer
  backDB = sdata->gGT->backBuffer;

  iVar6 = driver->const_SpeedometerScale_ClassStat;
  iVar9 = iVar6 << 0x10;
  iVar3 = iVar6 + driver->const_SacredFireSpeed >> 8;
  iVar1 = driver->unk36E << 0x10;
  backDB->drawEnv.clip.x = 0;
  iVar9 = iVar9 >> 0x18;
  if (iVar6 < iVar1 >> 0x10) {
    local_28 = 0x700;
    uVar8 = 0x980;
    backDB->drawEnv.clip.x = (iVar9 * 0x1a5e0) / 64000;
  }
  else {
    local_28 = 0x980;
    uVar8 = 0xd90;
    iVar3 = iVar9;
  }

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  sVar2 = MapToRange(((iVar1 >> 0x18) * 0x1a5e0) / 64000,backDB->drawEnv.clip.x,(iVar3 * 0x1a5e0) / 64000,uVar8,
                       local_28);

  // PrimMem ptrCurrent
  primmemCurr = backDB->primMem.curr;

  p = 0;

  // if there is room for more
  if (primmemCurr <= (u_long *)backDB->primMem.endMin100)
  {
	// increment prim pointer
    backDB->primMem.curr = &primmemCurr[7];
    p = (POLY_FT3 *)primmemCurr;
  }

  if (p != 0) {
    iVar3 = sVar2;
    iVar1 = iVar3 + 0x400;
    p->r0 = 0x30005b5b;
    p->r1 = 0x30012b32;
    p->r2 = 0x3000bbff;

	// Sine(angle)
	backDB->drawEnv.clip.x= MATH_Sin(iVar1);

	p->x2 = posX + ((backDB->drawEnv.clip.x) * 3 >> 0xb) + 0x41;

	// Cosine(angle)
	backDB->drawEnv.clip.x= MATH_Cos(iVar1);

	backDB->drawEnv.clip.x= ((backDB->drawEnv.clip.x << 2) >> 0xb) * 0x140;
    if (backDB->drawEnv.clip.x< 0) {
      backDB->drawEnv.clip.x= backDB->drawEnv.clip.x+ 0x1ff;
    }
    p->y2 = posY + (backDB->drawEnv.clip.x >> 9) + 0x29;

	// Sine(angle)
	backDB->drawEnv.clip.x= MATH_Sin(iVar3);

	p->x1 = posX - ((backDB->drawEnv.clip.x * 3 >> 0xb) + -0x41);

	// Cosine(angle)
	backDB->drawEnv.clip.x= MATH_Cos(iVar3);

	backDB->drawEnv.clip.x= (backDB->drawEnv.clip.x * 3 >> 0xb) * 0x140;
    if (backDB->drawEnv.clip.x< 0) {
      backDB->drawEnv.clip.x= backDB->drawEnv.clip.x+ 0x1ff;
    }
    p->y1 = posY - ((backDB->drawEnv.clip.x >> 9) + -0x29);

	// Sine(angle)
	backDB->drawEnv.clip.x= MATH_Sin(iVar3);

	p->x0 = posX + (backDB->drawEnv.clip.x * 0x1e >> 0xb) + 0x41;

	// Cosine(angle)
	backDB->drawEnv.clip.x= MATH_Cos(iVar3);

	gGT = sdata->gGT;
    backDB->drawEnv.clip.x= (backDB->drawEnv.clip.x* 0x1e >> 0xb) * 0x140;
    if (backDB->drawEnv.clip.x< 0) {
      backDB->drawEnv.clip.x= backDB->drawEnv.clip.x+ 0x1ff;
    }
    p->y0 = posY + (backDB->drawEnv.clip.x >> 9) + 0x29;

	// pointer to OT memory
    primmemCurr = gGT->tileView_UI.ptrOT;

    *(int*)p = *primmemCurr | 0x6000000;
    *primmemCurr = (u_int)p & 0xffffff;

	// gGT->backBuffer
    backDB->drawEnv.clip.x= sdata->gGT->backBuffer;

	// PrimMem ptrCurrent
    primmemCurr = backDB->primMem.curr;

	p = 0;

	// if there is room for more
	if (primmemCurr <= (u_long *)backDB->primMem.endMin100)
	{
	  // increment prim pointer
      backDB->primMem.curr = &primmemCurr[7];
      p = (POLY_G3 *)primmemCurr;
    }

    if (p != 0) {
      p->r0 = 0x30ffffff;
      p->r1 = 0x3000699c;
      p->r2 = 0x3000ffff;

	  // Sine(angle)
	  backDB->drawEnv.clip.x= MATH_Sin(iVar1);

	  p->x2 = posX - ((backDB->drawEnv.clip.x * 3 >> 0xb) + -0x41);

	  // Cosine(angle)
	  backDB->drawEnv.clip.x= MATH_Cos(iVar1);

	  backDB->drawEnv.clip.x= ((backDB->drawEnv.clip.x << 2) >> 0xb) * 0x140;
      if (backDB->drawEnv.clip.x< 0) {
        backDB->drawEnv.clip.x= backDB->drawEnv.clip.x+ 0x1ff;
      }
      p->y2 = posY - ((backDB->drawEnv.clip.x >> 9) + -0x29);

	  // Sine(angle)
	  backDB->drawEnv.clip.x= MATH_Sin(iVar3);

	  p->x1 = posX - ((backDB->drawEnv.clip.x * 3 >> 0xb) + -0x41);

	  // Cosine(angle)
	  backDB->drawEnv.clip.x= MATH_Cos(iVar3);

	  backDB->drawEnv.clip.x= (backDB->drawEnv.clip.x * 3 >> 0xb) * 0x140;
      if (backDB->drawEnv.clip.x< 0) {
        backDB->drawEnv.clip.x= backDB->drawEnv.clip.x+ 0x1ff;
      }
      p->y1 = posY - ((backDB->drawEnv.clip.x >> 9) + -0x29);

	  // Sine(angle)
	  backDB->drawEnv.clip.x= MATH_Sin(iVar3);

	  p->x0 = posX + ((backDB->drawEnv.clip.x * 0x1e >> 0xb) + 0x41);

	  // Cosine(angle)
	  backDB->drawEnv.clip.x= MATH_Cos(iVar3);

	  gGT = sdata->gGT;
      backDB->drawEnv.clip.x= (backDB->drawEnv.clip.x * 0x1e >> 0xb) * 0x140;
      if (backDB->drawEnv.clip.x< 0) {
        backDB->drawEnv.clip.x= backDB->drawEnv.clip.x+ 0x1ff;
      }
      *(short *)(p + 10) = posY + ((backDB->drawEnv.clip.x >> 9) + 0x29);

	  // pointer to OT memory
      primmemCurr = gGT->tileView_UI.ptrOT;

      *(int*)p = *primmemCurr | 0x6000000;
      *primmemCurr = (u_int)p & 0xffffff;
    }
  }
  return;
}