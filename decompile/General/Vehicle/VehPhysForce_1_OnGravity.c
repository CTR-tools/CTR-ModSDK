#include <common.h>

void VehPhysForce_OnGravity(struct Driver * driver, Vec3 * velocity)
{
    gte_SetRotMatrix(driver->matrixMovingDir);

    Vec3 rotatedVelocity;
    Matrix matrixMovingT;
    const SVec3 vel = { .x = velocity->x, .y = velocity->y, .z = velocity->z };
    TransposeMatrix(&matrixMovingT, &driver->matrixMovingDir);
    MulMatrixVec_Light(&rotatedVelocity, &matrixMovingT, &vel);

    Vec3 rotatedGravity;
    SVec3 gravity = { .x = 0, .y = -driver->const_Gravity, .z = 0 };
    if (driver->underDriver->quadFlags & QUAD_LOW_GRAVITY)
    {
        gravity.y = -(driver->const_Gravity * 41) / 100;
    }
    gravity.y = (gravity.y * sdata->gGT->elapsedTimeMS) / ELAPSED_MS;
    MulVector_Light(&rotatedGravity, &gravity);

    if (((rotatedGravity.z < 0) && (driver->unk_offset3B2 > 0)) ||
        ((rotatedGravity.z > 0) && (driver->unk_offset3B2 < 0)))
        {
            rotatedGravity.z = 0;
        }

    if ((driver->actionsFlagSet & ACTION_PREVENT_ACCEL) ||
        ((driver->baseSpeed > 0) && (driver->speedApprox < 0)) ||
        ((driver->baseSpeed < 0) && (driver->speedApprox > 0)))
        {
            rotatedGravity.x = 0;
            rotatedGravity.z = 0;
        }

}