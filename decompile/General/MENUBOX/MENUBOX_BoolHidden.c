#include <common.h>

int DECOMP_MENUBOX_BoolHidden(struct MenuBox* m)
{
	return ((m->state & NEEDS_TO_CLOSE) != 0);
}