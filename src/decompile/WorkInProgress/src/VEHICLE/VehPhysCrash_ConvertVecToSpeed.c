#include <common.h>

void DECOMP_VehPhysCrash_ConvertVecToSpeed(struct Driver* d, Vec3 *v)
{
  short speed3D;
  long speed2D;
  int projX;
  int projY;
  int projZ;
  int projOnMovingDirAxis;

  // 2D movement: sqrt(x^2 + z^2 << 0x10)
  speed2D = VehCalc_FastSqrt(v->x * v->x + v->z * v->z, 0x10);

  // 3D movement: sqrt(x^2 + y^2 + z^2 << 0x10)
  speed3D = FP8(VehCalc_FastSqrt(v->x * v->x + v->y * v->y + v->z * v->z, 0x10));

  // Set driver's 3D speed
  d->speed = speed3D;
  
  // Calculate vertical axis rotation (y-axis)
  speed2D = ratan2(FP8(v->y), speed2D);
  d->axisRotationY = (short)speed2D;
  
  // Calculate horizontal axis rotation (x-axis)
  speed2D = ratan2(v->x, v->z);
  d->axisRotationX = (short)speed2D;

  // Project the velocity vector onto the moving direction axis
  projOnMovingDirAxis = FP_INT(
      v->x * (int)d->matrixMovingDir.m[0][1] +
      v->y * (int)d->matrixMovingDir.m[1][1] +
      v->z * (int)d->matrixMovingDir.m[2][1]);
		  
  projX = (int)FP_INT(d->matrixMovingDir.m[0][1] * projOnMovingDirAxis);
  projY = (int)FP_INT(d->matrixMovingDir.m[1][1] * projOnMovingDirAxis);
  projZ = (int)FP_INT(d->matrixMovingDir.m[2][1] * projOnMovingDirAxis);

  // Calculate 3D projection speed
  speed3D = FP8(VehCalc_FastSqrt(projX * projX + projY * projY + projZ * projZ, 0x10));

  d->jumpHeightCurr = speed3D;
  if (projOnMovingDirAxis < 0) {
    d->jumpHeightCurr = -speed3D;
  }

  // Calculate deviation from projection
  projX = v->x - projX;
  projY = v->y - projY;
  projZ = v->z - projZ;

  // Compute approximate speed based on deviation
  speed3D = FP8(VehCalc_FastSqrt(projX * projX + projY * projY + projZ * projZ, 0x10));

  d->speedApprox = speed3D;

  if (
      projX * d->matrixMovingDir[0][2] + 
      projY * d->matrixMovingDir[1][2] +
      projZ * d->matrixMovingDir[2][2] < 0) 
  {
    d->speedApprox = -speed3D;
  }
}
