#include <common.h>

int DECOMP_MATH_Cos(unsigned int angle)
{
    return MATH_Sin(ANG_MODULO_TWO_PI(angle + 90));
}
