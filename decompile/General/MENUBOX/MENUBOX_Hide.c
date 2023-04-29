#include <common.h>

void DECOMP_MENUBOX_Hide(struct MenuBox* m)
{
	m->state |= 0x1000;
}