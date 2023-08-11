#include <common.h>

void DECOMP_Garage_PlayFX(u_int soundId, char charId)
{
  int random = sdata->audioRNG;

  if (charId < 8) 
  {
	// if sound == BIRD_RANDOM
    if (soundId == 0xf6)
	{
	  // pick a new sound, 0xF3, 0xF4, or 0xF5,
	  // one of three different bird noises near Pura
		
      random = ((random >> 3) + random * 0x20000000) * 5 + 1;

	  soundId =
				// optimized way to get 1% of something?
				(
					// 100%
					random -

					// 99%
					(
						// 66%
						((random * 0xaaaaaaab >> 0x20) & 0xfffffffe) +

						// 33%
						random / 3
					)
				) + 0xf3;
    }

    OtherFX_Play_LowLevel(soundId & 0xffff,1,

				 // volume
                 sdata->garageSoundPool[charId].volume << 0x10 |

				 // left/right
                 sdata->garageSoundPool[charId].LR

				 // distortion
				 | 0x8000);
  }
}