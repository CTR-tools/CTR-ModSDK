#include <common.h>

void CameraSlack_PhysAngular(struct Driver *driver)
{
	u_int terrain_meta;
	int angleLimit;
	int angle;
	short speedApprox;

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
		if ((
				// check if driver is not on warppad
				(driver->actionsFlagSet & 0x4000) == 0) &&
			(
				// if not crashing
				driver->kartState != 1
			) &&
			(
				(driver->set_0xF0_OnWallRub == 0) 
			) &&
			( // if driver is on quadblock
				(driver->actionsFlagSet & 1 != 0)
			) &&
				// 0x100 for everything except:
				// 0x000 for "ice" and "none" (mid-air)
			(	
					terrain_meta = driver->terrainMeta1->const_0x100,
					terrain_meta != 0
			)
			)
		{

			// kart angle cap from 'straight to camera'
			angleLimit = (u_char)driver->unk457;

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
			
			gte_ldVXY0(((terrain_meta * -8000) >> 8) * angle >> 0xc & 0xffff);
			gte_ldVZ0(0);
			gte_rtv0();

			// gte_stMAC is not defined yet
			// new acceleration vector
			driver->accelXYZ[0] = (short)gte_stMAC1();
			driver->accelXYZ[1] = (short)gte_stMAC2();
			driver->accelXYZ[2] = (short)gte_stMAC3();
		}
	}
}
