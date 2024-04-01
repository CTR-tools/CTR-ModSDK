#include <common.h>

void DECOMP_AH_HintMenu_FiveArrows(int param_1,short rotation)
{
  int *ptrColor;
  char i;
  
  ptrColor = &D232.fiveArrow_col1[0];
  if ((sdata->frameCounter & FPS_DOUBLE(2)) != 0)
  	ptrColor = &D232.fiveArrow_col2[0];
  
  for (i = 0; i < 5; i++)
  {	
	DECOMP_AH_Map_HubArrow(
        // posX
        (i * 0x32 + 0x95),
		
		// posY
		(param_1 + 4), 
        
		&D232.fiveArrow_pos[0],
		
        ptrColor,0x800,(int)rotation);
  }
}