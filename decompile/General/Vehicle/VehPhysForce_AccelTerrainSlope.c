#include <common.h>

void DECOMP_VehPhysForce_AccelTerrainSlope(struct Driver * driver)
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
		driver->terrainMeta1->const_0x100 == 0) { return; }

	int angleLimit = driver->unk457;
	int angle = driver->turnAngleCurr - driver->turnAnglePrev;
	angle = clamp(angle, -angleLimit, angleLimit);
	int sin = MATH_Sin(angle);

	SVec3 vec = {
		.x = FP_MULT(FP8_MULT(driver->terrainMeta1->const_0x100, FP8(-8)), sin),
		.y = 0,
		.z = 0
		};
	SVec3 accel;
	RotateVector(&accel, &vec);
	driver->accel = accel;
}

/*void DECOMP_VehPhysForce_AccelTerrainSlope(struct Driver *driver)
{
	u_int terrain_meta;
	int angleLimit;
	int angle;
	short speedApprox;
	u_short accel;

	// speed
	speedApprox = driver->speedApprox;

	// erase accel
	driver->accel.x = 0;
	driver->accel.y = 0;
	driver->accel.z = 0;

	if (speedApprox < 0)
		speedApprox = -speedApprox;

	// high speed
	if (speedApprox >= 0x301)
	{
		terrain_meta = driver->terrainMeta1->const_0x100;

		if (
			// not on warppad, not crashing, not wall rubbing,
			// must be on quadblock, but not on ice or flying
			((driver->actionsFlagSet & 0x4000) == 0) &&
			(driver->kartState != KS_CRASHING) &&
			(driver->set_0xF0_OnWallRub == 0) &&
			((driver->actionsFlagSet & 1) != 0) &&
			(terrain_meta != 0))
		{

			#ifdef REBUILD_PS1

			// placeholder, flat terrain ONLY
			driver->accel.x = speedApprox; // SINE * accel
			driver->accel.y = 0;
			driver->accel.z = 0; // COS * accel;

			#else
			// kart angle cap from 'straight to camera'
			angleLimit = driver->unk457;

			if (angleLimit < angle)
			{
				angle = angleLimit;
			}
			if (angle < -angleLimit)
			{
				angle = -angleLimit;
			}

			angle = MATH_Sin(angle);

			// FORWARD DIR matrix
			// before this function is called, there is always
			// gte_SetRotMatrix(driver->matrixMovingDir)

			#define gte_ldVXY0(r0) __asm__ volatile("mtc2   %0, $0" \
										:               \
										: "r"(r0))
			#define gte_ldVZ0(r0) __asm__ volatile("mtc2   %0, $1" \
									   :               \
									   : "r"(r0))

			// {X=??, Y=0, Z=0}
			gte_ldVXY0(((((terrain_meta * -8000) >> 8) * angle) >> 12) & 0xffff);
			gte_ldVZ0(0);
			gte_rtv0();

			// new acceleration vector,
			// based on FORWARD DIR of kart
			gte_stlvnl0(accel);
			driver->accel.x = accel;
			gte_stlvnl1(accel);
			driver->accel.y = accel;
			gte_stlvnl2(accel);
			driver->accel.z = accel;
			#endif
		}
	}
}*/
