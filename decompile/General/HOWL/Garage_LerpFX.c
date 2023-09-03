#include <common.h>

/**
 * @brief Byte budget: 408/476
 * FUN_800304b8
 */
void DECOMP_Garage_LerpFX(void) {
  struct GarageFX *garageSounds = sdata->garageSoundPool;
  void **audioPtrRef;

  for (int i = 0; i < 8; ++i, ++garageSounds) {
    short targetVolume, targetLR;
    char cVar1 = garageSounds->gsp_curr;

    if (cVar1 == GSP_CENTER) {
      targetVolume = 0xff;
      targetLR = 0x80;
    } else if (cVar1 == GSP_LEFT) {
      targetVolume = 100;
      targetLR = 0x3c;
    } else if (cVar1 == GSP_RIGHT) {
      targetVolume = 100;
      targetLR = 0xc3;
    } else {
      targetVolume = 0;
      targetLR = garageSounds->LR;
    }

    if (targetVolume != garageSounds->volume) {
      short delta = (garageSounds->volume < targetVolume) ? 8 : -8;
      garageSounds->volume += delta;
      if ((delta > 0 && garageSounds->volume > targetVolume) ||
          (delta < 0 && garageSounds->volume < targetVolume)) {
        garageSounds->volume = targetVolume;
      }
    }

    if (targetLR != garageSounds->LR) {
      short delta = (garageSounds->LR < targetLR) ? 2 : -2;
      garageSounds->LR += delta;
      if ((delta > 0 && garageSounds->LR > targetLR) ||
          (delta < 0 && garageSounds->LR < targetLR)) {
        garageSounds->LR = targetLR;
      }
    }

    audioPtrRef = &garageSounds->audioPtr;
    if (sdata->garageSoundIDs[i] != 0) {
      OtherFX_RecycleNew(audioPtrRef, sdata->garageSoundIDs[i],
                         ((int)garageSounds->volume << 0x10) |
                             (int)garageSounds->LR | 0x8000U);
    }

    if (targetLR == garageSounds->LR && targetVolume == garageSounds->volume &&
        garageSounds->gsp_curr == GSP_GONE) {
      OtherFX_RecycleMute(audioPtrRef);
    }
  }
}