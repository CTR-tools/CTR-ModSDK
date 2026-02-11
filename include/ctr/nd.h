#pragma once

#include <ctr/macros.h>
#include <ctr/math.h>
#include <ctr/rng.h>
#include <ctr/coll.h>
#include <ctr/jitpool.h>
#include <ctr/list.h>

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

/* LIST */
void ND_LIST_Clear(LinkedList* list);
void ND_LIST_AddFront(LinkedList* list, Item* item);
void ND_LIST_AddBack(LinkedList* list, Item* item);
void* ND_LIST_GetNextItem(Item* item);
void* ND_LIST_GetFirstItem(LinkedList* list);
Item* ND_LIST_RemoveMember(LinkedList* list, Item* item);
Item* ND_LIST_RemoveFront(LinkedList* list);
Item* ND_LIST_RemoveBack(LinkedList* list);
void ND_LIST_Init(LinkedList* list, Item* item, s32 itemSize, s32 numItems);

/* MEMPACK */
void* ND_MEMPACK_AllocMem(s32 size);

/* JITPOOL */
void ND_JitPool_Clear(JitPool* AP);
void ND_JitPool_Init(JitPool* AP, s32 maxItems, s32 itemSize);
Item* ND_JitPool_Add(JitPool* AP);
void ND_JitPool_Remove(JitPool* AP, Item* item);

/* MISC */
//TODO: ensure that the signedness of s32 for both of these are correct
void* memset(void* dest, u8 val, s32 len);
void* memcpy(void* dest, const void* src, s32 count);