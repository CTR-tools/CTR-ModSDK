#include <common.h>

void DECOMP_Garage_Enter(char charId)
{
  struct GarageFX* garageSounds;
  unsigned char* soundIDs;
  char i;
  char charRight;
  char charLeft;
  int* audioPtr;

  // if characterID is valid
  if (charId < 8)
  {
	// characterID to the left
    charLeft = charId + -1;

	// characterID to the right
    charRight = charId + 1;

	// if left of Crash
    if (charLeft < 0)
	{
	  // go to pura
      charLeft = 7;
    }

	// if right of pura
    if (7 < charRight)
	{
	  // go to Crash
      charRight = 0;
    }
    
    soundIDs = &sdata->garageSoundIDs;
    

	// loop through all characters in garage
	for (i = 0; i < 8; i++)
	{
      garageSounds = &sdata->garageSoundPool[i];
	  audioPtr = &garageSounds->audioPtr;
	  
      garageSounds->gsp_prev = GSP_GONE;
      garageSounds->volume = 0;
	  
	  // if this character is in focus
      if (i == charId)
	  {
        garageSounds->gsp_curr = GSP_CENTER;

		// Balance Left/Right
        garageSounds->LR = 0x80;

		if (soundIDs[i] != 0) {
		  OtherFX_RecycleNew(audioPtr,(u_int)soundIDs[i],(int)garageSounds->volume << 0x10 | 0x8080);
		  continue;
		}
	  }

	  // if this character is to the left
	  else if (i == charLeft)
	  {
        garageSounds->gsp_curr = GSP_LEFT;

		// 75% left, 25% right
        garageSounds->LR = 0x3c;

		if (soundIDs[i] != 0) {
          OtherFX_RecycleNew(audioPtr,(u_int)soundIDs[i],(int)garageSounds->volume << 0x10 | 0x803c);
          continue;
        }
      }
		
	  // if this character is to the right
      else if (i == charRight)
	  {
        garageSounds->gsp_curr = GSP_RIGHT;
	  
	  	// 25% left, 75% right
        garageSounds->LR = 0xc3;
	  
	  	if (soundIDs[i] != 0) {
          OtherFX_RecycleNew(audioPtr,(u_int)soundIDs[i],(int)garageSounds->volume << 0x10 | 0x80c3);
          continue;
        }
      }
	  
	  // if this character is too far away
	  // to make any sound at all
      else
	  {
        garageSounds->gsp_curr = GSP_GONE;
        garageSounds->LR = 0x80;
      }
	  
      *audioPtr = 0;

    } 
  }
  return;
}
