#include <common.h>

int DECOMP_MATH_Cos(unsigned int angle) {

    int cos = data.trigApprox[angle & 0x3FF];

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
