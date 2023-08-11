#include <common.h>

void DECOMP_Garage_Init(void)
{
  struct GarageFX* garageSounds;
  char i;

  // erase backup, keep music, stop all fx
  howl_StopAudio(1,0,1);

  for (i = 0; i < 8; i++)
  {
    garageSounds = &sdata->garageSoundPool[i];
    garageSounds->gsp_curr = GSP_GONE;
    garageSounds->gsp_prev = GSP_GONE;
    garageSounds->volume = 0;
    garageSounds->LR = 0;
    garageSounds->audioPtr = 0;
  }
  return;
}