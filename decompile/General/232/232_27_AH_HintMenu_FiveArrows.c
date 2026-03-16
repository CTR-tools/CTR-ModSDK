#include <common.h>

void DECOMP_AH_HintMenu_FiveArrows(int posY,short rotation)
{
  int *ptrColor;
  char i;
  
  ptrColor = &D232.fiveArrow_col1[0];
  if ((sdata->frameCounter & FPS_DOUBLE(2)) != 0)
  	ptrColor = &D232.fiveArrow_col2[0];

Vec2* arrowPos;
  
  for (i = 0; i < 5; i++)
  {	
    arrowPos->x = (i * 0x32 + 0x95);
	arrowPos->y = posY + 4;
	
	DECOMP_AH_Map_HubArrow(
	     arrowPos,
        
		&D232.fiveArrow_pos[0],
		
        (char*)ptrColor,0x800,(int)rotation);
  }
}