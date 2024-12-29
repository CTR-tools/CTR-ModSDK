#include <common.h>

int DECOMP_VehPhysGeneral_JumpGetVelY(short *normalVec, int *speedXYZ)
{
  int y1 = normalVec[1];
  int result = y1;

  if (y1 < 0)
  {
    result = -y1;
  }

  // nullify if jump is too weak
  if (result < 20) 
	  return 0;

  // this determines if you fly off a ramp or not,
  // regardless if you press L1 or R1

  // if quadblock is flat, normalvec x and z are zero,
  // causing the multiply product to also be zero (no fly)

  // if X points up, and you drive along the X,
  // then you get a high number to fly off the ramp

  result =

      // x2 * x1
      speedXYZ[0] * normalVec[0] +

      // z2 * z1
      speedXYZ[2] * normalVec[2];

  return result / y1;
}