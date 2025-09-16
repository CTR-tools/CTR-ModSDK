#include <common.h>

void DECOMP_VehPhysForce_OnApplyForces(struct Thread * thread, struct Driver * driver)
{
    const short maxSpeed = FP8(100);
    if (driver->speed > maxSpeed) { driver->speed = maxSpeed; }

    /* origin of driver model is center-bottom of kart,
    use orientation matrix, and half-radius {0, 25, 0},
	to find the "true" center of the 3D model */
    const SVec3 radius = { .x = 0, .y = 25, .z = 0 };
    #ifndef REBUILD_PC
    gte_SetColorMatrix(&driver->matrixFacingDir);
    gte_loadSVec(&radius, GTE_VECTOR_0);
    gte_mulMatrixVec(&driver->originToCenter, GTE_MATRIX_COLOR, GTE_VECTOR_0);
    #endif

	#ifndef REBUILD_PC
    // DECOMP_VehPhysForce_ConvertSpeedToVec(driver);
	VehPhysForce_ConvertSpeedToVec(driver, &driver->velocity);
	#endif

    const int maxMudSinkYLevel = FP(-1);
    if ((driver->underDriver) && (driver->underDriver->terrain_type == TERRAIN_MUD))
    {
        const int sinkSpeed = maxMudSinkYLevel - driver->posCurr.y;
        if ((driver->posCurr.y > maxMudSinkYLevel) && (sinkSpeed > driver->velocity.y))
        {
            driver->velocity.y = sinkSpeed;
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

    driver->velocity.x += driver->accel.x;
    driver->velocity.y += driver->accel.y;
    driver->velocity.z += driver->accel.z;

    #ifdef REBUILD_PC
    for (int i = 0; i < 3; i++)
	{


		// temporary replacement to
		// COLL (which does velocity) and
		// VehPhysForce_TranslateMatrix (which does matrix)
		driver->posCurr.v[i] += driver->velocity.v[i];
		driver->instSelf->matrix.t[i] = driver->posCurr.v[i] >> 8;
	}
    #endif
}