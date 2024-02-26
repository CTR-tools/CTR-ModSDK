#include <common.h>

int Player_StickGetStrengthAbsolute(int stickVal, int maxSteer,struct RacingWheelData *rwd)
{
  int pos;

  // center steering
  pos = 0x80;

  // if racing wheel data exists
  if (rwd != NULL)
  {
	// get center of wheel
    pos = rwd->gamepadCenter;
  }

  // if steering right
  if (stickVal - pos < 0)
  {
    pos = Player_StickGetStrength(-(stickVal - pos), maxSteer, rwd);

	// negate result to steer right
	pos = -pos;
  }

  // if steer left
  else
  {
    pos = Player_StickGetStrength(stickVal - pos, maxSteer, rwd);
  }

  // steer result
  return pos;
}
