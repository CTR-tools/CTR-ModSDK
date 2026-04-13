#include <common.h>

int DECOMP_VehPhysJoystick_GetStrengthAbsolute(int stickVal, int maxSteer,struct RacingWheelData *rwd)
{
  int center;

  center = 0x80;
  if (rwd != NULL)
    center = rwd->gamepadCenter;

  // if steering right
  if (stickVal - center < 0)
  {
    return 
		-DECOMP_VehPhysJoystick_GetStrength(
			-(stickVal - center), 
			maxSteer, rwd);
  }

  // steer left
  return
  	DECOMP_VehPhysJoystick_GetStrength(
  		stickVal - center, 
  		maxSteer, rwd);
}