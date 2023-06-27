#include <common.h>

void DECOMP_MainFreeze_ConfigDrawArrows(short offsetX, short offsetY, char* str)
{
	int lineWidth;
	int color;
	u_char **colorPtr;

	// orange color
	color = 0;

	if ((sdata->data18_aaa[0x14] & 4) == 0)
	{
		// red color
		color = 3;
	}

	// DecalFont_GetLineWidth
	lineWidth = DecalFont_GetLineWidth(str, 1);

	lineWidth = ((lineWidth << 0x10) >> 0x10) - ((lineWidth << 0x10) >> 0x1f) >> 1;

	// get color data
	colorPtr = (u_char **)&data.ptrColor[color];

	// Draw left arrow
	DecalHUD_Arrow2D
	(
		// largeFont
		sdata->gGT->iconGroup[4]->icons[0x38],

		(offsetX - lineWidth) - 0x14, (int)offsetY + 7,

		// pointer to PrimMem struct
		&sdata->gGT->backBuffer->primMem,

		// pointer to OT memory
		sdata->gGT->tileView_UI.ptrOT,

		// color data
		*colorPtr[0],
		*colorPtr[1],
		*colorPtr[2],
		*colorPtr[3],

		0, 0x1000, 0x800
	);

	// Draw right arrow
	DecalHUD_Arrow2D
	(
		// largeFont
		sdata->gGT->iconGroup[4]->icons[0x38],

		(offsetX + lineWidth) + 0x12 , (int)offsetY + 7,

		// pointer to PrimMem struct
		&sdata->gGT->backBuffer->primMem,

		// pointer to OT memory
		sdata->gGT->tileView_UI.ptrOT,

		// color data
		*colorPtr[0],
		*colorPtr[1],
		*colorPtr[2],
		*colorPtr[3],

		0, 0x1000, 0
	);

	return;
}