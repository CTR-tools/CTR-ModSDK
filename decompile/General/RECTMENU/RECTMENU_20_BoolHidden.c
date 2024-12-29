#include <common.h>

int DECOMP_RECTMENU_BoolHidden(struct RectMenu* m)
{
	return ((m->state & NEEDS_TO_CLOSE) != 0);
}