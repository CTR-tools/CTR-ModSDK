#include <common.h>

void DECOMP_MM_Battle_DrawIcon_Character(struct Icon* icon, int posX, int posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale)
{
	if (icon == 0)  return;
	DECOMP_DecalHUD_DrawPolyFT4(icon, posX, posY, primMem, ot, transparency, scale);
}