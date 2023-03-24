#include <common.h>

void DECOMP_UI_DrawNumWumpa(int param_1,int param_2,struct Driver* d)
{
  char currWumpa;
  int currWumpa10s;
  short posX;
  short posY;
  int i;
  int iconID;
  struct GameTracker* gGT;
  
  char message[16];

  gGT = sdata->gGT;
  posX = (short)param_1;
  posY = (short)param_2;

  // if numPlyrCurrGame is less than 3
  if (gGT->numPlyrCurrGame < 3)
  {
	// Draw 'x' before drawing number of wumpa
    DecalFont_DrawLine(&sdata->s_x[0],(int)posX,posY+4,2,0);

	// Draw number after the 'x'
    sprintf(message,&sdata->s_int[0],d->numWumpas);
	DecalFont_DrawLine(message,posX+0xd,(int)posY,1,0);

  }

  // if numPlyrCurrGame is 3 or 4
  else
  {
	// amount of wumpa
    currWumpa = d->numWumpas;

	// amount of wumpa / 10
    currWumpa10s = (currWumpa / 10) * 0x1000000 >> 0x18;
	
	// draw 2 digits
	for(i = 0; i < 2; i++)
	{
		iconID = currWumpa10s;
		if(i > 0) iconID = currWumpa + currWumpa10s * -10;
		
		DecalHUD_DrawPolyGT4(
	
			&gGT->iconGroup[0]->icons[iconID],
	
			posX + 0xc * i,
			posY,
	
			// pointer to PrimMem struct
			&gGT->backBuffer->primMem,
	
			// pointer to OT memory
			gGT->tileView_UI.ptrOT,
	
			// color data
			data.ptrColor[0][0],
			data.ptrColor[0][1],
			data.ptrColor[0][2],
			data.ptrColor[0][3],
	
			0,0x1000);
	}
  }
  return;
}
