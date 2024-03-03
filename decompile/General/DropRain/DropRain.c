#include <common.h>

void DECOMP_DropRain_MakeSound(struct GameTracker *gGT)
{
  int i, lev;
  unsigned int rained;

  rained = 0;
  lev = gGT->levelID;

  // if you are not in
  if (
		(lev != TIGER_TEMPLE) &&
		(lev != CORTEX_CASTLE)
	) 
  {
    return;
  }
    
  for (i = 0; i < gGT->numPlyrCurrGame; i++) 
  {
    rained |= gGT->rainBuffer[i].numParticles_curr;
  }


  // if someone is rained on
  if (rained != 0) 
  {
    // if there is no rain
    if (gGT->rainSoundID == 0) 
      gGT->rainSoundID = DECOMP_OtherFX_Play(0x82, 0);
  }
  
  // if nobody is rained on
  else 
  {
    if (gGT->rainSoundID != 0) 
	{
      DECOMP_OtherFX_Stop1(gGT->rainSoundID);
      gGT->rainSoundID = 0;
    }
  }
  return;
}

void DECOMP_DropRain_Reset(struct GameTracker *gGT) 
{
  gGT->rainSoundID = 0;
  return;
}
