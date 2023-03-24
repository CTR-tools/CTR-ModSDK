#include <common.h>

void DECOMP_UI_DrawLapCount(short posX,int posY,int param_3,struct Driver* d)
{
  short type;
  short currLap;
  int numLaps;
  int color;
  
  struct GameTracker* gGT;
  int numPlyrCurrGame;
  
  gGT = sdata->gGT;
  numLaps = gGT->numLaps;
  numPlyrCurrGame = gGT->numPlyrCurrGame;
  
  currLap = d->lapIndex + 1;

  if (currLap > numLaps)
	currLap = numLaps;

  // 3P or 4P
  type = 2;
  color = 1;

  // 1P or 2P
  if (numPlyrCurrGame < 3)
  {
	// LAP
    DecalFont_DrawLine(sdata->lngStrings[0x60],posX,posY,2,0x4001);

	type = 1;
    color = 0x4001;
  }
  
  sdata->s_printDividing[0] = currLap + '0';
  sdata->s_printDividing[2] = numLaps + '0';

  // draw string
  DecalFont_DrawLine(&sdata->s_printDividing[0],posX,(posY + 8),type,color);
  return;
}