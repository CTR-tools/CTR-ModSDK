#include <common.h>

/*
easy way to fix the menu storage bug
Top half is checking for a new menu, bottom half is updating menu logic, 
just reverse the order of the function, and it's fixed
*/

void DECOMP_RECTMENU_ProcessState()
{
	struct RectMenu* currMenu;
	int currState;
	short width;
	int state;
	
	// check for curr box
	currMenu = sdata->ptrDesiredMenu;
	
	// unused
	if(sdata->framesRemainingInMenu != 0)
		sdata->framesRemainingInMenu--;
	
	// if you want to change the Menu
	if(currMenu != 0)
	{
		sdata->ptrDesiredMenu = 0;
		
		// show menu
		sdata->ptrActiveMenu = currMenu;
		currMenu->state &= ~NEEDS_TO_CLOSE;
		
		// get menu at end of hierarchy, if there is hierarchy
		while((currMenu->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
		{
			currMenu = (struct RectMenu*)currMenu->ptrNextBox_InHierarchy;
		}
		
		// remove "draw only title bar" from lowest hierarchy,
		// so that rows in this menu draw properly
		currMenu->state &= ~ONLY_DRAW_TITLE;
	}
	
	currMenu = sdata->ptrActiveMenu;
	state = currMenu->state;
	
	// run funcPtr if it exists
	if((state & (EXECUTE_FUNCPTR | DISABLE_INPUT_ALLOW_FUNCPTRS)) != 0)
	{
		currMenu->unk1e = 1;
		currMenu->funcPtr(currMenu);
		
		// check if funcPtr changed "state"
		state = currMenu->state;
	}
	
	// if not character selection
	if((state & DISABLE_INPUT_ALLOW_FUNCPTRS) == 0)
	{
		// process button input for menu
		DECOMP_RECTMENU_ProcessInput(currMenu);
		
		// check if ProcessInput changed "state"
		state = currMenu->state;
		
		// if Menu border is not invisible
		if((state & INVISIBLE) == 0)
		{
			// clear width, then get width
			width = 0;
			DECOMP_RECTMENU_GetWidth(currMenu, &width, 1);
			
			// draw
			DECOMP_RECTMENU_DrawSelf(currMenu, 0, 0, (int)width);
		}
	}
	
	// not sure what this is
	if((state & 0x800) == 0)
	{
		if(DECOMP_RaceFlag_GetCanDraw() == 0)
		{
			DECOMP_RaceFlag_SetCanDraw(1);
		}
		
		sdata->gGT->renderFlags |= 0x20;
	}
	
	// if menu needs to close
	if((state & NEEDS_TO_CLOSE) != 0)
	{
		// deactivate
		sdata->ptrActiveMenu = 0;
	}
}