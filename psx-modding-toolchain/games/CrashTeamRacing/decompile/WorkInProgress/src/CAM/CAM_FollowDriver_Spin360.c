#include <common.h>

void CAM_FollowDriver_Spin360(struct CameraDC* cDC, short param_2, struct Driver* d, short* desiredPos, short* desiredRot)
{
  int ratio;
  short posX;
  
  // even number driver
  if ((d->driverID & 1) == 0)
  {
    // rotate one way
    posX = cDC->transitionTo.pos[0];
  }
  // odd number driver
  else
  {
    // rotate other way
    posX = -cDC->transitionTo.pos[0];
  }

  cDC->unk90 += posX;

  ratio = MATH_Sin((int)cDC->unk90);
  desiredPos[0] = (short)(d->posCurr[0] >> 8) + (short)((ratio * cDC->transitionTo.pos[2]) >> 0xc);

  desiredPos[1] = (cDC->transitionTo.pos[1] + (short)d->posCurr[1]) >> 8;

  ratio = MATH_Cos((int)cDC->unk90);
  desiredPos[2] = (short)(d->posCurr[2] >> 8) + (short)((ratio * cDC->transitionTo.pos[2]) >> 0xc);

  CAM_LookAtPosition(param_2, &d->posCurr, desiredPos, desiredRot);
  return;
}