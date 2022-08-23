#include <common.h>

// Sets icon dimension data for every Japanese character in the game's fonts, which is then used for DecalFont_DrawLineStrlen

void DECOMP_DecalFont_SetJfontDimensions()
{
	struct Icon* jfontBig;
	struct Icon* jfontSmall;
	struct Icon* jfontSmall0x18;
	
	jfontBig = sdata.gGT->iconGroup[0xe]->icons[0];
	jfontSmall = sdata.gGT->iconGroup[0xf]->icons[0];
	jfontSmall0x18 = sdata.gGT->iconGroup[0xf]->icons[0x18];
	sdata.font_jfontBigIconData[0] = *(u_int*)&jfontBig->X1;
	sdata.font_jfontBigIconData[1] = *(u_int*)&jfontBig->X2;
	sdata.font_jfontBigIconData[2] = *(u_int*)&jfontBig->X3;
	sdata.font_jfontSmallIconData[0] = *(u_int*)&jfontSmall->X1;
	sdata.font_jfontSmallIconData[1] = *(u_int*)&jfontSmall->X2;
	sdata.font_jfontSmallIconData[2] = *(u_int*)&jfontSmall->X3;
	sdata.font_jFontSmall0x18IconData[0] = *(u_int*)&jfontSmall0x18->X1;
	sdata.font_jFontSmall0x18IconData[1] = *(u_int*)&jfontSmall0x18->X2;
	sdata.font_jFontSmall0x18IconData[2] = *(u_int*)&jfontSmall0x18->X3;
	return;
}