#include <common.h>

u_int DECOMP_Music_GetHighestSongPlayIndex(void)
{
    // 0xffff - no cseq music
    // 0x0000 - song[0] (level music)
    // 0x0001 - song[1] (game aku)

    // "could" be 2 from [2] (menu aku),
    // but the game never sets it

    return sdata->cseqHighestIndex;
}