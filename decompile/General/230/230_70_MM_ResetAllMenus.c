#include <common.h>

void DECOMP_MM_ResetAllMenus(void)
{
    for (int i = 0; i < 9; i++)
    {
        struct RectMenu* menu = D230.arrayMenuPtrs[i];

		// PC doesn't "reload" 230 cause it's all
		// in the executable. Do manual clearing
		#ifdef REBUILD_PC
		do
		{
			struct RectMenu* next = menu->ptrNextBox_InHierarchy;
		#endif
			
			// Close menu
			menu->state |= 8;
			menu->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
			
			// Reset ptrNext and ptrPrev
			menu->ptrNextBox_InHierarchy = 0;
			menu->ptrPrevBox_InHierarchy = 0;

		#ifdef REBUILD_PC			
			menu = next;
		} while(menu != 0);
		#endif
    }

	// unused
    sdata->framesRemainingInMenu = FPS_DOUBLE(0xF);
}