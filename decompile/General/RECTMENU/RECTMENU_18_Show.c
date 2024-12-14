#include <common.h>

void DECOMP_RECTMENU_Show(struct RectMenu* m)
{
	sdata->ptrActiveMenu = m;
	
	m->state &= ~NEEDS_TO_CLOSE;
	
	DECOMP_RECTMENU_ClearInput();
}