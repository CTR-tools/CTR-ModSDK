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
		currMenuBox->state &= ~(0x1000);
		
		// get menubox at end of hierarchy, if there is hierarchy
		while((currMenuBox->state & 0x10) != 0)
		{
			currMenuBox = (struct MenuBox*)currMenuBox->ptrNextBox_InHierarchy;
		}
		
		// remove "draw only title bar" from lowest hierarchy,
		// so that rows in this menu draw properly
		currMenuBox->state &= ~(0x4);
	}
	
	currMenuBox = sdata->ptrActiveMenuBox;
	
	// run funcPtr if it exists
	if((currMenuBox->state & 0x420) != 0)
	{
		currMenuBox->unk1e = 1;
		currMenuBox->funcPtr(currMenuBox);
	}
	
	// if not character selection
	if((currMenuBox->state & 0x20) == 0)
	{
		// process button input for menu
		MENUBOX_ProcessInput(currMenuBox);
		
		// if MenuBox border is not invisible
		if((currMenuBox->state & 0x2000) == 0)
		{
			// clear width, then get width
			width = 0;
			MENUBOX_GetWidth(currMenuBox, &width, 1);
			
			// draw
			MENUBOX_DrawSelf(currMenuBox, 0, 0, (int)width);
		}
	}
	
	// not sure what this is
	if((currMenuBox->state & 0x800) == 0)
	{
		if(TitleFlag_GetCanDraw() == 0)
		{
			TitleFlag_SetCanDraw(1);
		}
		
		sdata->gGT->renderFlags |= 0x20;
	}
	
	// if menubox needs to close
	if((currMenuBox->state & 0x1000) != 0)
	{
		// deactivate
		sdata->ptrActiveMenuBox = 0;
	}
}