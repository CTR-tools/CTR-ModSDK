#include <common.h>

void NewAdjustDifficulty()
{
    /* Once we decompiled BOTS_Adv_AdjustDifficulty,
    we can say goodbye to these assembly injections
    perhaps even port it to other versions */

    u_short add = 0x2008;
    u_short modifier = sdata->gGT->arcadeDifficulty;
    u_int classic = 0x00624023; // "sub $t0 $v1 $v0"
    if (modifier != 0)
    {
        *(unsigned short *)0x800126b8 = modifier;
        *(unsigned short *)0x800126ba = add;
        *(unsigned short *)0x80012728 = modifier;
        *(unsigned short *)0x8001272a = add;
        *(unsigned short *)0x800127b0 = modifier * 2;
        *(unsigned short *)0x800127b2 = add;
        *(unsigned short *)0x80012844 = modifier;
        *(unsigned short *)0x80012846 = add;
    }
    else
    {
        *(unsigned int *)0x800126b8 = classic;
        *(unsigned int *)0x80012728 = classic;
        *(unsigned int *)0x800127b0 = classic;
        *(unsigned int *)0x80012844 = classic;
    }
    BOTS_Adv_AdjustDifficulty();
}