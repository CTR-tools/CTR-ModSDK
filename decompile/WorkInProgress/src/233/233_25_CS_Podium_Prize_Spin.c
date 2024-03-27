#include <common.h>

void CS_Podium_Prize_Spin(struct Instance *inst, short* prize)
{
    struct GamepadSystem *gGS;
    short sVar2;
    int iVar3;
    u_int angle;
    int iVar7;
    short lightDir[3];

    // spin rotY
    prize[5] += FPS_HALF(100);

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&inst->matrix, &prize[4]);

    // gamepad buffer
    gGS = sdata->gGamepads;

    // if no specular lighting, quit
    if ((inst->flags & USE_SPECULAR_LIGHT) == 0)
        return;

    sVar2 = prize[0x10];
    prize[0x10] = sVar2 + 0x3f;

    // offset 0x60
    if ((gGS->gamepad[1].buttonsHeldCurrFrame & BTN_L1) != 0)
    {
        prize[0x10] = sVar2;
    }

    iVar3 = (prize[0x10] & 0xfff) - 0x800;

    if (iVar3 < 0)
    {
        iVar3 = -iVar3;
    }

    angle = prize[0xc] + ((prize[0xe] - prize[0xc]) * iVar3 >> 11);

    short sine1 = (short)MATH_Sin(angle);
    short cos = (short)MATH_Cos(angle);

    lightDir[1] = cos;

    iVar7 = ((u_int)prize[0x10] & 0xfff) - 0x800;
    if (iVar7 < 0)
    {
        iVar7 = -iVar7;
    }

    angle = (int)prize[0xD] + ((prize[0xF] - prize[0xD]) * iVar7 >> 0xb);

    
    short sine2 = (short)MATH_Sin(angle);
    cos = (short)MATH_Cos(angle);
    
    lightDir[0] = (short)(sine1 * cos >> 12);
    lightDir[2] = (short)(sine1 * sine2 >> 12);

    Vector_SpecLightSpin3D(inst, &prize[4], &lightDir[0]);
}