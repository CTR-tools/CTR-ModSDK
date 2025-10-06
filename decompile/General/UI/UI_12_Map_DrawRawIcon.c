#include <common.h>

// Draw icon on map
void DECOMP_UI_Map_DrawRawIcon(
	struct Map* ptrMap, Vec3* pos,
	int iconID,int colorID,int unused,
    short scale)
{

  int *ptrColor;
  struct GameTracker* gGT = sdata->gGT;
  
  Vec2 iconPos;
  iconPos.x = pos->x;
  iconPos.y = pos->z;

  DECOMP_UI_Map_GetIconPos(ptrMap,&iconPos);
  #ifdef USE_ONLINE
  iconPos.y -= 50;
  #endif

  ptrColor = data.ptrColor[colorID];

  struct Icon** iconPtrArray =
  	ICONGROUP_GETICONS(sdata->gGT->iconGroup[5]);

  DECOMP_DecalHUD_DrawPolyGT4(
	iconPtrArray[iconID],
	iconPos.x, iconPos.y,
	&gGT->backBuffer->primMem,
	gGT->pushBuffer_UI.ptrOT,
    ptrColor[0], ptrColor[1], ptrColor[2], ptrColor[3],
	0, (int)scale);

  return;
}