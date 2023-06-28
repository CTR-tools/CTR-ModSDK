#ifndef CTR_MATH_H

#define CTR_MATH_H

// fixed point macros
#define FRACTIONAL_BITS 12
#define FP_ONE (1 << FRACTIONAL_BITS)
#define FP(x) (x * FP_ONE)

short FP_Div(short a, short b); // see fp.c

// to be used with fixed point values already converted to integer form
// e.g. FP_Mult(0x1000, 0x2000) or FP_Mult(FP(1), FP(2))
force_inline short FP_Mult(short x, short y)
{
	int result = x;
	return (result * y) >> FRACTIONAL_BITS;
}

force_inline int abs(int value)
{
	return (value < 0) ? (-value) : value;
}

#endif