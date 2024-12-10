#include <common.h>

// Does not fit byte budget
void DECOMP_DebugFont_Init(struct GameTracker* gGT)
{
	struct Icon* debugFontIcon = gGT->ptrIcons[0x42];

	if(debugFontIcon == 0) return;

	u8 u = debugFontIcon->texLayout.u0;
	u8 v = debugFontIcon->texLayout.v0;
	u16 clut = debugFontIcon->texLayout.clut;
	u16 tpage = debugFontIcon->texLayout.tpage;
	sdata->debugFont.u = u;
	sdata->debugFont.v = v;
	sdata->debugFont.clut = clut;
	sdata->debugFont.tpage = tpage;
}
