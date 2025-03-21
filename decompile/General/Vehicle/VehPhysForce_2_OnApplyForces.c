#include <common.h>

void DECOMP_VehPhysForce_OnApplyForces(struct Thread * thread, struct Driver * driver)
{
    const int maxMudSinkYLevel = FP(-1);
    const int maxSpeed = FP8(100);
    driver->speed = min(driver->speed, maxSpeed);

    /* origin of driver model is center-bottom of kart,
    use orientation matrix, and half-radius {0, 25, 0},
	to find the "true" center of the 3D model */
    const SVec3 radius = { .x = 0, .y = 25, .z = 0 };
    MulMatrixVec(&driver->originToCenter, (Matrix*)&driver->matrixFacingDir, &radius);

	#ifndef REBUILD_PC
    // DECOMP_VehPhysForce_ConvertSpeedToVec(driver);
	VehPhysForce_ConvertSpeedToVec(driver, &driver->velocity, 0);
	#endif

    if ((driver->underDriver) && (driver->underDriver->terrain_type == TERRAIN_MUD))
    {
        if (driver->posCurr.y > maxMudSinkYLevel)
        {
            // sink slower as you approach the mud's bottom
            int sinkSpeed = maxMudSinkYLevel - driver->posCurr.y;
            driver->velocity.y = max(driver->velocity.y, sinkSpeed);
        }
    }

	#ifndef REBUILD_PC
    VehPhysForce_OnGravity(driver, &driver->velocity);
	#endif

    const SVec3 up = { .x = FP(0), .y = FP(1), .z = FP(0) };
    driver->normalVecUP = up;
    driver->AxisAngle1_normalVec = up;
    driver->unkAA = 0; // driver quadblock flags?
    driver->currBlockTouching = nullptr;

	#ifdef REBUILD_PC
	driver->accel.y = 1; // move upward
	#endif

    for (int i = 0; i < 3; i++)
	{
        driver->velocity.v[i] += driver->accel.v[i];

		#ifdef REBUILD_PC
		// temporary replacement to
		// COLL (which does velocity) and
		// VehPhysForce_TranslateMatrix (which does matrix)
		driver->posCurr.v[i] += driver->velocity.v[i];
		driver->instSelf->matrix.t[i] = driver->posCurr.v[i] >> 8;
		#endif
	}
}