#include <common.h>

void DECOMP_EngineSound_AI(struct Driver *param_1, struct Driver *param_2, int param_3, int param_4, int param_5, uint LR)
{
  short fill;
  int approxSpd;
  int speedoScale;
  u_int desiredVolume;
  u_int volume;
  u_int distort;

  speedoScale = param_1->const_AccelSpeed_ClassStat;

  if (speedoScale < 0)
    speedoScale = -speedoScale;


  if (
		((param_1->actionsFlagSetPrevFrame & 1) == 0) ||
		(param_1->kartState == KS_DRIFTING)
	 )
  {
    speedoScale += 0xf00;
  }
  else
  {
    approxSpd = param_1->speedApprox;
    if (approxSpd < 0)
    {
      approxSpd = -approxSpd;
    }
    speedoScale = (speedoScale + approxSpd) >> 1;
  }

  approxSpd = speedoScale - param_1->fill_3B6[1];

  if (approxSpd < 0)
    approxSpd = -approxSpd;

  if (approxSpd < 0x601)
  {
    fill = param_1->fill_3B6[0] - 500;
    param_1->fill_3B6[0] = fill;

    if (param_1->kartState == KS_DRIFTING)
    {
      if (fill < 2000)
      {
        param_1->fill_3B6[0] = 2000;
      }
    }
    else
    {
      if ((fill << 0x10) < 0)
      {
        param_1->fill_3B6[0] = 0;
      }
    }
  }
  else
  {
    fill = param_1->fill_3B6[0] + 2000;
    param_1->fill_3B6[0] = fill;
    if (14000 < fill)
    {
      param_1->fill_3B6[0] = 14000;
    }
  }

  param_1->fill_3B6[1] = (short)((speedoScale * 0x89 + param_1->fill_3B6[1] * 0x177) >> 9);

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  desiredVolume = DECOMP_VehCalc_MapToRange(param_1->fill_3B6[0], 0, param_1->const_AccelSpeed_ClassStat, 0x82, 0xe6);

  if (param_4 < 2000 && 200 < param_4)
  {
    // Map value from [oldMin, oldMax] to [newMin, newMax]
    // inverting newMin and newMax will give an inverse range mapping
    desiredVolume = DECOMP_VehCalc_MapToRange(param_4, 200, 2000, desiredVolume, 0);
  }
  else
  {
    desiredVolume = 0;
  }

  char* arr1 = &sdata->audioDefaults[0];
  volume = EngineSound_VolumeAdjust(desiredVolume, arr1[param_3], 10);
  arr1[param_3] = volume;

  // Map value from [oldMin, oldMax] to [newMin, newMax]
  // inverting newMin and newMax will give an inverse range mapping
  speedoScale = DECOMP_VehCalc_MapToRange(param_1->fill_3B6[1], 0, param_1->const_AccelSpeed_ClassStat, 0x3c, 0xaa);
  param_5 = param_5 >> 3;

  if (param_5 < -0x14)
    param_5 = -0x14;
  else if (0x14 < param_5)
    param_5 = 0x14;

  distort = speedoScale - param_5;
  if (distort < 0)
    distort = 0;
  else if (0xff < distort)
    distort = 0xff;

  // L/R min
  if (LR < 0)
    LR = 0;
  // L/R max
  else if (0xff < LR)
    LR = 0xff;

  // distortion
  distort = distort << 8;

  // if echo is required
  if ((param_2->actionsFlagSet & 0x10000) != 0)
    // add echo
    distort |= 0x1000000;

  EngineAudio_Recalculate((param_3 + 0x10),
                          // volume
                          volume << 0x10 |
                          // distortion
                          distort |
                          // L/R
                          LR);
}