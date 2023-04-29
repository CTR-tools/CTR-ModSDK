#include <common.h>

void MenuBox_ClearInput();

void DECOMP_MENUBOX_Show(struct MenuBox* m)
{
	sdata->ptrActiveMenuBox = m;
	
	m->state &= ~(0x1000);
	
	MenuBox_ClearInput();
}