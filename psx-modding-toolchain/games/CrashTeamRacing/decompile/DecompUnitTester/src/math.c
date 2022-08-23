#include <common.h>
#include "math.h"

int MATH_Sin(unsigned int angle)
{
    int sine = trigApprox[angle & 0x3FF];

    if ((angle & 0x400) == 0)
        sine = sine << 0x10;

    sine = sine >> 0x10;

    if ((angle & 0x800) != 0)
        sine = -sine;

    return sine;
}

int MATH_Cos(unsigned int angle) {

    int cos = trigApprox[angle & 0x3FF];

    if ((angle & 0x400) != 0)
    {
        cos = (short)cos;
        if ((angle & 0x800) == 0)
            return -cos;
    }
    else
    {
        cos = cos >> 0x10;
        if ((angle & 0x800) != 0)
            return -cos;
    }

    return cos;
}