#include <common.h>

void DECOMP_RECTMENU_GetWidth(struct RectMenu* m, short* width, int boolCheckSubmenu)
{
	int fontType;
	struct MenuRow* row;
	int lineWidth;
	
	fontType = FONT_BIG;
	
	// if menu should have tiny text
	if((m->state & 0x80) != 0)
	{
		fontType = FONT_SMALL;
	}
	
	// handle rows
	for(row = m->rows; row->stringIndex != -1; row++)
	{
		// width of string in each row
		lineWidth = DECOMP_DecalFont_GetLineWidth(
			sdata->lngStrings[row->stringIndex & 0x7fff], 
			fontType);
		
		// set new width if new max is found
		if(*width < (lineWidth + 1))
		{
			*width = lineWidth + 1;
		}
	}
	
	// handle menu title
	if(m->stringIndexTitle != -1)
	{
		// if force title to be big
		if((m->state & 0x4000) != 0)
		{
			// override
			fontType = FONT_BIG;
		}
		
		// width of string in each row
		lineWidth = DECOMP_DecalFont_GetLineWidth(
			sdata->lngStrings[m->stringIndexTitle & 0x7fff], 
			fontType);

		// set new width if new max is found
		if(*width < (lineWidth + 1))
		{
			*width = lineWidth + 1;
		}
	}
	
	// if submenu needs to be drawn
	if((m->state & 0x10) != 0)
	{
		if(boolCheckSubmenu != 0)
		{
			// recursively check height for more submenus
			DECOMP_RECTMENU_GetWidth(
				m->ptrNextBox_InHierarchy,
				width, 1);
		}
	}
}