#include <common.h>

int DECOMP_MENUBOX_BoolHidden(struct MenuBox* m)
{
	return ((m->state & 0x1000) != 0);
}