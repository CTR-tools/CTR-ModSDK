#include <common.h>

// Draw icon on map
void DECOMP_UI_Map_DrawRawIcon(
	int param_1,int *param_2,
	int iconID,int colorID,int unused,
    short scale)
{
  int posX;
  int posY;
  int *ptrColor;
  struct GameTracker* gGT = sdata->gGT;

  posX = *param_2;
  posY = param_2[2];

  UI_Map_GetIconPos(param_1,&posX,&posY);

  ptrColor = data.ptrColor[colorID];

  DecalHUD_DrawPolyGT4(
	gGT->iconGroup[0]->icons[iconID],
	posX, posY,
	&gGT->backBuffer->primMem,
	gGT->tileView_UI.ptrOT,
    ptrColor[0], ptrColor[1], ptrColor[2], ptrColor[3],
	0, (int)scale);
	
  return;
}