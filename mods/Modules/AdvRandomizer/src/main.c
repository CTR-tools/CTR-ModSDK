#include <common.h>

int MixRNG_Scramble();
void LOAD_Callback_Overlay_230();
void LOAD_Callback_Overlay_232();

short pads[];

void NewCallback230()
{
    sdata->lngStrings[0x17d] = "EXPERT";
    LOAD_Callback_Overlay_230();
}

void NewCallback232()
{
    u_short add = 0x2008;
    u_short modifier = sdata->gGT->arcadeDifficulty;
    *(short *)0x80012846 = add;
    *(short *)0x80012844 = modifier;
    *(short *)0x800127b2 = add;
    *(short *)0x800127b0 = modifier;
    *(short *)0x800126ba = add;
    *(short *)0x800126b8 = modifier;
    *(short *)0x8001272a = add;
    *(short *)0x80012728 = modifier;
    LOAD_Callback_Overlay_232();
}

void RunEntryHook()
{
    #if 0
    char i, j, k;
    short temp;
    char offset, range;

    /* Total num of pads = 27
    18 Trophy Tracks
    4 Crystal tracks
    5 Gem Cups
    */
    char offsets[] = {27, 22, 17, 0};
    char ranges[] = {5, 4, 18};

    // Fill them up first
    for (i = 0; i < 27; i++)
    {
        // Gem cup IDs
        if (i > 21)
            pads[i] = 101 + (i - 22);
        else
            pads[i] = i;
    }

    // Shuffle all types of pads within their ranges
    for (i = 0; i < 3; i++)
    {
        offset = offsets[i];
        range = ranges[i];
        for (j = offset; j >= (offset - range) + 1; j--)
        {
            MixRNG_Scramble();
            k = ((RCNT_GetTime_Total() & 0xf) + (sdata->randomNumber >> 8)) % range;
            k = offset - k;

            temp = pads[j];
            pads[j] = pads[k];
            pads[k] = temp;
            printf("%d\n",pads[k]);
        }
    }
    #endif
    // for difficulty modifier
    data.overlayCallbackFuncs[0] = NewCallback230; // menus
    data.overlayCallbackFuncs[2] = NewCallback232; // modify values
}
