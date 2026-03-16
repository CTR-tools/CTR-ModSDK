#include <common.h>

// Draw dot for Player on 2D Adv Map
void DECOMP_UI_Map_DrawAdvPlayer(struct Map* ptrMap,Vec3 *pos,int unused1,int unused2,
                 short angle, short unk800)

{
  int* arrowColor;
  Vec2 iconPos;

  iconPos.x = pos->x;
  iconPos.y = pos->z;

  DECOMP_UI_Map_GetIconPos(ptrMap, &iconPos);

  arrowColor = &data.playerIconAdvMap.vertCol1[0];
  if ((sdata->gGT->timer & FPS_DOUBLE(2)) != 0) {
    arrowColor = &data.playerIconAdvMap.vertCol2[0];
  }

  DECOMP_AH_Map_HubArrow(&iconPos,
	&data.playerIconAdvMap.unk_playerAdvMap[0],
	(char*)arrowColor,(int)unk800, (int)angle);
	
  return;
}