#include <common.h>

void DECOMP_Garage_Leave(void)
{
  int i;
  struct GarageFX* garageSounds = sdata->garageSoundPool;

  for (i = 0; i < 8; i++)
  {
    garageSounds[i].gsp_curr = GSP_GONE;
  }
  
  return;
}
