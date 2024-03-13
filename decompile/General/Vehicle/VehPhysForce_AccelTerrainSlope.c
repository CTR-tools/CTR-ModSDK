#include <common.h>

void DECOMP_VehPhysForce_AccelTerrainSlope(struct Driver *driver)
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
			driver->accelXYZ[0] = speedApprox; // SINE * accel
			driver->accelXYZ[1] = 0;
			driver->accelXYZ[2] = 0; // COS * accel;
			
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
			driver->accelXYZ[0] = accel;
			gte_stlvnl1(accel);
			driver->accelXYZ[1] = accel;
			gte_stlvnl2(accel);
			driver->accelXYZ[2] = accel;
			#endif
		}
	}
}
