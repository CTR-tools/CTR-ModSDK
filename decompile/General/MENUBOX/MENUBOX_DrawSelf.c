#include <common.h>

void DECOMP_MENUBOX_DrawSelf(struct MenuBox *mb, int posX, short posY, short menuboxWidth)
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
    short menuboxHeight;
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
    if ((mb->drawStyle & 0x10U) != 0)
    {
        uVar8 = 0x1d;
    }
    offsetY = posY;
    if ((mb->state & 0x60000) == 0x60000)
    {
        mb->unk1e = 2;
        if (mb->funcPtr != NULL)
        {
            mb->funcPtr(mb);
        }
    }
    posX_prev = 2;
    if ((mb->state & 0x80) == 0)
    {
        posX_prev = 1;
        local_50 = 2;
        sVar7 = data.font_charPixHeight[1] + 3;
    }
    else
    {
        local_50 = 0;
        sVar7 = data.font_charPixHeight[2];
        if ((mb->state & 0x4000) == 0)
        {
            local_48 = data.font_charPixHeight[2];
            goto LAB_80045e94;
        }
    }
    local_48 = data.font_charPixHeight[1] + 3;
LAB_80045e94:

    local_60 = 0;
    mb->posX_prev = mb->posX_curr;
    mb->posY_prev = mb->posY_curr;
    DECOMP_MENUBOX_GetHeight(mb, &local_60, 0);

    state = mb->state;

    mb->width = menuboxWidth;
    mb->state &= 0xfffffff7;
    mb->height = local_60;

    if ((state & 2) != 0)
    {
        menuboxHeight = 0;
        DECOMP_MENUBOX_GetHeight(mb, &menuboxHeight, 1);
        local_38 = (short)(-menuboxHeight/2);
    }
    if ((state & 1) != 0)
    {
        local_40 = (short)(-menuboxWidth/2);
    }
    sVar6 = 0;
    row = &mb->rows[0];
    index = mb->stringIndexTitle;
    posY_prev = local_50 + local_38 + offsetY + mb->posY_prev;
    if ((-1 < index) && ((state & 4) == 0))
    {
        sVar4 = 1;
        if ((state & 0x4000) == 0)
        {
            sVar4 = posX_prev;
        }
        if ((state & 0x200) == 0)
        {
            offsetX = (short)(posX + mb->posX_prev);
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
            offsetX = (short)(posX + mb->posX_prev + (menuboxWidth/2));
        }
        DECOMP_DecalFont_DrawLine(titleString, offsetX, posY_prev, sVar4, uVar5);
        posY_prev = local_48 + posY_prev + 6;
    }

    if (row->stringIndex != -1)
    {
        local_30 = (menuboxWidth/2) + 1;
        local_2c = posX_prev;
        do
        {
            state = mb->state;
            if (((state & 0x44) == 0) || (sVar6 == mb->rowSelected))
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
                        sVar4 = (short)(posX + mb->posX_prev + 1);
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
                        sVar4 = (short)(posX + mb->posX_prev + local_30);
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
    if ((mb->state & 0x104) == 0)
    {
        background.x = local_40 + posX + mb->posX_prev;
        background.y = offsetY + mb->posY_prev + local_38;
        if ((mb->state & 0x40) == 0)
        {
            background.y += mb->rowSelected * sVar7 + local_50 + -1;
        }
        else
        {
            background.y += local_50 + -1;
        }
        if ((mb->state & 0x80) == 0)
        {
            background.h = -3;
        }
        else
        {
            background.h = 1;
        }
        background.h = sVar7 + background.h;
        if (-1 < mb->stringIndexTitle)
        {
            background.y += local_48 + 6;
        }
        rgb = &sdata->menuRowHighlight_Normal;
        if ((mb->drawStyle & 0x10U) != 0)
        {
            rgb = &sdata->menuRowHighlight_Green;
        }
        background.w = menuboxWidth;

        DECOMP_CTR_Box_DrawClearBox(
            &background, rgb, 1, 
            gGT->backBuffer->otMem.startPlusFour,
            &gGT->backBuffer->primMem);
    }
    if ((mb->state & 0x10) != 0)
    {
        DECOMP_MENUBOX_DrawSelf(mb->ptrNextBox_InHierarchy,
                         posX + mb->posX_prev,
                         local_38 + offsetY + mb->posY_prev + sVar7 + 0xc, menuboxWidth);
    }
    posX_prev = mb->posX_prev;
    posY_prev = mb->posY_prev;
    if ((mb->state & 4) == 0)
    {

        borders.h = (local_60 + 8) - (*(char *)&mb->state >> 7);
    }
    else
    {
        borders.h = sVar7 + 8;
    }
    borders.w = menuboxWidth + 0xc;
    borders.y = local_38 + offsetY + posY_prev - 4;
    borders.x = local_40 + posX + posX_prev - 6;
    DECOMP_MENUBOX_DrawFullRect(mb, &borders);
}
