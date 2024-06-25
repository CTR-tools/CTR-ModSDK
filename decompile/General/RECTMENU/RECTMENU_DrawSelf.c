#include <common.h>

void DECOMP_RECTMENU_DrawSelf(struct RectMenu* menu, int posX, short posY, short menuWidth)
{
    u_short textFlags;
    u_int state;
    int index;
    char *titleString;
    short offsetX;
    short sVar4;
    u_int *rgb;
    u_short uVar5;
    struct MenuRow *row;
    short sVar6;
    short sVar7;
    u_short uVar8;
    RECT background;
    RECT borders;
    short local_60;
    short menuHeight;
    short offsetY;
    short local_50;
    short local_48;
    short local_40;
    short local_38;
    int local_30;
    int local_2c;
    short posX_prev;
    short posY_prev;
    struct GameTracker *gGT = sdata->gGT;

    uVar8 = 0;
    local_40 = 0;
    local_38 = 0;
    if ((menu->drawStyle & 0x10U) != 0)
    {
        uVar8 = 0x1d;
    }
    offsetY = posY;
    if ((menu->state & 0x60000) == 0x60000)
    {
        menu->unk1e = 2;
        if (menu->funcPtr != NULL)
        {
            menu->funcPtr(menu);
        }
    }
    posX_prev = 2;
    if ((menu->state & 0x80) == 0)
    {
        posX_prev = 1;
        local_50 = 2;
        sVar7 = data.font_charPixHeight[1] + 3;
    }
    else
    {
        local_50 = 0;
        sVar7 = data.font_charPixHeight[2];
        if ((menu->state & 0x4000) == 0)
        {
            local_48 = data.font_charPixHeight[2];
            goto LAB_80045e94;
        }
    }
    local_48 = data.font_charPixHeight[1] + 3;
LAB_80045e94:

    local_60 = 0;
    menu->posX_prev = menu->posX_curr;
    menu->posY_prev = menu->posY_curr;
    DECOMP_RECTMENU_GetHeight(menu, &local_60, 0);

    state = menu->state;

    menu->width = menuWidth;
    menu->state &= 0xfffffff7;
    menu->height = local_60;

    if ((state & 2) != 0)
    {
        menuHeight = 0;
        DECOMP_RECTMENU_GetHeight(menu, &menuHeight, 1);
        local_38 = (short)(-menuHeight/2);
    }
    if ((state & 1) != 0)
    {
        local_40 = (short)(-menuWidth/2);
    }
    sVar6 = 0;
    row = &menu->rows[0];
    index = menu->stringIndexTitle;
    posY_prev = local_50 + local_38 + offsetY + menu->posY_prev;
    if ((-1 < index) && ((state & 4) == 0))
    {
        sVar4 = 1;
        if ((state & 0x4000) == 0)
        {
            sVar4 = posX_prev;
        }
        if ((state & 0x200) == 0)
        {
            offsetX = (short)(posX + menu->posX_prev);
            uVar5 = uVar8;
            if ((state & 1) != 0)
            {
                uVar5 = uVar8 | 0x8000;
            }
            titleString = sdata->lngStrings[index];
        }
        else
        {
            uVar5 = uVar8 | 0x8000;
            titleString = sdata->lngStrings[index];
            offsetX = (short)(posX + menu->posX_prev + (menuWidth/2));
        }
        DECOMP_DecalFont_DrawLine(titleString, offsetX, posY_prev, sVar4, uVar5);
        posY_prev = local_48 + posY_prev + 6;
    }

    if (row->stringIndex != -1)
    {
        local_30 = (menuWidth/2) + 1;
        local_2c = posX_prev;
        do
        {
            state = menu->state;
            if (((state & 0x44) == 0) || (sVar6 == menu->rowSelected))
            {
                uVar5 = row->stringIndex;
                textFlags = 0x17;
                if ((uVar5 & 0x8000) == 0)
                {
                    textFlags = uVar8;
                }
                if ((uVar5 & 0x7fff) != 0)
                {
                    if ((state & 0x200) == 0)
                    {
                        sVar4 = (short)(posX + menu->posX_prev + 1);
                        if ((state & 1) != 0)
                        {
                            textFlags |= 0x8000;
                        }
                        titleString = sdata->lngStrings[uVar5 & 0x7fff];
                        index = local_2c;
                    }
                    else
                    {
                        textFlags |= 0x8000;
                        titleString = sdata->lngStrings[uVar5 & 0x7fff];
                        sVar4 = (short)(posX + menu->posX_prev + local_30);
                        index = posX_prev;
                    }
                    DECOMP_DecalFont_DrawLine(titleString, sVar4, posY_prev, index, textFlags);
                }
                posY_prev += sVar7;
            }
            row++;
            sVar6++;
        } while (row->stringIndex != -1);
    }
    if ((menu->state & 0x104) == 0)
    {
        background.x = local_40 + posX + menu->posX_prev;
        background.y = offsetY + menu->posY_prev + local_38;
        if ((menu->state & 0x40) == 0)
        {
            background.y += menu->rowSelected * sVar7 + local_50 + -1;
        }
        else
        {
            background.y += local_50 + -1;
        }
        if ((menu->state & 0x80) == 0)
        {
            background.h = -3;
        }
        else
        {
            background.h = 1;
        }
        background.h = sVar7 + background.h;
        if (-1 < menu->stringIndexTitle)
        {
            background.y += local_48 + 6;
        }
        rgb = &sdata->menuRowHighlight_Normal;
        if ((menu->drawStyle & 0x10U) != 0)
        {
            rgb = &sdata->menuRowHighlight_Green;
        }
        background.w = menuWidth;

        Color color;
        color.self = *rgb;
        DECOMP_CTR_Box_DrawClearBox(&background, color, 1, gGT->backBuffer->otMem.startPlusFour);
    }
    if ((menu->state & 0x10) != 0)
    {
        DECOMP_RECTMENU_DrawSelf(menu->ptrNextBox_InHierarchy,
                         posX + menu->posX_prev,
                         local_38 + offsetY + menu->posY_prev + sVar7 + 0xc, menuWidth);
    }
    posX_prev = menu->posX_prev;
    posY_prev = menu->posY_prev;
    if ((menu->state & 4) == 0)
    {
        borders.h = (local_60 + 8) - (*(unsigned char *)&menu->state >> 7);
    }
    else
    {
        borders.h = sVar7 + 8;
    }
    borders.w = menuWidth + 0xc;
    borders.y = local_38 + offsetY + posY_prev - 4;
    borders.x = local_40 + posX + posX_prev - 6;
    DECOMP_RECTMENU_DrawFullRect(menu, &borders);
}
