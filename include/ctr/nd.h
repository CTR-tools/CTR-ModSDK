#pragma once

#include <ctr/macros.h>
#include <ctr/math.h>
#include <ctr/rng.h>
#include <ctr/coll.h>

void ND_LOAD_XnfFile(char* filename, u32 address, char* dummy);
void ND_LOAD_InitCD();

s32 ND_SquareRoot0_stub(s32 n);
int ND_printf(const char* format, ...);
int ND_sprintf(const char* outStr, const char* format, ...);

/* MATH */
s32 ND_MATH_Sin(u32 angle);
s32 ND_MATH_Cos(u32 angle);
u32 ND_MATH_Sqrt(u32 n, u32 shift);
void ND_MATH_GetInverseMatrixTransformation(Matrix* out, const Matrix* matrix);
s32 ND_MATH_VectorLength(const SVec3* vector);
void ND_MATH_VectorNormalize(SVec3* vector);
void ND_MATH_CombineMatrixTransformation(Matrix* out, const Matrix* m, const Matrix* n);
void ND_MATH_MatrixMultiplication(Matrix* out, const Matrix* m, const Matrix* n);

/* RNG */
u32 ND_RNG_Rand();
s32 ND_RNG_RandInt(u32 n);
u16 ND_RNG_PseudoRand(u16 n);
u32 ND_RNG_Random(RNGSeed* seed);

/* COLL */
void ND_COLL_ProjectPointToEdge(SVec3* out, const SVec3* v1, const SVec3* v2, const SVec3* point);
void ND_COLL_LoadQuadblockData_LowLOD(CollDCache* cache, const Quadblock* quadblock);
void ND_COLL_LoadQuadblockData_HighLOD(CollDCache* cache, const Quadblock* quadblock);
void ND_COLL_CalculateTrianglePlane(const CollDCache* cache, CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
void ND_COLL_LoadVerticeData(CollDCache* cache);
s32 ND_COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
void ND_COLL_TestTriangle(CollDCache* cache, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
void ND_COLL_TestLeaf_Quadblock(const Quadblock* quadblock, CollDCache* cache);

/* MEMPACK */
void* ND_MEMPACK_AllocMem(s32 size);

/* MISC */
void* memset(void* dest, u8 val, s32 len);