#include <common.h>
#include "menubox.h"

void heyguys(struct GameTracker* gGT)
{
	MENUBOX_DrawInnerRect(&r, 4, (u_long*)(gGT->backBuffer->otMem).startPlusFour);
}