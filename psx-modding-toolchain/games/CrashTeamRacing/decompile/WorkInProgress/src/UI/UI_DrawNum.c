#include <common.h>

void DECOMP_UI_DrawNumWumpa(int param_1,int param_2,struct Driver* d)
{
  char currWumpa;
  int currWumpa10s;
  short posX;
  short posY;
  char acStack40 [16];

  posX = (short)param_1;
  posY = (short)param_2;

  // if numPlyrCurrGame is less than 3
  if (sdata->gGT->numPlyrCurrGame < 3)
  {
	// Draw 'x' before drawing number of wumpa
    DecalFont_DrawLine(sdata->s_x[0],(int)posX,(param_2 + 4) * 0x10000 >> 0x10,2,0);

	// convert amount of wumpa to string
    sprintf(acStack40,sdata->s_int[0],(d + 0x30));

	// draw string
	DecalFont_DrawLine(acStack40,(param_1 + 0xd) * 0x10000 >> 0x10,(int)posY,1,0);

  }

  // if numPlyrCurrGame is 3 or 4
  else
  {
	// amount of wumpa
    currWumpa = d->numWumpas;

	// amount of wumpa / 10
    currWumpa10s = (currWumpa / 10) * 0x1000000 >> 0x18;

	// In 3P or 4P, we dont have enough time to
	// render strings, so we render individual
	// number icons 0-9

	// Draw the 10s place icon of wumpa fruit
	// DecalHUD_DrawPolyGT4
	DecalHUD_DrawPolyGT4(
    
        sdata->gGT->iconGroup[0]->icons[(currWumpa10s * 4 + 0x14)],

        // Dimensions
        posX,
        posY,

        // pointer to PrimMem struct
        &sdata->gGT->backBuffer->primMem,

        // pointer to OT memory
        sdata->gGT->tileView_UI.ptrOT,

        // color data
        data.ptrColor[0],
        data.ptrColor[1],
        data.ptrColor[2],
        data.ptrColor[3],

        0,0x1000);

	// 0-9 - 10*0
	// 10 - 10*1

	// Draw the 1s place icon of wumpa fruit
	// DecalHUD_DrawPolyGT4
	DecalHUD_DrawPolyGT4(
    
        sdata->gGT->iconGroup[0]->icons[((currWumpa + currWumpa10s * -10) * 4 + 0x14)],

        posX + 0xc,
        posY,

        // pointer to PrimMem struct
        &sdata->gGT->backBuffer->primMem,

        // pointer to OT memory
        sdata->gGT->tileView_UI.ptrOT,

        // color data
        data.ptrColor[0],
        data.ptrColor[1],
        data.ptrColor[2],
        data.ptrColor[3],

        0,0x1000);
  }
  return;
}
 
void DECOMP_UI_DrawNumTimebox(int param_1,int param_2,struct Driver* d)
{
  char acStack32 [16];

  // Draw 'x' before drawing number of time crates
  DecalFont_DrawLine(sdata->s_x[0],(param_1 + 0x14) * 0x10000 >> 0x10,(param_2 + -10) * 0x10000 >> 0x10,2,0);

  // Generate message for screen
  sprintf(acStack32,"%2.02d/%ld",

			// Number of Time Crates collected
			d->numTimeCrates,

			// Number of Total Crates collected
			sdata->gGT->timeCratesInLEV);

  // Draw the string
  DecalFont_DrawLine(acStack32,(param_1 + 0x21) * 0x10000 >> 0x10,(param_2 + -0xe) * 0x10000 >> 0x10,1,0);
  return;
}

void DECOMP_UI_DrawNumRelic(int param_1,int param_2)
{
  // number of relics
  int currRelics;

  // buffer for sprintf string
  char acStack32 [16];

  // Draw 'x' string before drawing number of relics
  DecalFont_DrawLine(sdata->s_x[0],(int)(short)param_1,(param_2 + 4) * 0x10000 >> 0x10,2,0);

  // get number of relics
  currRelics = sdata->gGT->currAdvProfile.numRelics;

  // If you're playing animation to increment number of relics while
  // returning to the podium after earning the relic
  if ((sdata->gGT->gameMode2 & 0x1000000) != 0)
  {
	// subtract one from the number of relics, then
	// after the animation is done, it will show the proper number
    currRelics--;
  }

  // %ld
  // convert number of relics to a string
  sprintf(acStack32,sdata->s_longInt[0],currRelics);

  // draw number of relics
  DecalFont_DrawLine(acStack32,(param_1 + 0xd) * 0x10000 >> 0x10,(int)(short)param_2,1,0);
  return;
}

void DECOMP_UI_DrawNumKey(int param_1,int param_2)
{
  // number of keys
  int currKeys;

  // buffer for sprintf
  char acStack32 [16];

  // Draw 'x' character before drawing number of keys
  DecalFont_DrawLine(sdata->s_x[0],(int)(short)param_1,(param_2 + 4) * 0x10000 >> 0x10,2,0);

  // get number of keys
  currKeys = sdata->gGT->currAdvProfile.numKeys;

  // if you just returned to podium after earning a key, and playing
  // animation for the key counter to be incremented
  if ((sdata->gGT->gameMode2 & 0x2000000) != 0)
  {
	// decrease key count by one until animation ends
    currKeys--;
  }

  // DAT_8008d520
  // %ld
  // turn number of keys into a string
  sprintf(acStack32,sdata->s_longInt[0],currKeys);

  // draw string for number of keys
  DecalFont_DrawLine(acStack32,(param_1 + 0xd) * 0x10000 >> 0x10,(int)(short)param_2,1,0);
  return;
}

void DECOMP_UI_DrawNumTrophy(int param_1,int param_2)
{
  // number of trophies
  int currTrophies;

  // buffer for sprintf
  char acStack32 [16];

  // Draw 'x' before the number of trophies
  DecalFont_DrawLine(sdata->s_x[0],(int)(short)param_1,(param_2 + 4) * 0x10000 >> 0x10,2,0);

  // number of trophies in adventure
  currTrophies = sdata->gGT->currAdvProfile.numTrophies;

  // If you're on the podium after winning a trophy
  if ((sdata->gGT->gameMode2 & 0x4000000) != 0)
  {
	// subtract a trophy, until the animation that shows
	// the trophy count incrementing is done
    currTrophies--;
  }

  // DAT_8008d520
  // %ld
  // Add trophy count to string
  sprintf(acStack32,sdata->s_longInt[0],currTrophies);

  // Draw String
  DecalFont_DrawLine(acStack32,(param_1 + 0xd) * 0x10000 >> 0x10,(int)(short)param_2,1,0);
  return;
}

void DECOMP_UI_DrawNumCrystal(int param_1,int param_2,struct Driver* d)
{
  char acStack32 [16];

  // Draw 'x' before drawing the number of crystals
  DecalFont_DrawLine(sdata->s_x[0],(int)(short)param_1,(param_2 + 4) * 0x10000 >> 0x10,2,0);

  // Generate message for screen
  sprintf(acStack32,"%2.02d/%ld",

			// amount of crystals you have
			d->numCrystals,

			// Number of crystals you need to win
      sdata->gGT->numCrystalsInLEV);

  // Draw the string
  DecalFont_DrawLine(acStack32,(param_1 + 0xd) * 0x10000 >> 0x10,(int)(short)param_2,1,0);
  return;
}
