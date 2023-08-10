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
    garageSounds->data[0] = 3;
    garageSounds->data[1] = 3;
    garageSounds->data[2] = 0;
    garageSounds->data[4] = 0;
    garageSounds->data[8] = 0;
  }
  return;
}

void Garage_Enter(char charId)
{
  struct garageSoundPool* garageSounds;
  char* idle;
  char* puVar4;
  char i;
  char charRight;
  char charLeft;

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
    
    idle = &sdata->Garage_Idle2;
    

	// loop through all characters in garage
	for (i = 0; i < 8; i++)
	{
    puVar4 = &sdata->garageSoundPool[i].data[8];
    garageSounds = &sdata->garageSoundPool[i];
	  // if this character is in focus
      if (i == charId)
	  {
        garageSounds->data[0] = 0;
        garageSounds->data[1] = 3;
        garageSounds->data[2] = 0;

		// Balance Left/Right
        garageSounds->data[4] = 0x80;

		if (idle[i] == 0) goto LAB_800303bc;
        OtherFX_RecycleNew(puVar4,(u_int)idle[i],(int)garageSounds->data[2] << 0x10 | 0x8080);
      }

	  else
	  {
		// if this character is to the left
        if (i == charLeft)
		{
          garageSounds->data[0] = 1;
          garageSounds->data[1] = 3;
          garageSounds->data[2] = 0;

		  // 75% left, 25% right
          garageSounds->data[4] = 0x3c;

		  if (idle[i] != 0) {
            OtherFX_RecycleNew(puVar4,(u_int)idle[i],(int)garageSounds->data[2] << 0x10 | 0x803c);
            goto LAB_800303c4;
          }
        }
        else
		{
		  // if this character is to the right
          if (i == charRight)
		  {
            garageSounds->data[0] = 2;
            garageSounds->data[1] = 3;
            garageSounds->data[2] = 0;

			// 25% left, 75% right
            garageSounds->data[4] = 0xc3;

			if (idle[i] != 0) {
              OtherFX_RecycleNew(puVar4,(u_int)idle[i],(int)garageSounds->data[2] << 0x10 | 0x80c3);
              goto LAB_800303c4;
            }
          }

		  // if this character is too far away
		  // to make any sound at all
          else
		  {
            garageSounds->data[0] = 3;
            garageSounds->data[1] = 3;
            garageSounds->data[2] = 0;
            garageSounds->data[4] = 0x80;
          }
        }
LAB_800303bc:
        *puVar4 = 0;
      }
LAB_800303c4:
    } 
  }
  return;
}

void Garage_Idle1(u_int soundId, char charId)
{
  int random = sdata->audioRNG

  if (charId < 8) {
    if (soundId == 0xf6)
	{
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
                 sdata->garageSoundPool[charId].data[2] << 0x10 |

				 // left/right
                 sdata->garageSoundPool[charId].data[4]

				 // distortion
				 | 0x8000);
  }
  return;
}

void Garage_Idle2(void)
{
  char cVar1;
  char bVar2;
  short sVar3;
  struct garageSoundPool* garageSounds;
  short sVar5;
  short sVar6;
  char* puVar7;
  char i;

  for (i = 0; i < 8; i++) {
    
  garageSounds = &sdata.garageSoundPool[i];
  puVar7 = &sdata.garageSoundPool[i].data[8];

    cVar1 = garageSounds->data[0];
	
	// center
    if (cVar1 == 0) {
      sVar6 = 0xff;
      sVar5 = 0x80;
    }
    else 
	{
	  // left
      if (cVar1 == 1) {
        sVar6 = 100;
        sVar5 = 0x3c;
      }
      else 
	  {
        sVar6 = 0;
        
		// right
		if (cVar1 == 2) 
		{
          sVar6 = 100;
          sVar5 = 0xc3;
        }
		
		// too far away
        else {
          sVar5 = garageSounds->data[4];
        }
      }
    }
    if ((sVar5 != garageSounds->data[4]) || (sVar6 != garageSounds->data[2])) {
      if (sVar6 != garageSounds->data[2]) {
        sVar3 = garageSounds->data[2] + 8;
        if (garageSounds->data[2] < sVar6) {
          garageSounds->data[2] = sVar3;
          bVar2 = sVar6 < sVar3;
        }
        else {
          sVar3 = garageSounds->data[2] + -8;
          garageSounds->data[2] = sVar3;
          bVar2 = sVar3 < sVar6;
        }
        if (bVar2) {
          garageSounds->data[2] = sVar6;
        }
      }
      if (sVar5 != garageSounds->data[4]) {
        sVar3 = garageSounds->data[4] + 2;
        if (garageSounds->data[4] < sVar5) {
          garageSounds->data[4] = sVar3;
          bVar2 = (sVar5 < sVar3);
        }
        else {
          sVar3 = garageSounds->data[4] + -2;
          garageSounds->data[4] = sVar3;
          bVar2 = (sVar3 < sVar5);
        }
        if (bVar2) {
          garageSounds->data[4] = sVar5;
        }
      }
      if (sdata.Garage_Idle2[i] != 0) {
        OtherFX_RecycleNew(
            *puVar7,
            sdata.Garage_Idle2[i],
            (int)garageSounds->data[2] << 0x10 | (int)garageSounds->data[4] | 0x8000U
            );
      }
      if (((sVar5 == garageSounds->data[4]) && (sVar6 == garageSounds->data[2])) &&
        (
            garageSounds->data[1] = garageSounds->data[0],
            garageSounds->data[0] == 3
        ))
	  {
		// 
        OtherFX_RecycleMute(*puVar7);
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
    garageSounds = &sdata.garageSoundPool[i];
	  // character in focus
      if (i == desiredId) {
        garageSounds->data[0] = 0;
      }
      else
	  {
		// left ID
        if (i == charLeft)
		{
          if (garageSounds->data[0] == 3)
		  {
			// 75% left, 25% right
            garageSounds->data[4] = 0x3c;
          }
          garageSounds->data[0] = 1;
        }
        else
		{
		  // right ID
          if (i == charRight)
		  {
            if (garageSounds->data[0] == 3)
			{
			  // 25% left, 75% right
              garageSounds->data[4] = 0xc3;
            }
            garageSounds->data[0] = 2;
          }
          else {
            garageSounds->data[0] = 3;
          }
        }
      }
    } 
  }
  return;
}

void Garage_Leave(void)
{
  struct garageSoundPool* garageSounds;
  char i;

  // loop 8 times
  for (i = 7; i > -1; i--)
  {
    // start from the last sound pool (8)
    garageSounds = sdata->garageSoundPool[i];
	// write
    garageSounds->data[0] = 3;
  }
  return;
}
