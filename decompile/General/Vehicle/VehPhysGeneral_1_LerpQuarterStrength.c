#include <common.h>

int DECOMP_VehPhysGeneral_LerpQuarterStrength(int current, int desired)
{
    if (desired != 0)
    {
        desired = desired >> 2;

        if (desired == 0)
        {
            desired = 1;
        }
    }

    if (desired <= current)
    {
        current = desired;
    }

    return current;
}