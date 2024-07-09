#include <common.h>

void DECOMP_CAM_FollowDriver_Spin360(struct CameraDC* cDC, int param_2, struct Driver* d, short* desiredPos, short* desiredRot)
{
  int ratio;
  short spinSpeed;

  // === Union Missing ===
  // Not really "transitionTo" but the variables
  // are shared with other camera modes, therefore
  // need a union with proper names for each mode

  // rotate one way
  spinSpeed = cDC->transitionTo.pos[0];

  // rotate other way for odd number
  if ((d->driverID & 1) != 0)
	spinSpeed = -spinSpeed;

  int angle = cDC->unk90 + spinSpeed;
  cDC->unk90 = angle;

  ratio = MATH_Sin(angle);
  desiredPos[0] = (short)(d->posCurr.x >> 8) + (short)((ratio * cDC->transitionTo.pos[2]) >> 0xc);

  ratio = MATH_Cos(angle);
  desiredPos[2] = (short)(d->posCurr.z >> 8) + (short)((ratio * cDC->transitionTo.pos[2]) >> 0xc);

  desiredPos[1] = (short)(d->posCurr.y >> 8) + cDC->transitionTo.pos[1];

  DECOMP_CAM_LookAtPosition(param_2, &d->posCurr.x, desiredPos, desiredRot);
  return;
}