#include <common.h>

void Driver_ConvertSpeedToVectors(struct Driver* driver,int *velocity)
{
  short sine;
  short cos;
  int y_component;
  u_int angle;

  // angle = axisRotationY
  angle = SEXT24(driver->axisRotationY);

  // approximate trigonometry
  sine = (short)MATH_Sin(angle);
  cos = (short)MATH_Cos(angle);

  velocity[1] = driver->speed * sine >> 12;
  y_component = driver->speed * cos >> 12;

  angle = SEXT24(driver->axisRotationX);

  // approximate trigonometry
  cos = (short)MATH_Cos(angle);
  sine = (short)MATH_Sin(angle);
  
  // velocityXYZ[x] and velocityXYZ[z]
  velocity[0] = y_component * sine >> 12;
  velocity[2] = y_component * cos >> 12;
}
