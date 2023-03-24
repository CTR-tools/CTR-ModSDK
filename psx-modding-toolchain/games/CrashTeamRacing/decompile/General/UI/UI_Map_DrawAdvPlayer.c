#include <common.h>

// Draw dot for Player on 2D Adv Map
void DECOMP_UI_Map_DrawAdvPlayer(int ptrMap,int *param_2,int unused1,int unused2,
                 short param_5,short param_6)

{
  int* puVar1;
  int posX;
  int posY;

  posX = *param_2;
  posY = param_2[2];

  UI_Map_GetIconPos(ptrMap,&posX,&posY);

  puVar1 = &data.playerIconAdvMap.vertCol1[0];
  if ((sdata->gGT->timer & 2) != 0) {
    puVar1 = &data.playerIconAdvMap.vertCol2[0];
  }

  // AH_Map_HubArrow
  AH_Map_HubArrow(
	(int)(short)posX,(int)(short)posY,
	&data.playerIconAdvMap.unk_playerAdvMap[0],
	puVar1,(int)param_6, (int)param_5);
	
  return;
}