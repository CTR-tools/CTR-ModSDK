#include <common.h>

void DECOMP_Garage_LerpFX(void)
{
  char cVar1;
  short sVar3;
  struct GarageFX* garageSounds;
  short sVar5;
  short sVar6;
  int i;

  for (i = 0; i < 8; i++) 
  {
    garageSounds = &sdata->garageSoundPool[i];

    cVar1 = garageSounds->gsp_curr;
	
	if (cVar1 == GSP_CENTER) 
	{
      sVar6 = 0xff;
      sVar5 = 0x80;
    }
    
	else if (cVar1 == GSP_LEFT) 
	{
      sVar6 = 100;
      sVar5 = 0x3c;
    }
    
	else if (cVar1 == GSP_RIGHT) 
	{
      sVar6 = 100;
      sVar5 = 0xc3;
    }
	
    else 
	{
	  sVar6 = 0;
      sVar5 = garageSounds->LR;
    }

	// if change is desired, lerp properties
    if ((sVar5 != garageSounds->LR) || (sVar6 != garageSounds->volume)) 
	{
	  // desired audio change
      if (sVar6 != garageSounds->volume) 
	  {
		// lerp up
        if (garageSounds->volume < sVar6) 
		{
		  sVar3 = garageSounds->volume + 8;
          garageSounds->volume = sVar3;
          cVar1 = sVar6 < sVar3;
        }
        
		// lerp down
		else 
		{
          sVar3 = garageSounds->volume + -8;
          garageSounds->volume = sVar3;
          cVar1 = sVar3 < sVar6;
        }
        
		// lock on
		if (cVar1) 
		{
          garageSounds->volume = sVar6;
        }
		
      }
      
	  // desired LR change
	  if (sVar5 != garageSounds->LR) 
	  {
		// lerp up
        if (garageSounds->LR < sVar5) 
		{
		  sVar3 = garageSounds->LR + 2;
          garageSounds->LR = sVar3;
          cVar1 = (sVar5 < sVar3);
        }
		
		// lerp down
        else 
		{
          sVar3 = garageSounds->LR + -2;
          garageSounds->LR = sVar3;
          cVar1 = (sVar3 < sVar5);
        }
        
		// lock on
		if (cVar1) 
		{
          garageSounds->LR = sVar5;
        }
      }
	  
      if (sdata->garageSoundIDs[i] != 0) 
	  {
        OtherFX_RecycleNew(
            garageSounds->audioPtr,
            sdata->garageSoundIDs[i],
            (int)garageSounds->volume << 0x10 | (int)garageSounds->LR | 0x8000U
            );
      }
	  
	  // if desired properties have been reached
      if (((sVar5 == garageSounds->LR) && (sVar6 == garageSounds->volume)) &&
        (
            garageSounds->gsp_prev = garageSounds->gsp_curr,
            garageSounds->gsp_curr == GSP_GONE
        ))
	  {
        OtherFX_RecycleMute(garageSounds->audioPtr);
      }
    }
  } 
  return;
}
