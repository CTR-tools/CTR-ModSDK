#include <common.h>

/*
easy way to fix the menu storage bug
Top half is checking for a new menu, bottom half is updating menu logic, 
just reverse the order of the function, and it's fixed
*/

void DECOMP_RECTMENU_ProcessState()
{
	struct RectMenu* currMenuBox;
	int currState;
	short width;
	int state;
	
	// check for curr box
	currMenuBox = sdata->ptrDesiredMenu;
	
	// unused
	if(sdata->framesRemainingInMenu != 0)
		sdata->framesRemainingInMenu--;
	
	// if you want to change the MenuBox
	if(currMenuBox != 0)
	{
		sdata->ptrDesiredMenu = 0;
		
		// show menubox
		sdata->ptrActiveMenu = currMenuBox;
		currMenuBox->state &= ~NEEDS_TO_CLOSE;
		
		// get menubox at end of hierarchy, if there is hierarchy
		while((currMenuBox->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
		{
			currMenuBox = (struct RectMenu*)currMenuBox->ptrNextBox_InHierarchy;
		}
		
		// remove "draw only title bar" from lowest hierarchy,
		// so that rows in this menu draw properly
		currMenuBox->state &= ~ONLY_DRAW_TITLE;
	}
	
	currMenuBox = sdata->ptrActiveMenu;
	state = currMenuBox->state;
	
	// run funcPtr if it exists
	if((state & (EXECUTE_FUNCPTR | DISABLE_INPUT_ALLOW_FUNCPTRS)) != 0)
	{
		currMenuBox->unk1e = 1;
		currMenuBox->funcPtr(currMenuBox);
		
		// check if funcPtr changed "state"
		state = currMenuBox->state;
	}
	
	// if not character selection
	if((state & DISABLE_INPUT_ALLOW_FUNCPTRS) == 0)
	{
		// process button input for menu
		DECOMP_RECTMENU_ProcessInput(currMenuBox);
		
		// check if ProcessInput changed "state"
		state = currMenuBox->state;
		
		// if MenuBox border is not invisible
		if((state & INVISIBLE) == 0)
		{
			// clear width, then get width
			width = 0;
			DECOMP_RECTMENU_GetWidth(currMenuBox, &width, 1);
			
			// draw
			DECOMP_RECTMENU_DrawSelf(currMenuBox, 0, 0, (int)width);
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
	
	// if menubox needs to close
	if((state & NEEDS_TO_CLOSE) != 0)
	{
		// deactivate
		sdata->ptrActiveMenu = 0;
	}
}