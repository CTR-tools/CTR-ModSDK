#include <common.h>

void DECOMP_VehPhysForce_ConvertSpeedToVec(struct Driver* driver)
{
  short sine;
  short cos;
  int y_component;
  u_int angle;
  
  // moved here, for byte budget
  int* velocity = &driver->velocityXYZ[0];

  angle = driver->axisRotationY;
  sine = (short)DECOMP_MATH_Sin(angle);
  cos = (short)DECOMP_MATH_Cos(angle);

  velocity[1] = (driver->speed * sine) >> 12;
  y_component = (driver->speed * cos) >> 12;

  angle = driver->axisRotationX;
  cos = (short)DECOMP_MATH_Cos(angle);
  sine = (short)DECOMP_MATH_Sin(angle);
  
  velocity[0] = (y_component * sine) >> 12;
  velocity[2] = (y_component * cos) >> 12;
}
