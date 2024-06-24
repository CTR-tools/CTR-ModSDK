#include <common.h>

void DECOMP_UI_VsQuipAssign(struct Driver *d, struct QuipMeta *quip, struct Driver* param_3, int charID)
{
  struct GameTracker *gGT;
  short timer;
  short* rng;
  short* currIndex;
  short* lngIndex;

  // if driver object exists
  if ((d != 0) &&
      (((quip->unk1 & 4) == 0 || (d == param_3))))
  {
    lngIndex = quip->ptrToLngIndex1;
      for (currIndex = lngIndex[4]; currIndex < quip->ptrToLngIndex2; currIndex += 4)
      {
        if (((lngIndex + 4) < (currIndex + 4)) ||
            (((currIndex + 4) == (lngIndex + 4) &&
                (
                    // random number
                    rng = DECOMP_MixRNG_Scramble(),
                    (rng >> 3 & 0xffU) < 0x40))))
        {
          lngIndex = currIndex;
        }
      } 
    
    if (d->EndOfRaceComment_lngIndex != 0)
    {
      rng = (d->EndOfRaceComment_lngIndex + 4);
      if ((lngIndex + 4) <= rng)
      {
        if ((lngIndex + 4) != rng)
        {
          return;
        }

        // Get random number
        rng = DECOMP_MixRNG_Scramble();

        if (0x3f < (rng >> 3 & 0xffU))
        {
          return;
        }
      }
      rng = d->EndOfRaceComment_lngIndex;
      
      if (rng != 0 && rng < -4)
      {
        rng = -rng - 4;
      }
    }
    if (lngIndex < -4)
    {
      lngIndex = -(lngIndex + 4);
    }
    gGT = sdata->gGT;
    d->EndOfRaceComment_lngIndex = lngIndex;
    d->EndOfRaceComment_characterID = charID;

    // 150 frames (5 seconds) for Battle
    timer = FPS_DOUBLE(150);

    // if not battle mode (VS)
    if ((gGT->gameMode1 & BATTLE_MODE) == 0)
    {
      // 300 frames (10 seconds) for VS
      timer = FPS_DOUBLE(300);
    }

    // set cooldown after end of VS race
    gGT->timerEndOfRaceVS = timer;
  }
}