#include <common.h>

#define gte_ldVXY0(r0) 	__asm__ volatile("mtc2   %0, $0" : : "r"(r0))
#define gte_ldVZ0(r0) 	__asm__ volatile("mtc2   %0, $1" : : "r"(r0))

void OnApplyForces(struct Thread *th, struct Driver *d)
{
    int sinkSpeed;

    // if speed is more than top speed
    if (0x6400 < d->speed)
    {
        // set top speed
        d->speed = 0x6400;
    }

    // vec3_originToCenter
    // origin of driver model is center-bottom of kart,
    // 0x19 is the half-radius of the model,
    // calculate normalVec with magnitude 0x19 of driver,
    // then we can find the "true center" of the model
    gte_SetColorMatrix(&d->matrix330.m[0][0]);
    gte_ldVXY0(0x190000);
    gte_ldVZ0(0);
    gte_lcv0();
    gte_stlvnl0((long *)d->vec3_originToCenter[0]);
    gte_stlvnl1((long *)d->vec3_originToCenter[1]);
    gte_stlvnl2((long *)d->vec3_originToCenter[2]);

    Driver_ConvertSpeedToVectors(d, &d->velocityXYZ[0], 0);

    // if under-quadblock exists
    if (((d->underDriver != 0) &&

            // if quadblock terrain is mud
            (d->underDriver->terrain_type == 14)))
    {
        // if you have not sinked to the mud's bottom (-0x1000)
        if (-0x1000 < d->posCurr[1])
        {
            // sink slower as you approach the mud's bottom
            sinkSpeed = -0x1000 - d->posCurr[1];

            // set driver velY
            if (d->velocityXYZ[1] < sinkSpeed)
            {
                d->velocityXYZ[1] = sinkSpeed;
            }
        }
    }

    OnGravity(d, &d->velocityXYZ[0]);

    // driver is not touching quadblock
    d->currBlockTouching = NULL;

    // normalVec = {0, 0x1000, ...}
    *(u_int *)&d->fill18_postQuadBlock[0] = 0x10000000;

    // normalVec = {0, 0x1000, ...}
     *(u_int *)&d->AxisAngle1_normalVec[0] = 0x10000000;

    // normalVec = {... ..., 0}
    *(u_short *)&d->fill18_postQuadBlock[4] = 0;
    
    // normalVec = {... ..., 0}
    d->AxisAngle1_normalVec[2] = 0;

    // driver quadblock flags?
    *(u_short *)&d->fill18_postQuadBlock[6] = 0;

    // increase velocity by acceleration
    for (char i = 0; i < 3; i++)
        d->velocityXYZ[i] += d->accelXYZ[i];
}