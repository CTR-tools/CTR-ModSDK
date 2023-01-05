#include <common.h>

int DECOMP_MENUBOX_ProcessInput(struct MenuBox* m)
{
	struct MenuRow* currMenuRow;
	int button;
	int oldRow;
	int newRow;
	int i;
	
	int returnVal;

	returnVal = 0;

	#if 0
	// do we need this?
	FUN_8006c684();
	#endif
	
	if(
		// if not drawing only title bar,
		// therefore this is the bottom of hierarchy
		((m->state & 4) == 0) &&
		
		// must be both 0x20000 and 0x40000
		((m->state & 0x60000) != 0x60000)
	  )
	{
	  oldRow = m->rowSelected;
	  
	  currMenuRow = m->rows[oldRow];
	  
	  if(sdata->activeSubMenu != m)
	  {
	    activeSubMenu = m;
	    
	    // if input should clear upon opening
	    if(m->state & 0x10000)
	    {
	  	  MenuBox_ClearInput();
	    }
	  }
	  
	  // button from any player
	  button = sdata->AnyPlayerTap;
	  
	  // if only P1 can use menu
	  if ((*(uint *)(param_1 + 8) & 0x8000) == 0) 
	  {
	    // get button from P1
	    button = sdata->buttonTapPerPlayer[0];
	  }
	  
	  // if P1 is not holding L1 or R1
	  if((sdata->buttonHeldPerPlayer[0] & 0xc00) != 0) goto AfterButtons;
	  
	  // If nobody pressed D-Pad, Cross, Square, Triangle, Circle
	  if ((button & 0x4007f) == 0) goto AfterButtons;
	  
	  // optimized way to check all four button presses:
	  // up, down, left, right, and get new row
	  for(i = 0; i < 4; i++)
	  {
		if(((button>>i) & 1) != 0) 
		{
			newRow = *(char*)((char*)&currMenuRow->rowOnPressUp + i);
			break;
		}
	  }
	  
	  // check if row has changed
	  if(oldRow != newRow)
	  {
	    // if cursor moving sound is not muted
	    if((m->state & 0x800000) == 0)
	    {
	  	  OtherFX_Play(0,1);
	    }
	  }
	  
	  // if not Cross or Circle
	  if((button & 0x50) == 0)
	  {
		if(
			// if Triangle or Square
			((button & 0x40020) != 0) &&

			// if this is not the top of the menu
			((m->state & 0x100000) == 0)
		  )
		{
			// process GO BACK

			// if menu is not muted
			if ((m->state & 0x800000) == 0)
			{
				OtherFX_Play(2, 1);
			}

			returnVal = -1;

			// bool showRows?
			m->unk6 = 0;
			m->rowSelected = -1;

			if (m->funcPtr != 0)
			{
				MenuBox_ClearInput();
				m->funcPtr(m);
			}

			// useless? cause set later?
			m->selectedRow = newRow;

		}
	  }
	  
	  // if Cross or Circle
	  else
	  {
		// if row is locked
		if((m->rows[m->rowSelected] & 0x8000) != 0)
		{
			// if menu is not muted
			if ((m->state & 0x800000) == 0)
			{
				// "womp" sound
				OtherFX_Play(5, 1);
			}
		}

		// unlocked row
		else
		{
			// if menu is not muted
			if ((m->state & 0x800000) == 0)
			{
				// enter sound
				OtherFX_Play(1, 1);
			}

			// bool showRows?
			m->unk6 = 0;

			// useless? cause set later?
			m->selectedRow = newRow;

			returnVal = 1;

			if (m->funcPtr != 0)
			{
				MenuBox_ClearInput();
				m->funcPtr(m);
			}
		}
	  }
	  
	  MenuBox_ClearInput();
	  
	  // this is why you can bug character select
	  // by pressing Down and X at the same time,
	  // cause the row isn't set until after X is processed
	  m->selectedRow = newRow;
	  
	}
	
	// if "next" hierarchy level exists
	if((m->state & 0x10) != 0)
	{
		// store self in the next
		m->ptrNextMenuBox_InHierarchy->ptrPrevMenuBox_InHierarchy = m;
		
		// keep going till the bottom hierarchy level is hit,
		// where m->state&4==0, cause not drawing "only title"
		returnVal = DECOMP_MENUBOX_ProcessInput(m->ptrNextMenuBox_InHierarchy);
	}

	return returnVal;
}