#include <common.h>

void DECOMP_UI_DrawLapCount(short posX,int posY,int param_3,struct Driver* d)
{
  short type;
  short currLap;
  int numLaps;
  int flags;
  
  struct GameTracker* gGT;
  int numPlyrCurrGame;
  
  gGT = sdata->gGT;
  numLaps = gGT->numLaps;
  numPlyrCurrGame = gGT->numPlyrCurrGame;
  
  currLap = d->lapIndex + 1;

  if (currLap > numLaps)
	currLap = numLaps;

  // 3P or 4P
  type = FONT_SMALL;
  flags = PERIWINKLE;

  // 1P or 2P
  if (numPlyrCurrGame < 3)
  {
    // LAP
    DECOMP_DecalFont_DrawLine(sdata->lngStrings[0x60/4],posX,posY,FONT_SMALL,(JUSTIFY_RIGHT | PERIWINKLE));

    type = FONT_BIG;
    flags = (JUSTIFY_RIGHT | PERIWINKLE);
  }
  
  #ifdef USE_ONLINE
 
  char message[8];
  char* str = &message[0];
  sprintf(str, &sdata->s_intDividing[0], currLap, numLaps);
 
  #else
  
  char* str = &sdata->s_printDividing[0];
  str[0] = currLap + '0';
  str[2] = numLaps + '0';

  #endif
 
  // draw string
  DECOMP_DecalFont_DrawLine(str,posX,(posY + 8),type,flags);
}