#include <common.h>

void MENUBOX_ClearInput();

void DECOMP_MENUBOX_Show(struct MenuBox* m)
{
	sdata->ptrActiveMenuBox = m;
	
	m->state &= ~(0x1000);
	
	MENUBOX_ClearInput();
}