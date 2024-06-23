#include <common.h>

// Draw icon on map
void DECOMP_UI_Map_DrawRawIcon(
	int ptrMap,int *param_2,
	int iconID,int colorID,int unused,
    short scale)
{
  int posX;
  int posY;
  int *ptrColor;
  struct GameTracker* gGT = sdata->gGT;

  posX = param_2[0];
  posY = param_2[2];

  DECOMP_UI_Map_GetIconPos(ptrMap,&posX,&posY);
  #ifdef USE_ONLINE
  posY -= 50;
  #endif

  ptrColor = data.ptrColor[colorID];

  struct Icon** iconPtrArray =
  	ICONGROUP_GETICONS(sdata->gGT->iconGroup[5]);

  DECOMP_DecalHUD_DrawPolyGT4(
	iconPtrArray[iconID],
	posX, posY,
	&gGT->backBuffer->primMem,
	gGT->pushBuffer_UI.ptrOT,
    ptrColor[0], ptrColor[1], ptrColor[2], ptrColor[3],
	0, (int)scale);

  return;
}