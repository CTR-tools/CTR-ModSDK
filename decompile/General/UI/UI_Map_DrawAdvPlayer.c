#include <common.h>

// Draw dot for Player on 2D Adv Map
void DECOMP_UI_Map_DrawAdvPlayer(int ptrMap,int *matrix,int unused1,int unused2,
                 short param_5,short param_6)

{
  int* arrowColor;
  int posX;
  int posY;

  posX = *matrix;
  posY = matrix[2];

  DECOMP_UI_Map_GetIconPos(ptrMap,&posX,&posY);

  arrowColor = &data.playerIconAdvMap.vertCol1[0];
  if ((sdata->gGT->timer & FPS_DOUBLE(2)) != 0) {
    arrowColor = &data.playerIconAdvMap.vertCol2[0];
  }

  DECOMP_AH_Map_HubArrow(posX,posY,
	&data.playerIconAdvMap.unk_playerAdvMap[0],
	arrowColor,(int)param_6, (int)param_5);
	
  return;
}