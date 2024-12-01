#pragma once

// where is this included 
// that's not ifndef guarded?
#ifndef REBUILD_PC

#include <ctr_math.h>
#include <psn00bsdk/include/inline_c.h>

void RotateVector(SVec3 * out, const SVec3 * in);
void MulMatrixVec(Vec3 * out, const Matrix * m, const SVec3 * in);

#endif