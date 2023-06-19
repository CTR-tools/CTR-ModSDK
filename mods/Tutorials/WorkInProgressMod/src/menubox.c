#include <common.h>

extern RECT r;

void heyguys(struct GameTracker* gGT)
{
	MainFreeze_SafeAdvDestroy();
	*(u_short *)&gGT->frontBuffer &= 0xFEFF;
	gGT->db[0].drawEnv.clip.y = 0;
	MENUBOX_DrawInnerRect(&r, 4, (u_long*)(gGT->backBuffer->otMem).startPlusFour);
}