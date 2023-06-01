int DECOMP_Player_Jump_GetVelY(short* normalVec,int* speedXYZ)
{
  int result;
  int y1;

  y1 = (int)normalVec[1];

  result = y1;
  if (y1 < 0) {
    result = -y1;
  }

  if (0x14 < result)
  {
	// this determines if you fly off a ramp or not,
	// regardless if you press L1 or R1
	
	// if quadblock is flat, normalvec x and z are zero,
	// causing the multiply product to also be zero (no fly)
	
	// if X points up, and you drive along the X,
	// then you get a high number to fly off the ramp

    result =

		// x2 * x1
		speedXYZ[0] * (int)normalVec[0] +

		// z2 * z1
		speedXYZ[2] * (int)normalVec[2];

	// alert debugger on error
	if (y1 == 0) trap(0x1c00);
    if ((y1 == -1) && (result == -0x80000000)) trap(0x1800);

    return result / y1;
  }
  return 0;
}