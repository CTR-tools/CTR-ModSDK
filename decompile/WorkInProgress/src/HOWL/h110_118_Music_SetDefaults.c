#include <common.h>

void Music_Restart(void)
{
    // if cseq music is playing
    if (sdata->cseqBoolPlay != 0)
    {
        CseqMusic_Restart(sdata->cseqHighestIndex, 8);
    }
}

void Music_Stop(void)
{
    // if music is playing
    if (sdata->cseqBoolPlay != 0)
    {
        CseqMusic_Stop(sdata->cseqHighestIndex & 0xffff);

        sdata->cseqBoolPlay = 0;
        sdata->cseqHighestIndex = -1;
    }
}

void Music_Start(u_int songID)
{
    sdata->cseqBoolPlay = true;

    // set highest song index
    sdata->cseqHighestIndex = songID & 0xffff;
}

void Music_End(void)
{
    sdata->cseqBoolPlay = false;

    // no songs are playing
    sdata->cseqHighestIndex = -1;
}

u_int Music_GetHighestSongPlayIndex(void)
{
    // 0xffff - no cseq music
    // 0x0000 - song[0] (level music)
    // 0x0001 - song[1] (game aku)

    // "could" be 2 from [2] (menu aku),
    // but the game never sets it

    return sdata->cseqHighestIndex;
}