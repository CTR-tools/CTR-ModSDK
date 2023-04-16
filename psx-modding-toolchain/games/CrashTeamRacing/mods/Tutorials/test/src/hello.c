#include <common.h>

void DECOMP_DecalHUD_DrawPolyFT4(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, int scale);

int Hello_Main2()
{
	if (!(sdata->gGT->gameMode1 & LOADING))
	{
		RECT r;
		r.x = -10;
		r.y = 28;
		r.w = 64;
		r.h = 64;

		u_int color = 0xFFFFFF;

		DecalHUD_DrawPolyFT4
		(
			sdata->gGT->ptrIcons[1],
			-10, 32,
			&sdata->gGT->backBuffer->primMem,
			sdata->gGT->tileView_UI.ptrOT,
			SUBTRACT, 0x1000
		);

		CTR_Box_DrawSolidBox(&r, &color, sdata->gGT->tileView_UI.ptrOT, &sdata->gGT->backBuffer->primMem);
	}
}