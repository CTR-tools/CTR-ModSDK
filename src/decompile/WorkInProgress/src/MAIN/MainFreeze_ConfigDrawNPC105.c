#include <common.h>

void DECOMP_MainFreeze_ConfigDrawNPC105(short startX, short startY, short param_3, int param_4, short param_5, char *color, u_long *otMem, struct PrimMem *primMem)
{
    u_int angle;
    u_int uVar6;
    char *colors = color;
    short *pos = (short *)malloc(sizeof(short) * 6);

    pos[0] = startX;
    pos[1] = startY;

    do
    {
        angle = (uVar6 + param_5) & 0xFFFF;

        // pretty sure this is just MATH_SIN and MATH_Cos combined into one
        #if 0
        sVar1 = (short)data.trigApprox[angle & 0x3FF];
        iVar4 = data.trigApprox[angle & 0x3FF] >> 0x10;

        if ((angle & 0x400) == 0)
        {
            iVar2 = sVar1;
            if ((angle & 0x800) != 0)
            {
                iVar3 = -iVar4;
                goto LAB_80037b18;
            }
        }
        else
        {
            iVar3 = sVar1;
            iVar2 = iVar4;
            if ((angle & 0x800) == 0)
            {
                iVar4 = -iVar3;
            }
            else
            {
            LAB_80037b18:
                iVar2 = -iVar2;
                iVar4 = iVar3;
            }
        }
        #endif

        pos[4] = startX + (short)((param_3 << 3) * MATH_Cos(angle) >> 0xC) / 5;
        pos[5] = startY + (short)(param_3 * MATH_Sin(angle) >> 0xC);

        if (uVar6 != 0)
        {
            RECTMENU_DrawRwdTriangle(pos, colors, otMem, primMem);
        }

        uVar6 += param_4;
        pos[2] = pos[4];
        pos[3] = pos[5];

        if (uVar6 > 0x1000)
        {
            free(pos);
            return;
        }
    } while (true);
}
