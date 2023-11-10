#include <common.h> 

int DECOMP_CountSounds(void)
{
  // watch it increase when scrolling in main menu
  sdata->countSounds += 1;
  if (sdata->countSounds == 0) {
    sdata->countSounds = 1;
  }
  return sdata->countSounds;
}