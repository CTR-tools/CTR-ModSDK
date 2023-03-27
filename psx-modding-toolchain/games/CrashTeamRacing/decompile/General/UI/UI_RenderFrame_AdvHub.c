#include <common.h>

void UI_DrawNumRelic(short, short, struct Driver*);
void UI_DrawNumKey(short, short, struct Driver*);
void UI_DrawNumTrophy(short, short, struct Driver*);

void DECOMP_UI_RenderFrame_AdvHub(void)
{
    struct UiElement2D* hudStructPtr = data.hudStructPtr[0];
    struct Driver* player = sdata->gGT->drivers[0];
    int xOffset = 0x10;
    int yOffset = -10;

    UI_DrawNumRelic(hudStructPtr[0x38].x + xOffset, hudStructPtr[0x38].y + yOffset, player);
    UI_DrawNumKey(hudStructPtr[0x3c].x + xOffset, hudStructPtr[0x3c].y + yOffset, player);
    UI_DrawNumTrophy(hudStructPtr[0x40].x + xOffset, hudStructPtr[0x40].y + yOffset, player);
}
