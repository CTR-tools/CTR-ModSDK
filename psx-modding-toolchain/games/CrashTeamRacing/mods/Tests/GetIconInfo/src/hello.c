#include <common.h>

//void DecalHUD_DrawPolyGT4(struct Icon* icon, u_int posX, int posY, struct PrimMem* primMem, u_long* ot, u_int topLeftColor, u_int topRightColor, u_int bottomLeftColor, u_int bottomRightColor, u_char semitransparencyEnabled, short scale);

int Hello_Main()
{
	int num = 14;
	struct IconGroup* ig = sdata->gGT->iconGroup[num];
	struct Icon* icon;
	int i;
	//struct Icon* icom = sdata->gGT->iconGroup[4]->icons[51];

	if(sdata->gGamepads->gamepad[0].buttonsTapped & BTN_R2)
	{
		if(ig->numIcons > 0)
		{
			printf("icongroup %d: %s\n", num, ig->name);
			printf("num icons: %d\n", ig->numIcons);

			for(i = 0; i < ig->numIcons; i++)
			{
				icon = ig->icons[i];
				printf("%d. %s   Total width: %d Total height: %d   x0: %d x1: %d x2: %d x3: %d y0: %d y1: %d y2: %d y3: %d   CLUT: 0x%04x Tpage: 0x%04x\n", i, icon->name, (icon->X2 - icon->X1), (icon->Y3 - icon->Y1), icon->X1, icon->X2, icon->X3, icon->X4, icon->Y1, icon->Y2, icon->Y3, icon->Y4, icon->paletteXY, icon->pageXY);
			}
		}
		else printf("no dice!\n");
	}

	/*
	DecalHUD_DrawPolyGT4
	(
		icom,

		10,
		170,

		&sdata->gGT->backBuffer->primMem,
		sdata->gGT->camera110_UI.ptrOT,

		data.ptrColor[0x17][0],
		data.ptrColor[0x17][1],
		data.ptrColor[0x17][2],
		data.ptrColor[0x17][3],

		0, 0x1000
	);
	*/
}