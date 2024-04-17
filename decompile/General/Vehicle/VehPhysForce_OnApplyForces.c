#include <common.h>

#define gte_ldVXY0(r0) 	__asm__ volatile("mtc2   %0, $0" : : "r"(r0))
#define gte_ldVZ0(r0) 	__asm__ volatile("mtc2   %0, $1" : : "r"(r0))

void DECOMP_VehPhysForce_OnApplyForces(struct Thread *t, struct Driver *d)
{
    int sinkSpeed;

    // speed cap
    if (d->speed > 0x6400)
        d->speed = 0x6400;

	#ifndef REBUILD_PC
    // vec3_originToCenter
    // origin of driver model is center-bottom of kart,
    // use orientation matrix, and half-radius {0, 0x19, 0},
	// to find the "true" center of the 3D model
    gte_SetColorMatrix(&d->matrixFacingDir.m[0][0]);
    gte_ldVXY0(0x190000);
    gte_ldVZ0(0);
    gte_lcv0();
    gte_stlvnl0((long *)&d->vec3_originToCenter[0]);
    gte_stlvnl1((long *)&d->vec3_originToCenter[1]);
    gte_stlvnl2((long *)&d->vec3_originToCenter[2]);
	#endif

    DECOMP_VehPhysForce_ConvertSpeedToVec(d);

    if (
			// if under-quadblock exists
			(d->underDriver != 0) &&

            // if quadblock terrain is mud
            (d->underDriver->terrain_type == 14)
		)
    {
        // if you have not sinked to the mud's bottom (-0x1000)
        if (-0x1000 < d->posCurr[1])
        {
            // sink slower as you approach the mud's bottom
            sinkSpeed = -0x1000 - d->posCurr[1];

            // set driver velY
            if (d->velocityXYZ[1] < sinkSpeed)
                d->velocityXYZ[1] = sinkSpeed;
        }
    }

	#ifndef REBUILD_PC
    VehPhysForce_OnGravity(d, &d->velocityXYZ[0]);
	#endif

    // driver is not touching quadblock
    d->currBlockTouching = NULL;

    // normalVec = {0, 0x1000, ...}
    *(u_int *)&d->normalVecUP[0] = 0x10000000;
    *(u_int *)&d->AxisAngle1_normalVec[0] = 0x10000000;

    // normalVec = {... ..., 0}
    d->normalVecUP[2] = 0;
    d->AxisAngle1_normalVec[2] = 0;

    // driver quadblock flags?
    d->unkAA = 0;

	#ifdef REBUILD_PC
	d->accelXYZ[1] = 1; // move upward
	#endif
	
    // increase velocity by acceleration
    for (char i = 0; i < 3; i++)
	{
		// comes from Driver_AccesTerrainSlope called previously
        d->velocityXYZ[i] += d->accelXYZ[i];
		
		// temporary replacement to
		// COLL (which does velocity) and
		// VehPhysForce_TranslateMatrix (which does matrix)
		#ifdef REBUILD_PC
		d->posCurr[i] += d->velocityXYZ[i];
		d->instSelf->matrix.t[i] = d->posCurr[i] >> 8;
		#endif
	}
}