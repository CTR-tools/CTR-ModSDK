#include <common.h>

void DECOMP_UI_DrawNumRelic(short, short);
void DECOMP_UI_DrawNumKey(short, short);
void DECOMP_UI_DrawNumTrophy(short, short);

void DECOMP_UI_RenderFrame_AdvHub(void)
{
    struct UiElement2D* hudStructPtr;
	
	hudStructPtr = data.hudStructPtr[0];

	DECOMP_UI_DrawNumRelic	(hudStructPtr[0x1C].x + 0x10, hudStructPtr[0x1C].y - 10);
	DECOMP_UI_DrawNumKey	(hudStructPtr[0x1E].x + 0x10, hudStructPtr[0x1E].y - 10);
	DECOMP_UI_DrawNumTrophy	(hudStructPtr[0x20].x + 0x10, hudStructPtr[0x20].y - 10);
}
