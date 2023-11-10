#include <common.h>

void DECOMP_Garage_MoveLR(int desiredId)
{
  struct GarageFX* garageSounds;
  char i;
  char charRight;
  char charLeft;

  // shouldn't ever happen
  if (desiredId > 7) return;

  charLeft = (desiredId + -1) & 7;
  charRight = (desiredId + 1) & 7;

  // loop through 8 characters
  for (i = 0; i < 8; i++)
  {
    garageSounds = &sdata->garageSoundPool[i];
    
    // character in focus
    if (i == desiredId) 
    {
      garageSounds->gsp_curr = GSP_CENTER;
    }
    
    else if (i == charLeft)
    {
      if (garageSounds->gsp_curr == GSP_GONE)
      {
    	  // 75% left, 25% right
        garageSounds->LR = 0x3c;
      }
  	
      garageSounds->gsp_curr = GSP_LEFT;
    }
    
    else if (i == charRight)
    {
      if (garageSounds->gsp_curr == GSP_GONE)
  	  {
		// 25% left, 75% right
        garageSounds->LR = 0xc3;
      }
       
  	  garageSounds->gsp_curr = GSP_RIGHT;
    }
        
    else 
    {
      garageSounds->gsp_curr = GSP_GONE;
    }
  }
  return;
}
