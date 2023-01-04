#include <common.h>

void DECOMP_MENUBOX_GetHeight(struct MenuBox* m, short* height, int boolCheckSubmenu)
{
	int lineHeight;
	struct MenuRow* row;
	
	// heighth of small line
	lineHeight = data.font_charPixHeight[FONT_SMALL];
	
	// if small text disabled
	if((m->state & 0x80) == 0)
	{
		// height of big line
		lineHeight = data.font_charPixHeight[FONT_BIG] + 3;
	}
	
	// if not showing only highlighted row
	if((m->state & 0x40) == 0)
	{
		// if not only drawing title bar
		if((m->state & 4) == 0)
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
		if((m->state & 0x4000) == 0)
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
	if((m->state & 0x10) != 0)
	{
		if(boolCheckSubmenu != 0)
		{
			// recursively check height for more submenus
			DECOMP_MENUBOX_GetHeight(
				m->ptrNextMenuBox_InHierarchy,
				height, 1);
		}
	}
	
}