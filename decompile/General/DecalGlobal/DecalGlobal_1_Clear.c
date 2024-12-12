#include <common.h>

void DECOMP_DecalGlobal_Clear(struct GameTracker* gGT)
{
	memset(&gGT->ptrIcons, 0, sizeof(gGT->ptrIcons));
	memset(&gGT->iconGroup, 0, sizeof(gGT->iconGroup));
}