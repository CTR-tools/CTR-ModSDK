#include <common.h>

void DECOMP_MainFreeze_ConfigDrawArrows(short offsetX, short offsetY, char* str)
{
	int lineWidth;
	int color;
	u_char **colorPtr;
	struct GameTracker* gGT = sdata->gGT;

	// orange color
	color = 0;

	if ((FPS_HALF(sdata->frameCounter) & 4) == 0)
	{
		// red color
		color = 3;
	}

	lineWidth = DECOMP_DecalFont_GetLineWidth(str, 1) >> 1;

	// get color data
	colorPtr = (u_char **)&data.ptrColor[color];

	struct Icon** iconPtrArray =
		ICONGROUP_GETICONS(gGT->iconGroup[4]);

	// Draw left arrow
	DecalHUD_Arrow2D
	(
		// largeFont
		iconPtrArray[0x38],

		(offsetX - lineWidth) - 0x14, (int)offsetY + 7,

		// pointer to PrimMem struct
		&gGT->backBuffer->primMem,

		// pointer to OT memory
		gGT->pushBuffer_UI.ptrOT,

		// color data
		*colorPtr[0],
		*colorPtr[1],
		*colorPtr[2],
		*colorPtr[3],

		0, FP(1.0), 0x800
	);

	// Draw right arrow
	DecalHUD_Arrow2D
	(
		// largeFont
		iconPtrArray[0x38],

		(offsetX + lineWidth) + 0x12 , (int)offsetY + 7,

		// pointer to PrimMem struct
		&gGT->backBuffer->primMem,

		// pointer to OT memory
		gGT->pushBuffer_UI.ptrOT,

		// color data
		*colorPtr[0],
		*colorPtr[1],
		*colorPtr[2],
		*colorPtr[3],

		0, FP(1.0), 0
	);

	return;
}