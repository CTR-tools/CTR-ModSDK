#include <common.h>

void DECOMP_Garage_PlayFX(u_int soundId, char charId)
{
  if (charId < 8) 
  {
	// if sound == BIRD_RANDOM
    if (soundId == 0xf6)
	{
	  // inline audioRNG scramble
      sdata->audioRNG = ((sdata->audioRNG >> 3) + sdata->audioRNG * 0x20000000) * 5 + 1;

	  // pick a new sound, 0xF3, 0xF4, or 0xF5,
	  // one of three different bird noises near Pura
	  soundId = (sdata->audioRNG%3) + 0xf3;
    }

    DECOMP_OtherFX_Play_LowLevel(soundId & 0xffff,1,

				 // volume
                 sdata->garageSoundPool[charId].volume << 0x10 |

				 // left/right
                 sdata->garageSoundPool[charId].LR

				 // distortion
				 | 0x8000);
  }
}