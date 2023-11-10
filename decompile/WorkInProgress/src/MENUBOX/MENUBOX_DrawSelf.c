#include <common.h>

void DECOMP_MENUBOX_DrawSelf(struct MenuBox* mb, int param_2, short param_3, u_short width)
{
    struct GameTracker* gGT = sdata->gGT;
    u_short textColor = 0;
    short rowHeight = data.font_charPixHeight[FONT_SMALL];
    short titleRowHeight = data.font_charPixHeight[FONT_BIG] + 3;
    short posX_prev = mb->posX_curr;
    short posY_prev = mb->posY_curr;

    if ((mb[10] & 0x10U) != 0)
        textColor = 0x1d;

    if ((mb->state & 0x60000) == 0x60000)
    {
        mb[0xf] = 2;
        if (mb->funcPtr != NULL)
            mb->funcPtr(mb);
    }

    if ((mb->state & USE_SMALL_FONT) == 0)
    {
        rowHeight = data.font_charPixHeight[FONT_BIG] + 3;
    }

    int menuBoxHeight = 0;
    MENUBOX_GetHeight(mb, &menuBoxHeight, 0);

    mb->width = width;
    mb->height = menuBoxHeight;
    mb->state &= 0xfffffff7;

    if ((mb->state & CENTER_ON_Y) != 0)
    {
        short tmpHeight = 0;
        MENUBOX_GetHeight(mb, &tmpHeight, 1);
        short centerOffset = -(tmpHeight >> 1);
        rowHeight += centerOffset;
    }

    short yOffset = param_3 + rowHeight + posY_prev;
    short sVar12 = 0;
    short titleIndex = mb->stringIndexTitle;

    if (titleIndex >= 0 && (mb->state & 4) == 0)
    {
        short titleHeight = (mb->state & BIG_TEXT_IN_TITLE) ? titleRowHeight : rowHeight;
        int titleX = param_2 + posX_prev;

        if (mb->state & 0x200)
        {
            titleX += (width - (width >> 0xf) >> 1);
            textColor |= 0xffff8000;
        }

        DecalFont_DrawLine(sdata->lngStrings[titleIndex], titleX, yOffset, titleHeight, textColor);
        yOffset += titleRowHeight + 6;
    }

    struct MenuRow* row = mb->rows[0];
    if (row->stringIndex != -1)
    {
        int rowX = (width - (width >> 0xf) >> 1) + 1;

        do
        {
            if ((mb->state & (SHOW_ONLY_HIGHLIT_ROW | ONLY_DRAW_TITLE)) == 0 || sVar12 == mb->rowSelected)
            {
                u_short stringIndex = row->stringIndex;
                u_short textColor = (stringIndex & 0x8000) ? 0x17 : 0;
                if (stringIndex & 0x7fff)
                {
                    if (mb->state & CENTER_ON_X)
                        textColor |= 0x8000;

                    DecalFont_DrawLine(sdata->lngStrings[stringIndex], param_2 + posX_prev + 1, yOffset, rowHeight, textColor);
                }
                yOffset += rowHeight;
            }

            sVar12++;
        } while (row++->stringIndex != -1);
    }

    if ((mb->state & 0x104) == 0)
    {
        short rectX = param_2 + posX_prev + local_40;
        short rectY = param_3 + posY_prev + local_38 + local_58 + rowHeight - 1;

        if ((mb->state & SHOW_ONLY_HIGHLIT_ROW) == 0)
            rectY += mb->rowSelected * rowHeight + local_50;

        u_short* highlightColor = &sdata->menuRowHighlight_Normal;
        if (mb[10] & 0x10U)
            highlightColor = &sdata->menuRowHighlight_Green;

        CTR_Box_DrawClearBox(&rectX, highlightColor, TRANS_50_DECAL, gGT->backBuffer->otMem.startPlusFour, &gGT->backBuffer->primMem);
    }

    if (mb->state & DRAW_NEXT_MENU_IN_HIERARCHY)
    {
        MENUBOX_DrawSelf(mb->ptrNextBox_InHierarchy, param_2 + posX_prev, param_3 + local_38 + local_58 + rowHeight + 0xc, width);
    }

    if ((mb->state & ONLY_DRAW_TITLE) == 0)
    {
        posX_prev = mb->posX_prev;
        posY_prev = mb->posY_prev;
        rowHeight = (menuBoxHeight + 8) - (u_short)(*(byte*)(mb + 4) >> 7);
    }
    else
    {
        posX_prev = mb->posX_prev;
        posY_prev = mb->posY_prev;
        rowHeight += 8;
    }

    short rectWidth = width + 0xc;
    short rectHeight = local_38 + local_58 + posY_prev - 4;
    short rectX = param_2 + posX_prev - 6;
    MENUBOX_DrawFullRect(mb, &rectX);
}
