#include <common.h>
// can only be positive (negated elsewhere)
int Player_StickGetStrength(int desired,int constMax,struct RacingWheelData* rwd)

{
  int deadzone;
  int range;
  int validRange;

  // dead zone
  deadzone = 0x30;

  // if not using a racing wheel
  if (rwd == NULL)
  {
	// range of steering
    range = 0x7f;

	// RangeMinusDeadzone
    validRange = 0x5e;
  }

  // if using a racing wheel
  else
  {
	// dead zone
    deadzone = rwd->deadZone;

	// range
	range = rwd->range;

	// RangeMinusDeadzone
	validRange = range - deadzone;
  }

  // if desired steer < Deadzone
  if (desired < deadzone)
  {
	// dont steer
    return 0;
  }

  // SteerMinusDeadzone
  int steer = desired - deadzone;

  // if desired steer > Range
  if (range <= desired)
  {
	// default to max desired steer
    return constMax;
  }

  // if SteerMinusDeadzone >= Half RangeMinusDeadzone
  if (validRange / 2 <= steer) 
  {
    steer = (steer - validRange / 2) * (constMax - constMax / 5) * 2;
    
	// check error
    #if 0
	if (validZone == 0) trap(0x1c00);
    if ((validZone == -1) && (deadzone == -0x80000000)) trap(0x1800);
    #endif
    
    return steer / validRange + constMax / 5;
  }
  
  // if SteerMinusDeadzone < Half RangeMinusDeadzone
  
  steer = deadzone * (constMax / 5) * 2;
  
  // check error
  #if 0
  if (validZone == 0) trap(0x1c00);
  if ((validZone == -1) && (deadzone == -0x80000000)) trap(0x1800);
  #endif
  
  // xxx / RangeMinusDeadzone
  return steer / validRange;
}