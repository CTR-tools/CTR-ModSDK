#include <common.h>

void Audio_AdvHub_SwapSong(u_int levelID)
{
    if ((sdata->unkAudioState == 5) &&
        // If you're on a map in the Adventure Arena
        (levelID - 25 < 5))
    {
        CseqMusic_AdvHubSwap(0, &sdata->advHubSongSet, (1 << (levelID - 25)));
    }
}