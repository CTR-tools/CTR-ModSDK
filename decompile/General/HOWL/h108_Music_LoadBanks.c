#include <common.h>

void DECOMP_Music_LoadBanks(void)
{
    u_int bankID;
    struct Bank thisBank;
    struct GameTracker *gGT = sdata->gGT;
    int level = gGT->levelID;
	char* arr = &sdata->audioDefaults[7];

    Audio_SetReverbMode(
        // Level ID
        level,

        // Check to see if this is a boss race
        (gGT->gameMode1 < 0),

        // Boss ID
        gGT->bossID);

    if (level == INTRO_RACE_TODAY)
    {
        Bank_DestroyAll();

        bankID = 0x22;
    }
    else
    {
        // if not Naughty Dog Box
        if (level != NAUGHTY_DOG_CRATE)
        {
            if (sdata->audioDefaults[7] == 0)
            {
                Bank_DestroyAll();

                Bank_Load(0, thisBank);

                sdata->audioDefaults[7] = 1;
            }

            else
            {
                Bank_DestroyUntilIndex(0);
            }

            // loading state of song (one byte)
            arr[1] = 0;
            return;
        }

        // if it is naughty dog box scene

        Bank_DestroyAll();

        bankID = 33;
    }

    sdata->audioDefaults[7] = 0;

    Bank_Load(bankID, thisBank);

    // loading state of song (one byte)
    arr[1] = 3;
}