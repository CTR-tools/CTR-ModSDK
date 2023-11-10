#include <common.h>

int DECOMP_MATH_Cos(unsigned int angle)
{
    return DECOMP_MATH_Sin(ANG_MODULO_TWO_PI(angle + ANG_HALF_PI));
}
