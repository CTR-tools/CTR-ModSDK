#include <common.h>

void UI_Map_DrawMap_ExtraFunc(struct Icon* icon, POLY_FT4* p, short posX, short empty, struct PrimMem* primMem, u_long* otMem, u_int colorID);

void DECOMP_UI_Map_DrawMap(struct Icon* mapTop, struct Icon* mapBottom, short posX, short posY, struct PrimMem* primMem, u_long* otMem, u_int colorID)
{
	short mapBottomHeight;
	short mapTopHeight;
	int iVar9;
	POLY_FT4* p;
	u_int color;
	struct GameTracker* gGT;

	gGT = sdata->gGT;

	iVar9 = 0;

	// draw minimap with neutral/none vertex color, minimap's regular color is white
	color = 0x808080;

	// draw map black
	// used for the minimap shadow in the track select screen
	if (colorID == 2)
	{
		color = 0;
	}

	// draw minimap blue
	// used for the minimap outline in the track select screen
	if (colorID == 3)
	{
		color = 0x402000;
	}

	if (gGT->level1->ptrSpawnType1 != 0)
	{
		void** pointers = ST1_GETPOINTERS(gGT->level1->ptrSpawnType1);
		iVar9 = pointers[ST1_MAP];
	}

	// position of the bottom margin of the primitive for the bottom half of the minimap
	mapBottomHeight = mapBottom->texLayout.v2 - mapBottom->texLayout.v0;

	// if these conditions are met, then draw the top half of the minimap; otherwise, only draw the bottom half
	// not sure when the game ever draws only the bottom half
	if
	(
		((iVar9 != 0) && (*(short *)(iVar9 + 0x12) == 0)) ||

		// if in main menu (character selection, track selection, any part of it)
		((gGT->gameMode1 & MAIN_MENU) != 0)
	)
	{
		// draw top half of minimap
		p = (POLY_FT4*)primMem->curr;

		// r0, g0, b0 (vertex color)
		*(int*)&p->r0 = color;

		// position of the top margin of the primitive for the top half of the minimap
		mapTopHeight = posY - (((u_short)mapTop->texLayout.v2 - (u_short)mapTop->texLayout.v0) + mapBottomHeight);

		p->y0 = mapTopHeight;
		p->y1 = mapTopHeight;
		p->y2 = posY - mapBottomHeight;
		p->y3 = posY - mapBottomHeight;

		UI_Map_DrawMap_ExtraFunc(mapTop, p, posX, 0, primMem, otMem, colorID);
	}

	// draw bottom half of minimap
	p = (POLY_FT4*)primMem->curr;

	// r0, g0, b0 (vertex color)
	*(int*)&p->r0 = color;

	p->y0 = posY - mapBottomHeight;
	p->y1 = posY - mapBottomHeight;
	p->y2 = posY;
	p->y3 = posY;

	UI_Map_DrawMap_ExtraFunc(mapBottom, p, posX, 0, primMem, otMem, colorID);

	return;
}

// function that calculates and sets the width of both minimap primitives and alters texpage on a certain condition
// doesn't exist in ghidra disassembly, created from UI_Map_DrawMap for optimization
void UI_Map_DrawMap_ExtraFunc(struct Icon* icon, POLY_FT4* p, short posX, short empty, struct PrimMem* primMem, u_long* otMem, u_int colorID)
{
	short leftX;

	// width of the primitive
	// leftX is the left margin of the primitive, posX is the right
	leftX = posX - (short)(icon->texLayout.u1 - icon->texLayout.u0);
	p->x0 = leftX;
	p->x1 = posX;
	p->x2 = leftX;
	p->x3 = posX;

	// set header
	setPolyFT4(p);

	// UVs
	*(int*)&p->u0 = *(int*)&icon->texLayout.u0;
	*(int*)&p->u1 = *(int*)&icon->texLayout.u1;
	*(int*)&p->u2 = *(int*)&icon->texLayout.u2;
	*(short*)&p->u3 = *(short*)&icon->texLayout.u3;

	// check for if the minimap being drawn is white, if it's white then alter the blending mode bits of the texpage from 11 to 01
	if (colorID == 1)
	{
		p->tpage = p->tpage & 0xff9f | (u_short)(1 << 5);
	}

	p->code |= 2;

	AddPrim(otMem, p);

	// POLY_FT4 is 0x28 bytes large
	primMem->curr = p + 1;
}