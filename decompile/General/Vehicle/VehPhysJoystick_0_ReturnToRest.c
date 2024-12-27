#include <common.h>

// less bytes, less instructions, than original
extern struct RacingWheelData rwd_default;

int DECOMP_VehPhysJoystick_ReturnToRest(int stickVal, int half, struct RacingWheelData* rwd)
{	
	if(rwd == 0)
		rwd = &rwd_default;
	
	stickVal -= rwd->gamepadCenter;
	
	if(stickVal < 0)
	{
		return -DECOMP_VehCalc_MapToRange(
			-stickVal,
			rwd->deadZone, rwd->range,
			0, half);
	}
	
	return DECOMP_VehCalc_MapToRange(
		stickVal,
		rwd->deadZone, rwd->range,
		0, half);
}

struct RacingWheelData rwd_default =
{
	.gamepadCenter = 0x80,
	
	.deadZone = 0x30,
	
	.range = 0x7f
};