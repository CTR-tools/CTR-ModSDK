#ifndef ND_H
#define ND_H

#include <ctr/macros.h>
#include <ctr/math.h>

void ND_LOAD_XnfFile(char* filename, u32 address, char* dummy);
s32 ND_SquareRoot0_stub(s32 n);
int ND_printf(const char* format, ...);
void ND_LOAD_InitCD();

/* MATH */
s32 ND_MATH_Sin(u32 angle);
s32 ND_MATH_Cos(u32 angle);
s32 ND_MATH_Sqrt(u32 n, u32 shift);
void ND_MATH_GetInverseMatrixTransformation(Matrix* out, const Matrix* matrix);
s32 ND_MATH_VectorLength(const SVec3* vector);
void ND_MATH_VectorNormalize(SVec3* vector);
void ND_MATH_CombineMatrixTransformation(Matrix* out, const Matrix* m, const Matrix* n);
void ND_MATH_MatrixMultiplication(Matrix* out, const Matrix* m, const Matrix* n);

#endif