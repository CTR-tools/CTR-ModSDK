#include <common.h>

int DECOMP_RECTMENU_ProcessInput(struct RectMenu *m)
{
	struct MenuRow *currMenuRow;
	int i;
	int button;
	int oldRow;
	int newRow;

	int returnVal = 0;

#if 0
	// do we need this?
	RngDeadCoed();
#endif

	if
	(
		// if not drawing only title bar,
		// therefore this is the bottom of hierarchy
		((m->state & ONLY_DRAW_TITLE) == 0) &&

		// must be both 0x20000 and 0x40000
		((m->state & 0x60000) != 0x60000)
	)
	{
		oldRow = m->rowSelected;
		newRow = oldRow;

		currMenuRow = &m->rows[oldRow];

		if (sdata->activeSubMenu != m)
		{
			sdata->activeSubMenu = m;

			// if input should clear upon opening
			if ((m->state & KEEP_INPUTS_IN_SUBMENU) == 0)
			{
				DECOMP_RECTMENU_ClearInput();
			}
		}

		// button from any player
		button = sdata->AnyPlayerTap;

		// if only P1 can use menu
		if ((m->state & ALL_PLAYERS_USE_MENU) == 0)
		{
			// get button from P1
			button = sdata->buttonTapPerPlayer[0];
		}

		// if P1 is not holding L1 or R1
		if ((sdata->buttonHeldPerPlayer[0] & (BTN_L1 | BTN_R1)) != 0)
			goto AfterButtons;

		// If nobody pressed D-Pad, Cross, Square, Triangle, Circle
		if ((button & 0x4007f) == 0)
			goto AfterButtons;

		// optimized way to check all four button presses:
		// up, down, left, right, and get new row
		for (i = 0; i < 4; i++)
		{
			if (((button >> i) & 1) != 0)
			{
				newRow = *(char *)((char *)&currMenuRow->rowOnPressUp + i);
				break;
			}
		}

		// check if row has changed
		if (oldRow != newRow)
		{
			// if cursor moving sound is not muted
			if ((m->state & MUTE_SOUND_OF_MOVING_CURSOR) == 0)
			{
				DECOMP_OtherFX_Play(0, 1);
			}
		}

		if ((button & (BTN_CROSS | BTN_CIRCLE)) == 0)
		{
			if
			(
				// if Triangle or Square
				((button & (BTN_TRIANGLE | BTN_SQUARE)) != 0) &&

				// if this is not the top of the menu
				((m->state & MENU_CANT_GO_BACK) == 0)
			)
			{
				// process GO BACK

				// if menu is not muted
				if ((m->state & MUTE_SOUND_OF_MOVING_CURSOR) == 0)
				{
					DECOMP_OtherFX_Play(2, 1);
				}

				returnVal = -1;

				m->unk1e = 0;
				
				m->rowSelected = -1;

				if (m->funcPtr != 0)
				{
					DECOMP_RECTMENU_ClearInput();
					m->funcPtr(m);
				}

				// useless? cause set later?
				m->rowSelected = newRow;
			}
		}

		// if Cross or Circle
		else
		{
			// if row is locked
			if ((m->rows[m->rowSelected].stringIndex & 0x8000) != 0)
			{
				// if menu is not muted
				if ((m->state & MUTE_SOUND_OF_MOVING_CURSOR) == 0)
				{
					// "womp" sound
					DECOMP_OtherFX_Play(5, 1);
				}
			}

			// unlocked row
			else
			{
				// if menu is not muted
				if ((m->state & MUTE_SOUND_OF_MOVING_CURSOR) == 0)
				{
					// enter sound
					DECOMP_OtherFX_Play(1, 1);
				}

				m->unk1e = 0;

				// useless? cause set later?
				m->rowSelected = newRow;

				returnVal = 1;

				if (m->funcPtr != 0)
				{
					DECOMP_RECTMENU_ClearInput();
					m->funcPtr(m);
				}
			}
		}

		DECOMP_RECTMENU_ClearInput();

AfterButtons:
		// this is why you can bug character select
		// by pressing Down and X at the same time,
		// cause the row isn't set until after X is processed
		m->rowSelected = newRow;
	}

	// if "next" hierarchy level exists
	if ((m->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
	{
		// store self in the next
		m->ptrNextBox_InHierarchy->ptrPrevBox_InHierarchy = m;

		// keep going till the bottom hierarchy level is hit,
		// where m->state&4==0, cause not drawing "only title"
		returnVal = DECOMP_RECTMENU_ProcessInput(m->ptrNextBox_InHierarchy);
	}

	return returnVal;
}