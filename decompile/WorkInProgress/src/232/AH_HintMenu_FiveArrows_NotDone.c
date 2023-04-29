#include <common.h>

void DECOMP_AH_HintMenu_FiveArrows(int param_1,short rotation)
{
  int *ptrColor;
  char i;
  
  // loop 5 times
  for (i = 0; i < 5; i++)
  {
    ptrColor = (int*)0x800b51c4;
	
	// blink on even frames
    if ((sdata->frameCounter & 2) != 0) 
	{
      ptrColor = (int*)0x800b51d0;
    }
	AH_Map_HubArrow(
              // posX             posY
              (i * 0x32 + 0x95),(param_1 + 4), 
              // AdvMap pointers
              (short*)0x800b51b8,
                      //scale
              ptrColor,0x800,(int)rotation);
  }
  return;
}