#include <common.h>

void DECOMP_VehPhysForce_CounterSteer(struct Driver * driver)
{
	driver->accel.x = 0;
	driver->accel.y = 0;
	driver->accel.z = 0;

	int speedApprox = abs(driver->speedApprox);
	if (speedApprox <= FP8(3) ||
		driver->actionsFlagSet & ACTION_WARP ||
		driver->kartState == KS_CRASHING ||
		driver->set_0xF0_OnWallRub ||
		!(driver->actionsFlagSet & ACTION_TOUCH_GROUND) ||
		driver->terrainMeta1->counterSteerRatio == 0) { return; }

	int angleLimit = driver->angleMaxCounterSteer;
	int angle = driver->turnAngleCurr - driver->turnAnglePrev;
	angle = clamp(angle, -angleLimit, angleLimit);
	int sin = MATH_Sin(angle);

	const int counterSteerStrength = FP8(-8);
	SVec3 vec = {
		.x = FP_MULT(FP8_MULT(driver->terrainMeta1->counterSteerRatio, counterSteerStrength), sin),
		.y = 0,
		.z = 0
		};
	SVec3 accel;
	RotateVector(&accel, &vec);
	driver->accel = accel;
}