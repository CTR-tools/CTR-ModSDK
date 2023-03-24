#include <common.h>

void DECOMP_UI_DrawPosSuffix(short param_1,short param_2,struct Driver* d,short param_4)

{
  int currRank;

  // If you're not in Battle Mode
  if ((sdata->gGT->gameMode1 & BATTLE_MODE) == 0) {
    // Get the rank you're in (1st, 2nd, 3rd, etc)
	currRank = d->driverRank;
  }

  // If you are in Battle Mode
  else
  {
	// get the rank that the battle team is in
    currRank = sdata->gGT->battleSetup.finishedRankOfEachTeam[d->BattleHUD.teamID];
  }

  // Draw the suffix of your current position
  DecalFont_DrawLine(sdata->lngStrings[data.stringIndexSuffix[currRank]],
               (int)param_1,(int)param_2,1,(int)param_4);

  // If pointer to instance of "Big Number" is valid
  if (d->BigNumber[0] != 0)
  {
	// Set [something] to position in race + 0x100
    d->BigNumber[0]->matrix.t[2] = (d->driverRank + 0x100);
  }
  return;
}

void DECOMP_UI_DrawLapCount(short posX,int posY,int param_3,struct Driver* d)
{
  char *pcVar1;
  short type;
  short currLap;
  int color;
  char acStack48 [24];

  // get current lap number, then add 1
  currLap = d->lapIndex + 1;

  // if your current lap is more than the number of laps in the race
  if (sdata->gGT->numLaps < currLap)
  {
	// set current lap to the max number of laps in the race (3, 5, 7)
    currLap = sdata->gGT->numLaps;
  }

  // if numPlyrCurrGame is less than 3
  if (sdata->gGT->numPlyrCurrGame < 3)
  {
	// LAP
    DecalFont_DrawLine(sdata->lngStrings[0x60],posX,posY,2,0x4001);

	// turn it into a string
    sprintf(acStack48,sdata->s_intDividing[0],currLap,sdata->gGT->numLaps);

	// copy a pointer to the string
    pcVar1 = acStack48;

	// set the Y value to the top of the string
    type = 1;

	// set the color
    color = 0x4001;
  }

  // if numPlyrCurrGame is 3 or 4
  else
  {
	// set pointer to string
    pcVar1 = sdata->s_printDividing[0];

	// height of text
    type = 2;

	// convert current lap number to ascii
    sdata->s_printDividing[0] = currLap + '0';

	// color
    color = 1;

	// convert number of laps to ascii
    sdata->s_printDividing[2] = sdata->gGT->numLaps + '0';
  }

  // draw string
  DecalFont_DrawLine(pcVar1,posX,(posY + 8) * 0x10000 >> 0x10,type,color);
  return;
}