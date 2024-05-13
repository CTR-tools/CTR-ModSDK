#include <common.h>

void DECOMP_OtherFX_RecycleNew(u_int* soundID_Count, u_int newSoundID, u_int modifyFlags)
{
	int local = *soundID_Count;
	
    if (
		// if this sound is already playing
		(local != 0) &&

        // if soundID doesn't match new ID
        ((local & 0xffff) != newSoundID)
	   )
    {
        OtherFX_Stop1(local);
        
		*soundID_Count = 0;
		local = 0;
    }

    if (newSoundID != -1)
    {
        // if this is a new sound
        if (local == 0)
        {
            *soundID_Count = 
				OtherFX_Play_LowLevel(newSoundID & 0xffff, 0, modifyFlags);
        }
        // if not a new sound,
        // modification of old sound
        else
        {
            OtherFX_Modify(local, modifyFlags);
        }
    }
}