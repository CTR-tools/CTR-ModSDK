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
        #if BUILD == UsaRetail
        *(unsigned short *)0x800126b8 = modifier;
        *(unsigned short *)0x800126ba = add;
        *(unsigned short *)0x80012728 = modifier;
        *(unsigned short *)0x8001272a = add;
        *(unsigned short *)0x800127b0 = modifier * 2;
        *(unsigned short *)0x800127b2 = add;
        *(unsigned short *)0x80012844 = modifier;
        *(unsigned short *)0x80012846 = add;
        #endif
        #if BUILD == EurRetail
        *(unsigned short *)0x800126d8 = modifier;
        *(unsigned short *)0x800126da = add;
        *(unsigned short *)0x80012748 = modifier;
        *(unsigned short *)0x8001274a = add;
        *(unsigned short *)0x800127d0 = modifier * 2;
        *(unsigned short *)0x800127d2 = add;
        *(unsigned short *)0x80012864 = modifier;
        *(unsigned short *)0x80012866 = add;
        #endif
        #if BUILD == JpnRetail
        *(unsigned short *)0x80013afc = modifier;
        *(unsigned short *)0x80013afe = add;
        *(unsigned short *)0x80013b6c = modifier;
        *(unsigned short *)0x80012b6e = add;
        *(unsigned short *)0x80013bf4 = modifier * 2;
        *(unsigned short *)0x80013bf6 = add;
        *(unsigned short *)0x80013cd4 = modifier;
        *(unsigned short *)0x80013cd6 = add;
        #endif
    }
    else
    {
        #if BUILD == UsaRetail
        *(unsigned int *)0x800126b8 = classic;
        *(unsigned int *)0x80012728 = classic;
        *(unsigned int *)0x800127b0 = classic;
        *(unsigned int *)0x80012844 = classic;
        #endif
        #if BUILD == EurRetail
        *(unsigned int *)0x800126d8 = classic;
        *(unsigned int *)0x80012748 = classic;
        *(unsigned int *)0x800127d0 = classic;
        *(unsigned int *)0x80012864 = classic;
        #endif
        #if BUILD == JpnRetail
        *(unsigned int *)0x80013afc = classic;
        *(unsigned int *)0x80013b6c = classic;
        *(unsigned int *)0x80013bf4 = classic;
        *(unsigned int *)0x80013cd4 = classic;
        #endif
    }
    BOTS_Adv_AdjustDifficulty();
}