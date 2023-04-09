#include <common.h>

void DECOMP_DecalHUD_DrawPolyGT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, u_int color0, u_int color1, u_int color2, u_int color3, char transparency, int scale);

int Hello_Main2()
{
	if (!(sdata->gGT->gameMode1 & LOADING))
	{
		DecalHUD_DrawPolyGT4
		(
			sdata->gGT->ptrIcons[1],
			-10, 6,
			&sdata->gGT->backBuffer->primMem,
			sdata->gGT->tileView_UI.ptrOT,
			data.ptrColor[COCO_MAGENTA][0],
			data.ptrColor[GRAY][1],
			data.ptrColor[GRAY][2],
			data.ptrColor[GRAY][3],
			3, 0x1000
		);
	}
}