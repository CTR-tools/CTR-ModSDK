#include <common.h>

void Audio_SetDefaults(void)
{
    // AI Engine Sounds?
    DAT_8008d818 = 0;
    DAT_8008d81c = 0;
    DAT_8008d820 = 0;
    DAT_8008d824 = 0;

    DAT_8008d828 = 0x80;
    DAT_8008d82c = 0x80;
    DAT_8008d830 = 0;
    DAT_8008d834 = 0;
    DAT_8008d838 = 0;

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