#include <common.h>

void CS_Podium_Prize_Spin(struct Instance *inst, int prize)
{
    struct GamepadSystem *gGS;
    short sVar2;
    int iVar3;
    u_int angle;
    int iVar7;
    short lightDir[3];

    // spin rotY
    *(short *)(prize + 0xA) += 100;

    // convert 3 rotation shorts into rotation matrix
    ConvertRotToMatrix(&inst->matrix, prize + 8);

    // gamepad buffer
    gGS = sdata->gGamepads;

    // if no specular lighting, quit
    if ((inst->flags & DISABLE_VCOLOR_USE_INSTCOLOR) == 0)
        return;

    sVar2 = *(short *)(prize + 0x20);
    *(short *)(prize + 0x20) = sVar2 + 0x3f;

    // pointer incrementation, offset 0x180, not 0x60
    if ((*(u_int*)&gGS->gamepad[4].data14[0x10] & 0x800) != 0)
    {
        *(short *)(prize + 0x20) = sVar2;
    }

    iVar3 = (*(u_short *)(prize + 0x20) & 0xfff) - 0x800;

    if (iVar3 < 0)
    {
        iVar3 = -iVar3;
    }

    angle = *(short *)(prize + 0x18) + ((*(short *)(prize + 0x1c) - *(short *)(prize + 0x18)) * iVar3 >> 11);

    short sine1 = (short)MATH_Sin(angle);
    short cos = (short)MATH_Cos(angle);

    lightDir[1] = cos;

    iVar7 = ((u_int) * (u_short *)(prize + 0x20) & 0xfff) - 0x800;
    if (iVar7 < 0)
    {
        iVar7 = -iVar7;
    }

    angle = (int)*(short *)(prize + 0x1a) + (((int)*(short *)(prize + 0x1e) - (int)*(short *)(prize + 0x1a)) * iVar7 >> 0xb);

    
    short sine2 = (short)MATH_Sin(angle);
    cos = (short)MATH_Cos(angle);
    
    lightDir[0] = (short)(sine1 * cos >> 12);
    lightDir[2] = (short)(sine1 * sine2 >> 12);

    Vector_SpecLightSpin3D(inst, (prize + 8), &lightDir[0]);
}