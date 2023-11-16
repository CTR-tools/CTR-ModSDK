#include <common.h>

void DECOMP_MENUBOX_DrawSelf(struct MenuBox* mb, int param_2, short param_3, u_short width)
{
    u_short textColor = 0;
	int font = FONT_SMALL;
    struct GameTracker* gGT = sdata->gGT;
    short rowHeight = data.font_charPixHeight[FONT_SMALL];
    short titleRowHeight = data.font_charPixHeight[FONT_BIG] + 3;
    short posX_prev = mb->posX_curr;
    short posY_prev = mb->posY_curr;
	RECT r;

    if ((mb->drawStyle & 0x10U) != 0)
        textColor = LIGHT_GREEN;

    if ((mb->state & 0x60000) == 0x60000)
    {
        mb->unk1e = 2;
        if (mb->funcPtr != NULL)
            mb->funcPtr(mb);
    }

#if 0
    if ((mb->state & USE_SMALL_FONT) == 0)
    {
		font = FONT_BIG;
        rowHeight = data.font_charPixHeight[FONT_BIG] + 3;
    }
	
    int menuBoxHeight = 0;
    DECOMP_MENUBOX_GetHeight(mb, &menuBoxHeight, 0);

    mb->width = width;
    mb->height = menuBoxHeight;
    mb->state &= ~8;

    if ((mb->state & CENTER_ON_Y) != 0)
    {
        short tmpHeight = 0;
        DECOMP_MENUBOX_GetHeight(mb, &tmpHeight, 1);
        short centerOffset = -(tmpHeight >> 1);
        rowHeight += centerOffset;
    }

    short yOffset = param_3 + rowHeight + posY_prev;
    short sVar12 = 0;
    short titleIndex = mb->stringIndexTitle;

    if ((titleIndex >= 0) && ((mb->state & ONLY_DRAW_TITLE) == 0))
    {
        short titleHeight = ((mb->state & BIG_TEXT_IN_TITLE)!=0) ? 1 : 2;
        int titleX = param_2 + posX_prev;

        if ((mb->state & 0x200) != 0)
        {
            titleX += width>>1;
            textColor |= JUSTIFY_CENTER;
        }

        DecalFont_DrawLine(sdata->lngStrings[titleIndex], titleX, yOffset, titleHeight, textColor);
        yOffset += titleRowHeight + 6;
    }

    struct MenuRow* row = &mb->rows[0];
    if (row->stringIndex != -1)
    {
        int rowX = (width >> 1) + 1;

        do
        {
            if (
				(((mb->state & (SHOW_ONLY_HIGHLIT_ROW | ONLY_DRAW_TITLE))) == 0) || 
				(sVar12 == mb->rowSelected)
				)
            {
                u_short stringIndex = row->stringIndex;
                u_short textColor = ((stringIndex & 0x8000) != 0) ? GRAY : ORANGE;

                if ((mb->state & CENTER_ON_X) != 0)
                    textColor |= JUSTIFY_CENTER;

                DecalFont_DrawLine(
					sdata->lngStrings[stringIndex & 0x7fff], 
					param_2 + posX_prev + 1, yOffset, font, textColor);
					

                yOffset += rowHeight;
            }
			
            sVar12++;
			row++;
        } while (row->stringIndex != -1);
    }

    if ((mb->state & 0x104) == 0)
    {
        r.x = param_2 + posX_prev;// + local_40;
        r.y = param_3 + posY_prev + rowHeight - 1;
		r.w = width;

        if ((mb->state & SHOW_ONLY_HIGHLIT_ROW) == 0)
            r.h += mb->rowSelected * rowHeight;// + local_50;

        u_short* highlightColor = &sdata->menuRowHighlight_Normal;
        if ((mb->drawStyle & 0x10) != 0)
            highlightColor = &sdata->menuRowHighlight_Green;

        CTR_Box_DrawClearBox(&r, highlightColor, TRANS_50_DECAL, gGT->backBuffer->otMem.startPlusFour, &gGT->backBuffer->primMem);
    }

    if ((mb->state & DRAW_NEXT_MENU_IN_HIERARCHY) != 0)
    {
        DECOMP_MENUBOX_DrawSelf(mb->ptrNextBox_InHierarchy, param_2 + posX_prev, param_3 + rowHeight + 0xc, width);
    }

    if ((mb->state & ONLY_DRAW_TITLE) == 0)
    {
        posX_prev = mb->posX_prev;
        posY_prev = mb->posY_prev;
        rowHeight = (menuBoxHeight + 8) - (u_short)((unsigned char)(mb->state >> 7));
    }
    else
    {
        posX_prev = mb->posX_prev;
        posY_prev = mb->posY_prev;
        rowHeight += 8;
    }

	r.h = rowHeight;
    r.w = width + 0xc;
    r.y = posY_prev - 4;
    r.x = param_2 + posX_prev - 6;
    MENUBOX_DrawFullRect(mb, &r);
#endif
}
