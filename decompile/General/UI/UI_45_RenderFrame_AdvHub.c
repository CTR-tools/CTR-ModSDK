#include <common.h>

void DECOMP_UI_RenderFrame_AdvHub(void)
{
    struct UiElement2D* hudStructPtr;
	
	hudStructPtr = data.hudStructPtr[0];

	DECOMP_UI_DrawNumRelic	(hudStructPtr[0xE].x + 0x10,  hudStructPtr[0xE].y - 10);
	DECOMP_UI_DrawNumKey	(hudStructPtr[0xF].x + 0x10,  hudStructPtr[0xF].y - 10);
	DECOMP_UI_DrawNumTrophy	(hudStructPtr[0x10].x + 0x10, hudStructPtr[0x10].y - 10);
}
