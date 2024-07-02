#include <common.h>

void DECOMP_UI_DrawSpeedNeedle(short posX, short posY, struct Driver * driver)
{
  int minScale = 0;
  #ifdef USE_ONLINE
  int maxScale = 100; // USF
	int speed = driver->kartState == KS_ENGINE_REVVING ?
              driver->unk36E :
              MATH_FastSqrt((driver->xSpeed * driver->xSpeed) + (driver->zSpeed * driver->zSpeed), 0);
  #else
  int maxScale = FP8_INT(driver->const_AccelSpeed_ClassStat) + FP8_INT(driver->const_SacredFireSpeed);
  int speed = driver->unk36E; // is this actually speed?
  #endif
  int minAngle, maxAngle;
  int accelSpeedInt = FP8_INT(driver->const_AccelSpeed_ClassStat);
  if (driver->const_AccelSpeed_ClassStat < speed) {
    #ifdef USE_ONLINE
    maxAngle = ANG(67.5);
    #else
    maxAngle = ANG(157.5);
    #endif
    minAngle = ANG(213.75);
    minScale = (accelSpeedInt * 108000) / 64000;
  } else {
    maxAngle = ANG(213.75);
    minAngle = ANG(305.20);
    maxScale = accelSpeedInt;
  }

  int speedScale = (FP8_INT(speed) * 108000) / 64000;
  maxScale = (maxScale * 108000) / 64000;
  int angle1 = DECOMP_VehCalc_MapToRange(speedScale, minScale, maxScale, minAngle, maxAngle);
  int angle2 = angle1 + ANG(90);

  int cos[2] = {DECOMP_MATH_Cos(angle1), DECOMP_MATH_Cos(angle2)};
  int sin[2] = {WIDE_34(DECOMP_MATH_Sin(angle1)), WIDE_34(DECOMP_MATH_Sin(angle2))};

  PolyG3 * p;
  GetPrimMem(p);
  if (p == nullptr) { return; }

  const PrimCode primCode = { .poly = { .gouraud = 1, .renderCode = RenderCode_Polygon } };

  p->v[0].color = MakeColorCode(91, 91, 0, primCode);
  p->v[1].color = MakeColor(50, 43, 1);
  p->v[2].color = MakeColor(255, 187, 0);

  /* Needle is distorted in the y axis by a factor of 0.625 */
  const int needleHeight = 60;
  const int needleWidth = 6;
  const int needleCenterX = 65;
  const int needleCenterY = 41;

  int yLen = FP_INT(cos[1] * (needleWidth + 2)) * FP8(1.25);
  if (yLen < 0) {
    yLen += FP8(2) - 1;
  }
  yLen /= FP8(2);
  p->v[2].pos.x = posX + (FP_INT(sin[1] * needleWidth) + needleCenterX);
  p->v[2].pos.y = posY + (yLen + needleCenterY);

  yLen = FP_INT(cos[0] * needleWidth) * FP8(1.25);
  if (yLen < 0) {
    yLen += FP8(2) - 1;
  }
  yLen /= FP8(2);
  p->v[1].pos.x = posX - (FP_INT(sin[0] * needleWidth) - needleCenterX);
  p->v[1].pos.y = posY - (yLen - needleCenterY);

  yLen = FP_INT(cos[0] * needleHeight) * FP8(1.25);
  if (yLen < 0) {
    yLen += FP8(2) - 1;
  }
  yLen /= FP8(2);
  p->v[0].pos.x = posX + (FP_INT(sin[0] * needleHeight) + needleCenterX);
  p->v[0].pos.y = posY + (yLen + needleCenterY);

  AddPrimitive(p, sdata->gGT->pushBuffer_UI.ptrOT);
  GetPrimMem(p);
  if (p == nullptr) { return; }

  p->v[0].color = MakeColorCode(255, 255, 255, primCode);
  p->v[1].color = MakeColor(156, 105, 0);
  p->v[2].color = MakeColor(255, 255, 0);

  yLen = FP_INT(cos[1] * (needleWidth + 2)) * FP8(1.25);
  if (yLen < 0) {
    yLen += FP8(2) - 1;
  }
  yLen /= FP8(2);
  p->v[2].pos.x = posX - (FP_INT(sin[1] * needleWidth) - needleCenterX);
  p->v[2].pos.y = posY - (yLen - needleCenterY);

  yLen = FP_INT(cos[0] * needleWidth) * FP8(1.25);
  if (yLen < 0) {
    yLen += FP8(2) - 1;
  }
  yLen /= FP8(2);
  p->v[1].pos.x = posX - (FP_INT(sin[0] * needleWidth) - needleCenterX);
  p->v[1].pos.y = posY - (yLen - needleCenterY);

  yLen = FP_INT(cos[0] * needleHeight) * FP8(1.25);
  if (yLen < 0) {
    yLen += FP8(2) - 1;
  }
  yLen /= FP8(2);
  p->v[0].pos.x = posX + (FP_INT(sin[0] * needleHeight) + needleCenterX);
  p->v[0].pos.y = posY + (yLen + needleCenterY);

  AddPrimitive(p, sdata->gGT->pushBuffer_UI.ptrOT);

  #ifdef USE_ONLINE
  char s_speed[15];
  int speedInt = FP8_INT(speed);
  sprintf(s_speed, "%d", speedInt);
  DECOMP_DecalFont_DrawLine(s_speed, posX + 60, posY + 46, FONT_SMALL, PAPU_YELLOW);
  #endif
}