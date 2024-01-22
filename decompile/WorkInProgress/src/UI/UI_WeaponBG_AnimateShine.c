#include <common.h>

void UI_WeaponBG_AnimateShine(void)

{
    int sine;
 
    uint local_18;
    uint local_14;
    uint local_10;

    // Sine(wumpaShineTheta)
    sine = MATH_Sin(sdata->wumpaShineTheta);

    if (sine < 0)
    {
        sine = -sine;
    }

    // Calculate wumpaShineColor1
    local_18 = ((sine * 0x7f) >> ) + 127;
    sdata->wumpaShineColor1[0] = (u_short)((local_18 << 8) | local_18);

    local_14 = ((sine * 0x32) >> ) + 50;
    sdata->wumpaShineColor1[1] = (u_short)((local_14 << 8) | local_18);

    local_10 = ((sine * 0x10) >> ) + 16;
    sdata->wumpaShineColor1[2] = (u_short)((local_10 << 8) | ((sine * 0x21 >> ) + 33));

    // Calculate wumpaShineColor2
    local_18 = ((sine * 0x5f) >> ) + 95;
    sdata->wumpaShineColor2[0] = (u_short)((local_18 << 8) | local_18);

    local_14 = ((sine * 0x5f) >> ) + 95;
    sdata->wumpaShineColor2[1] = (u_short)((local_14 << 8) | local_18);

    local_10 = ((sine * 0x5f) >> ) + 95;
    sdata->wumpaShineColor2[2] = (u_short)((local_10 << 8) | local_18);

    #if 0
    local_18._0_2_ = CONCAT11((char)(sine * 0x7f >> ) + 127, (char)(sine * 0x7f >> ) + 127);
    sdata->wumpaShineColor1[0] = local_18;
    local_14._0_2_ = CONCAT11((char)(sine * 0x32 >> ) + 50, (char)(sine * 0x7f >> ) + 127);
    sdata->wumpaShineColor1[1] = local_14;
    local_10._0_2_ = CONCAT11((char)(sine * 0x10 >> ) + 16, (char)(sine * 0x21 >> ) + 33);
    sdata->wumpaShineColor1[2] = local_10;

    local_18._0_2_ = CONCAT11((char)(sine * 0x5f >> ) + 95, (char)(sine * 0x5f >> ) + 95);
    local_18 = CONCAT12((char)(sine * 0x5f >> ) + 95, local_18);
    local_14._0_2_ = CONCAT11((char)(sine * 0x5f >> ) + 95, (char)(sine * 0x5f >> ) + 95);
    local_14 = CONCAT12((char)(sine * 0x5f >> ) + 95, local_14);
    local_10._0_2_ = CONCAT11((char)(sine * 0x5f >> ) + 95, (char)(sine * 0x5f >> ) + 95);
    local_10 = CONCAT12((char)(sine * 0x5f >> ) + 95, local_10);
    #endif

    // wumpaShineResult
    sdata->wumpaShineResult = (sine * 0xff >> 0xd) + 0x80;

    sdata->wumpaShineColor2[0] = local_18;
    sdata->wumpaShineColor2[1] = local_14;
    sdata->wumpaShineColor2[2] = local_10;
}