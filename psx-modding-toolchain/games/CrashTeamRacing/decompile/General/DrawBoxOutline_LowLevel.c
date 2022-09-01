#include <common.h>

void DrawRectangle(RECT* r, u_int rgb, u_int param_3, u_long* otMem);

void DECOMP_DrawBoxOutline_LowLevel(RECT* p, short xOffset, u_short yOffset, u_int rgb, short param_5, u_long* otMem)
{
	int iVar1;
	RECT r;

	r.x = p->x;
	iVar1 = (int)param_5;
	r.y = p->y;
	r.w = p->w;
	r.h = yOffset;

	DrawRectangle(&r, rgb, iVar1, otMem);

	r.y += (p->h - yOffset);

	DrawRectangle(&r, rgb, iVar1, otMem);

	r.y = p->y + yOffset;
	r.h = p->h - (short)((int)((u_int)yOffset << 0x10) >> 0xf);
	r.w = xOffset;

	DrawRectangle(&r, rgb, iVar1, otMem);

	r.x += (p->w - xOffset);

	DrawRectangle(&r, rgb, iVar1, otMem);
	return;
}