#pragma once
#include <macros.h>

// vectors //

typedef union SVec2
{
	struct
	{
		s16 x;
		s16 y;
	};
	s16 v[2];
} SVec2;

typedef union SVec3
{
	struct
	{
		s16 x;
		s16 y;
		s16 z;
	};
	s16 v[3];
} SVec3;

typedef union SVec4
{
	struct
	{
		s16 x;
		s16 y;
		s16 z;
		s16 w;
	};
	s16 v[4];
} SVec4;

typedef union Vec2
{
	struct
	{
		s32 x;
		s32 y;
	};
	s32 v[2];
} Vec2;

typedef union Vec3
{
	struct
	{
		s32 x;
		s32 y;
		s32 z;
	};
	s32 v[3];
} Vec3;

typedef union Vec4
{
	struct
	{
		s32 x;
		s32 y;
		s32 z;
		s32 w;
	};
	s32 v[4];
} Vec4;

typedef struct Matrix {
	s16 m[3][3];
	Vec3 t;
} Matrix;

// trigonometry //

struct TrigTable
{
    s16 sin;
    s16 cos;
};

#define ANG_TWO_PI 0x1000        // 360
#define ANG_PI (ANG_TWO_PI / 2)  // 180
#define ANG_HALF_PI (ANG_PI / 2) // 90

#define ANG_MODULO_TWO_PI(x) ((x) & (ANG_TWO_PI - 1))   // ang % 360
#define ANG_MODULO_PI(x) ((x) & (ANG_PI - 1))           // ang % 180
#define ANG_MODULO_HALF_PI(x) ((x) & (ANG_HALF_PI - 1)) // ang % 90

#define ANG(x) ANG_MODULO_TWO_PI(((short)((((float) x) * ANG_TWO_PI) / 360))) // works for any float, pos or neg

#define IS_ANG_FIRST_OR_THIRD_QUADRANT(x) (((x) & ANG_HALF_PI) == 0) // [0, 90[ \/ [180, 270[
#define IS_ANG_THIRD_OR_FOURTH_QUADRANT(x) ((x) & ANG_PI)            // [180, 360[

// fixed point //

#define FRACTIONAL_BITS_8 8
#define FP8_ONE (1 << FRACTIONAL_BITS_8)
#define FP8_INT(x) ((x) >> FRACTIONAL_BITS_8)
#define FP8_MULT(x, y) (((x) * (y)) >> FRACTIONAL_BITS_8)
#define FP8(x) ((int)(((float)x) * FP8_ONE))

#define FRACTIONAL_BITS 12
#define FP_ONE (1 << FRACTIONAL_BITS)
#define FP_INT(x) ((x) >> FRACTIONAL_BITS)
#define FP_MULT(x, y) (((x) * (y)) >> FRACTIONAL_BITS)
#define FP(x) ((int)(((float)x) * FP_ONE))

short FP_Div(short a, short b); // see fp.c

// at least one of the operands needs to be a fixed point value converted to integer form
// e.g. FP_Mult(0x1000, 0x2000) or FP_Mult(FP(1.0), FP(2.0)) or FP_Mult(3, FP(0.75))
static inline int FP_Mult(int x, int y)
{
	return (x * y) >> FRACTIONAL_BITS;
}

// misc //

#ifndef REBUILD_PC
int abs(int value);
#endif

int clamp(int n, int lo, int hi);
int max(int a, int b);
int min(int a, int b);