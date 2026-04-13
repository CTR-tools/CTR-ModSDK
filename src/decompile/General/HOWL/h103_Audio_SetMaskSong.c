#include <common.h>

void DECOMP_Audio_SetMaskSong(u_int tempo)
{
    char i;
    u_char isMaskUsed;
    u_int songID;
    struct GameTracker *gGT = sdata->gGT;
    u_int gameMode = gGT->gameMode1;

    // Assume no player is using a mask
    isMaskUsed = false;

    for (i = 0; i < gGT->numPlyrCurrGame; i++)
    {
        // if player is using mask weapon
        if ((gGT->drivers[i]->actionsFlagSet & 0x800000) != 0)
        {
            // There is at least one player using a mask
            isMaskUsed = true;
        }
    }

    // If any player is using a mask
    if (isMaskUsed)
    {
        // Uka song is playing
        songID = 2;

        if (
            // If Uka song is playing
            ((gameMode & UKA_SONG) != 0) ||

            (
                // Aku song is playing
                songID = 1,

                // If Aku song is playing
                (gameMode & AKU_SONG) != 0))
        {
            DECOMP_Music_Adjust(songID, tempo, 0, 0);
        }
    }

    // If no players are using mask
    else
    {
        DECOMP_Music_Adjust(0, tempo, 0, 0);

        if ((gameMode & (UKA_SONG|AKU_SONG)) != 0)
        {
            gGT->gameMode1 &= ~(UKA_SONG|AKU_SONG);
        }
    }
}