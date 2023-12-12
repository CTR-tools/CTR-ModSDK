#include <common.h>

void DECOMP_Audio_SetDefaults(void)
{
	sdata->audioDefaults[0] = 0;
	sdata->audioDefaults[1] = 0;
	sdata->audioDefaults[2] = 0;
	sdata->audioDefaults[3] = 0;

    sdata->audioDefaults[4] = 0x80;
    sdata->audioDefaults[5] = 0x80;
    sdata->audioDefaults[6] = 0;
    sdata->audioDefaults[7] = 0;
    sdata->audioDefaults[8] = 0;

    // erase both SoundFadeInput
    sdata->SoundFadeInput[0].unk = 0;
    sdata->SoundFadeInput[0].desiredVolume = 0;
    sdata->SoundFadeInput[0].currentVolume = 0;
    sdata->SoundFadeInput[0].soundID_soundCount = 0;
    sdata->SoundFadeInput[1].unk = 0;
    sdata->SoundFadeInput[1].desiredVolume = 0;
    sdata->SoundFadeInput[1].currentVolume = 0;
    sdata->SoundFadeInput[1].soundID_soundCount = 0;
}