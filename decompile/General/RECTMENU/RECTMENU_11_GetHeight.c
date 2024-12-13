#include <common.h>

void DECOMP_RECTMENU_GetHeight(struct RectMenu* m, short* height, int boolCheckSubmenu)
{
	int lineHeight;
	struct MenuRow* row;
	
	// heighth of small line
	lineHeight = data.font_charPixHeight[FONT_SMALL];
	
	// if small text disabled
	if((m->state & USE_SMALL_FONT) == 0)
	{
		// height of big line
		lineHeight = data.font_charPixHeight[FONT_BIG] + 3;
	}
	
	// if not showing only highlighted row
	if((m->state & SHOW_ONLY_HIGHLIT_ROW) == 0)
	{
		// if not only drawing title bar
		if((m->state & ONLY_DRAW_TITLE) == 0)
		{
			// add rows
			for(row = m->rows; row->stringIndex != -1; row++)
			{
				*height += lineHeight;
			}
		}
		
		// only drawing title bar
		else
		{
			*height += lineHeight - 6;
		}
	}
	
	// only showing row highlighted
	else
	{
		*height += lineHeight;
	}
	
	// handle menu title
	if(m->stringIndexTitle != -1)
	{
		// if not drawing title big
		if((m->state & BIG_TEXT_IN_TITLE) == 0)
		{
			*height += lineHeight + 6;
		}
		
		// if drawing title big,
		// this overrides title to big, even if rest of menu is small
		else
		{
			*height += data.font_charPixHeight[FONT_BIG] + 9;
		}
	}
	
	// if submenu needs to be drawn
	if((m->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
	{
		if(boolCheckSubmenu != 0)
		{
			// recursively check height for more submenus
			DECOMP_RECTMENU_GetHeight(
				m->ptrNextBox_InHierarchy,
				height, 1);
		}
	}
}