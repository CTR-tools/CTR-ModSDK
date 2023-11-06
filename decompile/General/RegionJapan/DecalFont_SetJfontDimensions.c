#include <common.h>

// Sets icon dimension data for every Japanese character in the game's fonts, which is then used for DecalFont_DrawLineStrlen

void DECOMP_DecalFont_SetJfontDimensions()
{
	struct Icon* jfontBig;
	struct Icon* jfontSmall;
	struct Icon* jfontSmall0x18;
	struct GameTracker* gGT = sdata->gGT;
	
	struct Icon** iconPtrArray;
	
	iconPtrArray = ICONGROUP_GETICONS(gGT->iconGroup[0xE]);
	jfontBig = iconPtrArray[0];
	
	iconPtrArray = ICONGROUP_GETICONS(gGT->iconGroup[0xF]);
	jfontSmall = iconPtrArray[0];
	jfontSmall0x18 = iconPtrArray[0x18];
	
	sdata->font_jfontBigIconData[0] = *(u_int*)&jfontBig->texLayout.u0;
	sdata->font_jfontBigIconData[1] = *(u_int*)&jfontBig->texLayout.u1;
	sdata->font_jfontBigIconData[2] = *(u_int*)&jfontBig->texLayout.u2;
	sdata->font_jfontSmallIconData[0] = *(u_int*)&jfontSmall->texLayout.u0;
	sdata->font_jfontSmallIconData[1] = *(u_int*)&jfontSmall->texLayout.u1;
	sdata->font_jfontSmallIconData[2] = *(u_int*)&jfontSmall->texLayout.u2;
	sdata->font_jFontSmall0x18IconData[0] = *(u_int*)&jfontSmall0x18->texLayout.u0;
	sdata->font_jFontSmall0x18IconData[1] = *(u_int*)&jfontSmall0x18->texLayout.u1;
	sdata->font_jFontSmall0x18IconData[2] = *(u_int*)&jfontSmall0x18->texLayout.u2;
	return;
}