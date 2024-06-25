#include <common.h>

void DECOMP_SelectProfile_DrawAdvProfile(struct AdvProgress *adv, int posX, int posY, u_int isHighlighted, short slotIndex, u_short menuFlag)
{
    u_int highlightColor;
    u_short emptySlotColor;
    u_short nameColor;
    u_short percentColor;
    u_short integerColor;
    u_int iconColor;
    RECT highlight;
    RECT box;
    struct GameTracker *gGT = sdata->gGT;

    u_int isGreenLoadMenu = (menuFlag & 0x10);

    // if not Green load menu (adv)
    if (isGreenLoadMenu == 0)
    {
        integerColor = JUSTIFY_RIGHT;
        emptySlotColor = RED;
        nameColor = PERIWINKLE;
        percentColor = WHITE;
    }
    else
    {
        integerColor = (LIGHT_GREEN | JUSTIFY_RIGHT);
        emptySlotColor = FOREST_GREEN;
        nameColor = LIGHT_GREEN;
        percentColor = LIGHT_GREEN;
    }

    GAMEPROG_AdvPercent(adv);

    // If Adventure Profile is empty
    if (adv->characterID < 0)
    {
        // EMPTY (slot)
        DecalFont_DrawLine(sdata->lngStrings[0xb5], posX + 0x6c, posY + 23, 1, emptySlotColor | JUSTIFY_CENTER);
    }
    else
    {
        iconColor = (isGreenLoadMenu) ? sdata->greenColor : sdata->greyColor;

        // Character Icon
        RECTMENU_DrawPolyGT4(gGT->ptrIcons[data.MetaDataCharacters[adv->characterID].iconID],
                            posX + 10, posY + 6,
                            &gGT->backBuffer->primMem,
                            gGT->pushBuffer_UI.ptrOT,
                            iconColor, iconColor, iconColor, iconColor,
                            1, 0x1000);

        // Draw Name of profile
        DecalFont_DrawLine(adv->name, posX + 0x6c, posY + 0x29, 1, nameColor | JUSTIFY_CENTER);

        // Print the numbers
        SelectProfile_PrintInteger(gGT->currAdvProfile.completionPercent, posX + 0x6a, posY + 23, 0, integerColor);
        SelectProfile_PrintInteger(gGT->currAdvProfile.numTrophies, posX + 0x6a, posY + 5, 0, integerColor);
        SelectProfile_PrintInteger(gGT->currAdvProfile.numKeys, posX + 0xb5, posY + 5, 0, integerColor);
        SelectProfile_PrintInteger(gGT->currAdvProfile.numRelics, posX + 0xb5, posY + 23, 0, integerColor);

        // "%"
        DecalFont_DrawLine(&sdata->s_percent_sign, posX + 0x70, posY + 23, 1, percentColor);

        // Draw instances of Trophy, Key and Relics
        for (int i = 0; i < 3; i++)
        {
            struct Instance * inst = sdata->LoadSaveData[(slotIndex * 3) + i].inst;
            inst->matrix.t[0] = SelectProfile_UI_ConvertX(posX + (i == 1 ? 0x78 : 0xc3), 0x100);
            inst->matrix.t[1] = SelectProfile_UI_ConvertY(posY + (i == 0 ? 0x1f : 0xd), 0x100);
            inst->matrix.t[2] = 0x100;
            inst->flags &= ~(HIDE_MODEL); // make visible
        }
    }

    // if this profile is currently highlighted
    if (isHighlighted != 0)
    {
        highlightColor = isGreenLoadMenu ? sdata->menuRowHighlight_Green : sdata->menuRowHighlight_Normal;

        highlight.x = posX + 6;
        highlight.y = posY + 4;
        highlight.w = 208;
        highlight.h = 53;
        Color color;
        color.self = highlightColor;
        DECOMP_CTR_Box_DrawClearBox(&highlight, color, 1, gGT->backBuffer->otMem.startPlusFour[0xC]);
    }

    box.x = posX;
    box.y = posY;
    box.w = 220;
    box.h = 61;
    RECTMENU_DrawInnerRect(&box, menuFlag, gGT->backBuffer->otMem.startPlusFour[0xC]);
}
