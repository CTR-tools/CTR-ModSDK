#include <common.h>

void UI_DrawStatsBar(short posX, short posY, u_int engineID);

void CS_Garage_EngineSelectProc(void)
{
    u_int charIndex = sdata->advCharSelectIndex_curr;
    struct GameTracker *gGT = sdata->gGT;
    struct PrimMem *primMem = &gGT->backBuffer->primMem;
    struct MetaDataCHAR *MDC = &data.MetaDataCharacters[charIndex];
    u_char engineID = MDC->engineID;

    short statX = 128;

    // Tiger or Pura
    if (charIndex == 3 || charIndex == 7)
        statX = 384;

    // Draw Stats Box
    UI_DrawStatsBar(statX, 11, engineID);

    // Draw Arrows around the box
    char arrowColor = ORANGE;

    // blink arrows
    if ((sdata->frameCounter & FPS_DOUBLE(4)) == 0)
    {
        arrowColor = RED;
    }

    int *arrowColors = data.ptrColor[arrowColor];
    short arrowPos[2] = {236 - statX, statX + 274};
    short arrowRot[2] = {0x800, 0};

    struct Icon **iconPtrArray =
        ICONGROUP_GETICONS(gGT->iconGroup[4]);

    for (int i = 0; i < 2; i++)
    {
        DECOMP_DecalHUD_Arrow2D(
            iconPtrArray[0x38],
            arrowPos[i],
            43,

            primMem,
            gGT->pushBuffer_UI.ptrOT,

            arrowColors[0], arrowColors[1],
            arrowColors[2], arrowColors[3],

            0, 0x1000, arrowRot[i]);
    }

    int buttonTap = sdata->gGamepads->gamepad[0].buttonsTapped;
    u_char sfx = 0;

    switch (buttonTap)
    {
        // left
    case BTN_LEFT:
        // decrease
        engineID = (engineID + 4) % 5;
        sfx = 0;
        break;
        // right
    case BTN_RIGHT:
        // increase
        engineID = (engineID + 1) % 5;
        sfx = 0;
        break;
        // Choose class by pressing Cross
    case BTN_CROSS:
        sfx = 1;
        sdata->ptrDesiredMenu = &data.menuSubmitName;
        break;
    case (BTN_TRIANGLE | BTN_SQUARE):
        sfx = 2;
        sdata->ptrDesiredMenu = DECOMP_CS_Garage_GetMenuPtr();
    }

    // write back to meta
    MDC->engineID = engineID;

    DecalFont_DrawLine(
        "PRESS LEFR OR RIGHT TO SWAP ENGINE",

        0x100,                    // midpoint
        0xc8,                     // near bottom
        FONT_SMALL,               // small text
        (JUSTIFY_CENTER | ORANGE) // center
    );
}

struct RectMenu garageEngineSelect =
    {
        .stringIndexTitle = 0xFFFF,
        .posX_curr = 0x100,
        .posY_curr = 0x6c,

        .unk1 = 0,

        .state = 0x823,
        .rows = 0,
        .funcPtr = CS_Garage_EngineSelectProc,
        .drawStyle = 0,
}