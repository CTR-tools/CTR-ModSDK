#include <common.h>

// param_1 - SongID (playing)
// param_2 - deltaBPM
// param_3 - 8008d068 for AdvHub
// param_4 - songSetActiveBits
void DECOMP_Music_Adjust(u_int songID, int newTempo, struct SongSet *set, u_int songSetActiveBits)
{
    songID &= 0xffff;

    // if cseq music can play
    if (sdata->cseqBoolPlay != 0)
    {
        if (sdata->cseqHighestIndex == songID)
        {
            // if tempo has changed
            if (sdata->cseqTempo != newTempo)
            {
                CseqMusic_ChangeTempo(sdata->cseqHighestIndex, newTempo);
                sdata->cseqTempo = newTempo;
            }
        }
        else
        {
            CseqMusic_Stop(sdata->cseqHighestIndex);
        }
    }

    // if new SongID
    if (sdata->cseqHighestIndex != songID)
    {
        //  (loopAtEnd)
        CseqMusic_Start(songID, newTempo, set, songSetActiveBits, 1);

        sdata->cseqBoolPlay = true;

        // set active SongID and tempo
        sdata->cseqHighestIndex = songID;
        sdata->cseqTempo = newTempo;
    }
}