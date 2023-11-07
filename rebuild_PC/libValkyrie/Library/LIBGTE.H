#ifndef LIBGTE_H
#define LIBGTE_H

#include "SYSTEM/TYPES.H"

#include "GTEREG.H"

#include "LIBGPU.H"

#if defined(__ANDROID__)
#ifdef __cplusplus
extern "C" {
#endif
#endif

/*
 * Geometry Structures:
 */
#define	ONE		4096	/* GTE regards 4096 as 1.0 */
#define TMPVTXNUM	16	/* Clip Function Header */
#define OUTVTXNUM	10

extern void InitGeom();
extern void SetGeomOffset(int ofx, int ofy);
extern void SetGeomScreen(int h);
extern unsigned int gte_leadingzerocount(unsigned int lzcs);

extern void SetRotMatrix(MATRIX* m);
extern void SetLightMatrix(MATRIX* m);
extern void SetColorMatrix(MATRIX* m);
extern void SetTransMatrix(MATRIX* m);
extern void PushMatrix();
extern void PopMatrix();
extern long RotTransPers(SVECTOR* v0, long* sxy, long* p, long* flag);
extern void RotTrans(SVECTOR* v0, VECTOR* v1, long* flag);
extern void NormalColorDpq(SVECTOR* v0, CVECTOR* v1, long p, CVECTOR* v2);
extern void NormalColorCol(SVECTOR* v0, CVECTOR* v1, CVECTOR* v2);
extern long RotAverageNclip4(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, SVECTOR* v3, long* sxy0/*arg_10*/, long* sxy1/*arg_14*/, long* sxy2/*arg_18*/, long* sxy3/*arg_1C*/, long* p/*arg_20*/, long* otz/*arg_24*/, long* flag/*arg_28*/);
extern MATRIX* MulMatrix0(MATRIX* m0, MATRIX* m1, MATRIX* m2);
extern MATRIX* MulMatrix(MATRIX* m0, MATRIX* m1);
extern MATRIX* MulMatrix2(MATRIX* m0, MATRIX* m1);
extern void SetBackColor(long rbk, long gbk, long bbk);
extern void SetFarColor(long rfc, long gfc, long bfc);
extern MATRIX* RotMatrix(SVECTOR* r, MATRIX* m);
extern MATRIX* TransMatrix(MATRIX* m, VECTOR* v);
extern MATRIX* ScaleMatrix(MATRIX* m, VECTOR* v);
extern void SetDQA(int iDQA);
extern void SetDQB(int iDQB);
extern void SetFogNear(long a, long h);
extern void LoadAverageShort12(SVECTOR* v0, SVECTOR* v1, long p0, long p1, SVECTOR* v2);
extern void LoadAverageCol(u_char* v0, u_char* v1, long p0, long p1, u_char* v2);
#if !defined(KAIN2)
extern int rsin(int a);
extern int rcos(int a);
#endif
extern long ratan2(long y, long x);
extern long DivideFT4(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, SVECTOR* v3, long* sxy0, long* sxy1, long* sxy2, long* sxy3, CVECTOR* col0, POLY_FT4* poly, long otz, DIVPOLYGON4* divp4);
extern void DpqColor(CVECTOR* v0, long p, CVECTOR* v1);
extern VECTOR* ApplyMatrix(MATRIX* m, SVECTOR* v0, VECTOR* v1);
extern void ApplyMatrixLV(MATRIX* mat, VECTOR* v0, VECTOR* v1);
extern SVECTOR* ApplyMatrixSV(MATRIX* m, SVECTOR* v0, SVECTOR* v1);
extern MATRIX* CompMatrix(MATRIX* m0, MATRIX* m1, MATRIX* m2);
extern void CompMatrixLV(MATRIX* m0, MATRIX* m1, MATRIX* m2);
extern long RotAverageNclip3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0, long* sxy1, long* sxy2, long* p, long* otz, long* flag);
extern void SetFogNearFar(long a, long b, long h);
extern long RotTransPers4(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, SVECTOR* v3, long* sxy0, long* sxy1, long* sxy2, long* sxy3, long* p, long* flag);
extern void RotTransSV(SVECTOR* v0, SVECTOR* v1, long* flag);
extern long TransRotPers(SVECTOR* v0, long* sxy, long* p, long* flag);
extern long NormalClip(long sxy0, long sxy1, long sxy2);
extern MATRIX* TransposeMatrix(MATRIX* m0, MATRIX* m1);

#if 0
extern MATRIX* RotMatrixX(long r, MATRIX* m);
extern MATRIX* RotMatrixY(long r, MATRIX* m);
extern MATRIX* RotMatrixZ(long r, MATRIX* m);
#endif

#if defined(PGXP)
#define MAX_NUM_VERTICES 32768
#define PGXP_MAGIC_FLAG 0x8000
#define PGXP_INDEX_BITS 0x7FFF

struct PGXPVertex
{
	unsigned int originalSXY2;
	unsigned int originalSZ3;
	float x;
	float y;
	float z;
	int used;
};

extern struct PGXPVertex pgxp_vertex_buffer[MAX_NUM_VERTICES];
extern int pgxp_vertex_count;
#endif

#if defined(__ANDROID__)
#ifdef __cplusplus
}
#endif
#endif

#endif