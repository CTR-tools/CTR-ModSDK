#pragma once

// vectors //

typedef struct SVec2
{
	short x;
	short y;
} SVec2;

typedef struct SVec3
{
	short x;
	short y;
	short z;
} SVec3;

typedef struct Vec2
{
	int x;
	int y;
} Vec2;

typedef struct Vec3
{
	int x;
	int y;
	int z;
} Vec3;

// trigonometry //

struct TrigTable
{
    short sin;
    short cos;
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
#define FP8(x) ((int)(((float)x) * FP8_ONE))

#define FRACTIONAL_BITS 12
#define FP_ONE (1 << FRACTIONAL_BITS)
#define FP_INT(x) ((x) >> FRACTIONAL_BITS)
#define FP(x) ((int)(((float)x) * FP_ONE))

short FP_Div(short a, short b); // see fp.c

// at least one of the operands needs to be a fixed point value converted to integer form
// e.g. FP_Mult(0x1000, 0x2000) or FP_Mult(FP(1.0), FP(2.0)) or FP_Mult(3, FP(0.75))
force_inline short FP_Mult(short x, short y)
{
	int result = x;
	return (result * y) >> FRACTIONAL_BITS;
}

// misc //

#ifndef REBUILD_PC
force_inline int abs(int value)
{
	return (value < 0) ? (-value) : value;
}
#endif

force_inline int max(int a, int b)
{
	return (a > b) ? a : b;
}

force_inline int min(int a, int b)
{
	return (a < b) ? a : b;
}