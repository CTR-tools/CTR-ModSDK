#include <common.h>

void Garage_Init(void)
{
  struct garageSoundPool* garageSounds;
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

void Garage_Enter(char charId)
{
  struct garageSoundPool* garageSounds;
  char* soundIDs;
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

void Garage_PlayFX(u_int soundId, char charId)
{
  int random = sdata->audioRNG

  if (charId < 8) 
  {
	// if sound == BIRD_RANDOM
    if (soundId == 0xf6)
	{
	  // pick a new sound, 0xF3, 0xF4, or 0xF5,
	  // one of three different bird noises near Pura
		
      random = ((random >> 3) + random * 0x20000000) * 5 + 1;

	  soundId =
				// optimized way to get 1% of something?
				(
					// 100%
					random -

					// 99%
					(
						// 66%
						((random * 0xaaaaaaab >> 0x20) & 0xfffffffe) +

						// 33%
						random / 3
					)
				) + 0xf3;
    }

    OtherFX_Play_LowLevel(soundId & 0xffff,1,

				 // volume
                 sdata->garageSoundPool[charId].volume << 0x10 |

				 // left/right
                 sdata->garageSoundPool[charId].LR

				 // distortion
				 | 0x8000);
  }
  return;
}

void Garage_LerpFX(void)
{
  char cVar1;
  char bVar2;
  short sVar3;
  struct garageSoundPool* garageSounds;
  short sVar5;
  short sVar6;
  int* puVar7;
  char i;

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
          bVar2 = sVar6 < sVar3;
        }
        
		// lerp down
		else 
		{
          sVar3 = garageSounds->volume + -8;
          garageSounds->volume = sVar3;
          bVar2 = sVar3 < sVar6;
        }
        
		// lock on
		if (bVar2) 
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
          bVar2 = (sVar5 < sVar3);
        }
		
		// lerp down
        else 
		{
          sVar3 = garageSounds->LR + -2;
          garageSounds->LR = sVar3;
          bVar2 = (sVar3 < sVar5);
        }
        
		// lock on
		if (bVar2) 
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

void Garage_MoveLR(int desiredId)
{
  struct garageSoundPool* garageSounds;
  char i;
  char charRight;
  char charLeft;

  // left ID
  charLeft = desiredId + -1;

  // if desired is valid
  if (desiredId < 8)
  {
	// right ID
    charRight = desiredId + 1;

	// if left ID is to the left of Crash
    if (charLeft < 0)
	{
	  // use Pura
      charLeft = 7;
    }

	// if right ID is to the right of Pura
	if (7 < charRight)
	{
	  // use Crash
      charRight = 0;
    }

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
  }
  return;
}

void Garage_Leave(void)
{
  int i;

  for (i = 0; i < 8; i++)
  {
    sdata->garageSoundPool[i].gsp_curr = GSP_GONE;
  }
  
  return;
}
