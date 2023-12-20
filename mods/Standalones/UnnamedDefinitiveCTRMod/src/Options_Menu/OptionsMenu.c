#include <common.h>

void UDCTRM_OM_FuncPtr(struct MenuBox* mb)
{
	short row = mb->rowSelected;

	// if uninitialized
	if (row == -1)
	{
		mb->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
		return;
	}

	// if you are on a valid row
	if (row < 2)
	{
		if (row == 0)
			D230.desiredMenu = 0x2a;
		if (row == 1)
			D230.desiredMenu = 0x45;

		D230.MM_State = EXITING_MENU;
		mb->state |= ONLY_DRAW_TITLE;
	}
}