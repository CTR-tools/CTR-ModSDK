#include <common.h>

int Player_StickReturnToRest(int stickVal, int constCenter, struct RacingWheelData *rwd)

{
  int position;
  int deadzone;
  int range;

  // if not using racing wheel
  if (rwd == NULL)
  {
    // deadzone
    deadzone = 0x30;

    // range
    range = 0x7f;

    // center of wheel
    position = 0x80;
  }

  // if using racing wheel
  else
  {
    // deadzone
    deadzone = rwd->deadzone;

    // range
    range = rwd->range;

    // center of wheel
    position = rwd->gamepadCenter;
  }

  // convert from [0,0xff] to [-0x7f,0x7f]
  stickVal = stickVal - position;

  // negative strength
  if (stickVal < 0)
  {
    stickVal = -stickVal;
    // map value
    position = MapToRange(
        stickVal, deadzone, // [stickVal, deadzone]
        range, 0,            // [range, 0]
        constCenter          // const 0x80 (halfway lerp)
    );
    position = -position;
  }
  // positive strength
  else
  {
    // map value
    position = MapToRange(
        stickVal, deadzone, // [stickVal, deadzone]
        range, 0,           // [range, 0]
        constCenter         // const 0x80 (halfway lerp)
    );
  }
  return position;
}