#include <common.h>

void DECOMP_Garage_Enter(char charId)
{
	struct GarageFX* garageSounds;
	unsigned char* soundIDs;
	int i;
	int charRight;
	int charLeft;
	int* audioPtr;
	int LR;
	
	if (charId >= 8)
		return;
  
	// characterID to the left/right
    charLeft = (charId + -1) & 7;
    charRight = (charId + 1) & 7;
    
    soundIDs = &sdata->garageSoundIDs[0];
    
	// loop through all characters in garage
	for (i = 0; i < 8; i++)
	{
      garageSounds = &sdata->garageSoundPool[i];
	  
      garageSounds->gsp_prev = GSP_GONE;
      garageSounds->volume = 0;
	  garageSounds->audioPtr = 0;
	  
	  // if this character is in focus
      if (i == charId)
	  {
        garageSounds->gsp_curr = GSP_CENTER;

		// Balance Left/Right
		LR = 0x80;
	  }

	  // if this character is to the left
	  else if (i == charLeft)
	  {
        garageSounds->gsp_curr = GSP_LEFT;

		// 75% left, 25% right
		LR = 0x3c;
      }
		
	  // if this character is to the right
      else if (i == charRight)
	  {
        garageSounds->gsp_curr = GSP_RIGHT;
	  
	  	// 25% left, 75% right
		LR = 0xc3;
      }
	  
	  // if this character is too far away
	  // to make any sound at all
      else
	  {
        garageSounds->gsp_curr = GSP_GONE;
        garageSounds->LR = 0x80;
		continue;
      }
	  
	  // === only if 'i' is center/left/right ===
	  
      garageSounds->LR = LR;
	  
	  if (soundIDs[i] == 0)
		  continue;
	  
      OtherFX_RecycleNew(
	  	&garageSounds->audioPtr,
	  	(int)soundIDs[i],
	  	0x8000 | LR);
	}
}
