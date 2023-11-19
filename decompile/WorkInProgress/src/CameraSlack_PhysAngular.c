#include <common.h>

void CameraSlack_PhysAngular(struct Driver *driver)
{
	u_int terrain_meta;
	int angleLimit;
	int angle;
	short speedApprox;
	u_short accel;

	// speed
	speedApprox = driver->speedApprox;

	// erase accel
	driver->accelXYZ[0] = 0;
	driver->accelXYZ[1] = 0;
	driver->accelXYZ[2] = 0;

	if (speedApprox < 0)
		speedApprox = -speedApprox;

	// high speed
	if (speedApprox >= 0x301)
	{
		// check if driver is not on warppad
		if (((driver->actionsFlagSet & 0x4000) == 0) &&

			// if not crashing
			(driver->kartState != 1) &&

			((driver->set_0xF0_OnWallRub == 0)) &&

			// if driver is on quadblock
			((driver->actionsFlagSet & 1 != 0)) &&

			// not on ice or flying
			(terrain_meta = driver->terrainMeta1->const_0x100, terrain_meta != 0))
		{

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

			// before this function is called, there is always
			// gte_SetRotMatrix(driver->matrix310)

#define gte_ldVXY0(r0) __asm__ volatile("mtc2   %0, $0" \
										:               \
										: "r"(r0))
#define gte_ldVZ0(r0) __asm__ volatile("mtc2   %0, $1" \
									   :               \
									   : "r"(r0))

			gte_ldVXY0(((((terrain_meta * -8000) >> 8) * angle) >> 12) & 0xffff);
			gte_ldVZ0(0);
			gte_rtv0();

			// new acceleration vector
			gte_stlvnl0(accel);
			driver->accelXYZ[0] = accel;
			gte_stlvnl1(accel);
			driver->accelXYZ[1] = accel;
			gte_stlvnl2(accel);
			driver->accelXYZ[2] = accel;
		}
	}
}
