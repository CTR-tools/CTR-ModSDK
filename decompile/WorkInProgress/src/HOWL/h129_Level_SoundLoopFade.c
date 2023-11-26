#include <common.h>

void Level_SoundLoopFade(int slot, u_int soundID, int desiredVolume, int fadeRate)
{
    u_char overflow;
    int currVolume;

    // current volume
    currVolume = *(int *)(slot + 8); // SoundFadeInput.currentVolume

    // if current volume = desired
    if (currVolume == desiredVolume)
    {
        // quit, leave audio loop alone,
        // regardless if lerping to 0x0, or 0xFF
        return;
    }

    // desired volume
    *(int *)(slot + 4) = desiredVolume; // SoundFadeInput.desiredVolume

    if (currVolume < desiredVolume)
    {
        // increase at desired rate [param_4]
        *(int *)(slot + 8) = currVolume + fadeRate;

        // if increased too far...
        overflow = desiredVolume < currVolume + fadeRate;
    }

    // if current > desired
    else
    {
        // if equal, skip
        if (currVolume <= desiredVolume)
            goto LAB_8002ea9c;

        // decrease at desired rate [param_4]
        *(int *)(slot + 8) = currVolume - fadeRate;

        // if decreased too far...
        overflow = currVolume - fadeRate < desiredVolume;
    }

    // gone to far...
    if (overflow)
    {
        // set current to desired
        *(int *)(slot + 8) = desiredVolume;
    }

LAB_8002ea9c:

    Level_SoundLoopSet
    (
        slot + 0xc, // &SoundFadeInput.soundID_soundCount

        // sound ID
        soundID,

        // current volume
        *(u_int *)(slot + 8)  // SoundFadeInput.currentVolume
    );
}