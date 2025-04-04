#include <common.h>

// causes bug:
// https://discord.com/channels/527135227546435584/527136553957589005/1349544147916292106

void DECOMP_VehPhysForce_ConvertSpeedToVec(struct Driver* driver)
{
  int yAngle = driver->axisRotationY;
  int ySine = DECOMP_MATH_Sin(yAngle);
  int yCos = DECOMP_MATH_Cos(yAngle);
  int yComponent = FP_MULT(driver->speed, yCos);

  int xAngle = driver->axisRotationX;
  int xCos = DECOMP_MATH_Cos(xAngle);
  int xSine = DECOMP_MATH_Sin(xAngle);

  driver->velocity.x = FP_MULT(yComponent, xSine);
  driver->velocity.y = FP_MULT(driver->speed, ySine);
  driver->velocity.z = FP_MULT(yComponent, xCos);
}
