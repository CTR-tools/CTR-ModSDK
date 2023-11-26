#include <common.h>

void OtherFX_RecycleNew(u_int soundID_Count, u_int newSoundID, u_int modifyFlags)
{
     // if this sound is already playing
    if ((soundID_Count != 0) &&

        // if soundID doesn't match new ID
        ((soundID_Count & 0xffff) != newSoundID))
    {
        OtherFX_Stop1(soundID_Count);
        soundID_Count = 0;
    }

    if (newSoundID != -1)
    {
        // if this is a new sound
        if (soundID_Count == 0)
        {
            newSoundID = OtherFX_Play_LowLevel(newSoundID & 0xffff, 0, modifyFlags);
            soundID_Count = newSoundID;
        }
        // if not a new sound,
        // modification of old sound
        else
        {
            OtherFX_Modify(soundID_Count, modifyFlags);
        }
    }
}