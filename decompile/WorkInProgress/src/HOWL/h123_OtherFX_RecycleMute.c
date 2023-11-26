#include <common.h>

void OtherFX_RecycleMute(int *param_1)
{
    if (*param_1 != 0)
    {
        OtherFX_Stop1(*param_1);
        *param_1 = 0;
    }
}