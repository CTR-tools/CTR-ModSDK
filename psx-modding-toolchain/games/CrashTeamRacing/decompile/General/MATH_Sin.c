#include <common.h>

int DECOMP_MATH_Sin(unsigned int angle)
{
    int sine = data.trigApprox[angle & 0x3FF];

    if ((angle & 0x400) == 0)
        sine = sine << 0x10;

    sine = sine >> 0x10;

    if ((angle & 0x800) != 0)
        sine = -sine;

    return sine;
}