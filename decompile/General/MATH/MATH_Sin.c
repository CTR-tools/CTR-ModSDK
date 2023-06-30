#include <common.h>

int DECOMP_MATH_Sin(unsigned int angle)
{
    int sine;
    
    if (IS_ANG_FIRST_OR_THIRD_QUADRANT(angle))
        sine = data.trigApprox[ANG_MODULO_HALF_PI(angle)].sin;
    else
        sine = data.trigApprox[ANG_MODULO_HALF_PI(angle)].cos;

    if (IS_ANG_THIRD_OR_FOURTH_QUADRANT(angle))
        sine = -sine;

    return sine;
}
