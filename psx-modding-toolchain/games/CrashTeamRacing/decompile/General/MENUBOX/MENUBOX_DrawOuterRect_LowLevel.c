#include <common.h>

void DECOMP_MenuBox_DrawOuterRect_LowLevel(RECT* p, short xOffset, u_short yOffset, u_int* rgb, short param_5, u_long* otMem)
{
	int iVar1;
	RECT r;

	r.x = p->x;
	iVar1 = (int)param_5;
	r.y = p->y;
	r.w = p->w;
	r.h = yOffset;

	MenuBox_DrawOuterRect_Edge(&r, rgb, iVar1, otMem);

	r.y += (p->h - yOffset);

	MenuBox_DrawOuterRect_Edge(&r, rgb, iVar1, otMem);

	r.y = p->y + yOffset;
	r.h = p->h - (short)((int)((u_int)yOffset << 0x10) >> 0xf);
	r.w = xOffset;

	MenuBox_DrawOuterRect_Edge(&r, rgb, iVar1, otMem);

	r.x += (p->w - xOffset);

	MenuBox_DrawOuterRect_Edge(&r, rgb, iVar1, otMem);
	return;
}