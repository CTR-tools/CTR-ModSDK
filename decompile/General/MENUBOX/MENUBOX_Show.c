#include <common.h>

void DECOMP_MENUBOX_Show(struct MenuBox* m)
{
	sdata->ptrActiveMenuBox = m;
	
	m->state &= ~NEEDS_TO_CLOSE;
	
	MENUBOX_ClearInput();
}