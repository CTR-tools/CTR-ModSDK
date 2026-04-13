#include <common.h>

// This still crashes the game
#if 0

// Restore a backup of game options,
// this is stored between GameProgress and AdventureProgress
void RaceConfig_LoadGameOptions(void)
{
    if (sdata->boolHasLoadedOptions == false)
    {
        // set this to true so it won't try loading again
        sdata->boolHasLoadedOptions = true;

        struct GameOptions *options = &sdata->gameOptions;

        char i;

        // loop 3 times (fx, music, voice)
        for (i = 0; i < 3; i++)
            howl_VolumeSet(0, ((short*)&options->volFx)[i]);

        // copy 24 bytes (4 structs) of RWD from sdata to data
        // should be correct but crashes the game
        for (i = 0; i < 4; i++)
        {
            data.rwd[i].gamepadCenter = options->rwd[i].gamepadCenter;
            data.rwd[i].deadZone = options->rwd[i].deadZone;
            data.rwd[i].range = options->rwd[i].range;
        }

        sdata->gGT->gameMode1 = ((sdata->gGT->gameMode1 | options->gameMode1_0xf00) & 0xf00);

        howl_ModeSet((options->audioMode & 1));
    }
}

#endif

// make a backup of game options,
// this is stored between GameProgress and AdventureProgress
void RaceConfig_SaveGameOptions(void)
{
    struct GameOptions * options = &sdata->gameOptions;

    for (char i = 0; i < 3; i++)
    {
        // store a backup of volume
        // volFX, volMusic, volVoice
        ((short*)&options->volFx)[i] = howl_VolumeGet(i) & 0xff;
    }

    // copy 24 bytes (4 structs) of RWD from data to sdata
    for (char i = 0; i < 4; i++)
    {
        options->rwd[i].gamepadCenter = data.rwd[i].gamepadCenter;
        options->rwd[i].deadZone = data.rwd[i].deadZone;
        options->rwd[i].range = data.rwd[i].range;
    }

    options->gameMode1_0xf00 = sdata->gGT->gameMode1 & 0xf00;

    // store a saftery-copy of mode?
    options->audioMode = ((howl_ModeGet() & 0xff) != 0);
}