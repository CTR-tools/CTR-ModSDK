#include <common.h>

void DECOMP_UI_DrawNumWumpa(short posX, short posY, struct Driver* d)
{
  char currWumpa;
  int currWumpa10s;
  int i;
  int iconID;
  struct GameTracker* gGT;
  
  char message[16];

  gGT = sdata->gGT;
  
  // if numPlyrCurrGame is less than 3
  if (gGT->numPlyrCurrGame < 3)
  {
	// Draw 'x' before drawing number of wumpa
    DECOMP_DecalFont_DrawLine(&sdata->s_x[0],(int)posX,posY+4,FONT_SMALL,ORANGE);

	// Draw number after the 'x'
    sprintf(message,&sdata->s_int[0],d->numWumpas);
	DECOMP_DecalFont_DrawLine(message,posX+0xd,(int)posY,FONT_BIG,ORANGE);

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
		
		struct Icon** iconPtrArray =
			ICONGROUP_GETICONS(gGT->iconGroup[5]);
		
		DECOMP_DecalHUD_DrawPolyGT4(
	
			iconPtrArray[iconID],
	
			posX + 0xc * i,
			posY,
	
			// pointer to PrimMem struct
			&gGT->backBuffer->primMem,
	
			// pointer to OT memory
			gGT->pushBuffer_UI.ptrOT,
	
			// color data
			data.ptrColor[ORANGE][0],
			data.ptrColor[ORANGE][1],
			data.ptrColor[ORANGE][2],
			data.ptrColor[ORANGE][3],
	
			0,FP(1.0));
	}
  }
  return;
}
