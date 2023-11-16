#include <common.h>

/*
easy way to fix the menu storage bug
Top half is checking for a new menu, bottom half is updating menu logic, 
just reverse the order of the function, and it's fixed
*/

void DECOMP_MENUBOX_ProcessState()
{
	struct MenuBox* currMenuBox;
	int currState;
	short width;
	int state;
	
	// check for curr box
	currMenuBox = sdata->ptrDesiredMenuBox;
	
	// unused
	if(sdata->framesRemainingInMenu != 0)
		sdata->framesRemainingInMenu--;
	
	// if you want to change the MenuBox
	if(currMenuBox != 0)
	{
		sdata->ptrDesiredMenuBox = 0;
		
		// show menubox
		sdata->ptrActiveMenuBox = currMenuBox;
		currMenuBox->state &= ~NEEDS_TO_CLOSE;
		
		// get menubox at end of hierarchy, if there is hierarchy
		while((currMenuBox->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
		{
			currMenuBox = (struct MenuBox*)currMenuBox->ptrNextBox_InHierarchy;
		}
		
		// remove "draw only title bar" from lowest hierarchy,
		// so that rows in this menu draw properly
		currMenuBox->state &= ~ONLY_DRAW_TITLE;
	}
	
	currMenuBox = sdata->ptrActiveMenuBox;
	state = currMenuBox->state;
	
	// run funcPtr if it exists
	if((state & (EXECUTE_FUNCPTR | DISABLE_INPUT_ALLOW_FUNCPTRS)) != 0)
	{
		currMenuBox->unk1e = 1;
		currMenuBox->funcPtr(currMenuBox);
	}
	
	// check if funcPtr changed "state"
	state = currMenuBox->state;
	
	// if not character selection
	if((state & DISABLE_INPUT_ALLOW_FUNCPTRS) == 0)
	{
		// process button input for menu
		MENUBOX_ProcessInput(currMenuBox);
		
		// if MenuBox border is not invisible
		if((state & INVISIBLE) == 0)
		{
			// clear width, then get width
			width = 0;
			DECOMP_MENUBOX_GetWidth(currMenuBox, &width, 1);
			
			// draw
			MENUBOX_DrawSelf(currMenuBox, 0, 0, (int)width);
		}
	}
	
	// not sure what this is
	if((state & 0x800) == 0)
	{
		if(DECOMP_TitleFlag_GetCanDraw() == 0)
		{
			DECOMP_TitleFlag_SetCanDraw(1);
		}
		
		sdata->gGT->renderFlags |= 0x20;
	}
	
	// if menubox needs to close
	if((state & NEEDS_TO_CLOSE) != 0)
	{
		// deactivate
		sdata->ptrActiveMenuBox = 0;
	}
}