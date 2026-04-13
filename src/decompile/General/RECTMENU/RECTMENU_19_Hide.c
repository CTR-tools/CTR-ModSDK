#include <common.h>

void DECOMP_RECTMENU_Hide(struct RectMenu* m)
{
	m->state |= 0x1000;
}