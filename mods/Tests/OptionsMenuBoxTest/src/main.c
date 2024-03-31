#include <common.h>

/*
void eggplant(struct GameTracker* gGT)
{
	//string1[]  = "         ";
	char string2[]  = "         ";
	char string3[]  = "         ";
	char string4[]  = "         ";
	char string5[]  = "         ";
	char string6[]  = "         ";
	char string7[]  = "         ";
	char string8[]  = "         ";
	char string9[]  = "         ";
	char string10[] = "         ";
	char string11[] = "         ";
	char string12[] = "         ";
	char string13[] = "         ";
	char string14[] = "         ";
	char string15[] = "         ";
	char string16[] = "         ";
	char string17[] = "         ";
	char string18[] = "         ";
	struct RectMenu* m = &data.menuRacingWheelConfig;

	//sprintf(string1,  "%d\n", m->stringIndexTitle);
	sprintf(string2,  "%d\n", m->posX_curr);
	sprintf(string3,  "%d\n", m->posY_curr);
	sprintf(string4,  "%X\n", m->unk1);
	sprintf(string5,  "%X\n", m->state);
	sprintf(string6,  "%X\n", m->rows);
	sprintf(string7,  "%X\n", m->funcPtr);
	sprintf(string8,  "%X\n", m->drawStyle);
	sprintf(string9,  "%d\n", m->posX_prev);
	sprintf(string10, "%d\n", m->posY_prev);
	sprintf(string11, "%d\n", m->rowSelected);
	sprintf(string12, "%X\n", m->unk1a);
	sprintf(string13, "%X\n", m->unk1e);
	sprintf(string14, "%d\n", m->width);
	sprintf(string15, "%d\n", m->height);
	sprintf(string16, "%X\n", m->ptrNextBox_InHierarchy);
	sprintf(string17, "%X\n", m->ptrPrevBox_InHierarchy);
	sprintf(string18, "%X\n", &data.menuRacingWheelConfig);

	DecalFont_DrawLine("stringTitle:",  6, 10 + 10*0,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("posX_curr:",  6, 10 + 10*1,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("posY_curr:",  6, 10 + 10*2,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("unk1:",  6, 10 + 10*3,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("state:",  6, 10 + 10*4,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("rows:",  6, 10 + 10*5,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("funcPtr:",  6, 10 + 10*6,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("drawStyle:",  6, 10 + 10*7,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("posX_prev:",  6, 10 + 10*8,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("posY_prev:", 6, 10 + 10*9,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("rowSelected:", 6, 10 + 10*10, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("unk1a:", 6, 10 + 10*11, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("unk1e", 6, 10 + 10*12, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("width", 6, 10 + 10*13, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("height", 6, 10 + 10*14, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("ptrNextBox:", 6, 10 + 10*15, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("ptrPrevBox:", 6, 10 + 10*16, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine("ptrCurrBox:", 6, 10 + 10*17, FONT_SMALL, COCO_MAGENTA);

	DecalFont_DrawLine(sdata->lngStrings[m->stringIndexTitle],  6 + 150, 10 + 10*0,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string2,  6 + 150, 10 + 10*1,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string3,  6 + 150, 10 + 10*2,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string4,  6 + 150, 10 + 10*3,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string5,  6 + 150, 10 + 10*4,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string6,  6 + 150, 10 + 10*5,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string7,  6 + 150, 10 + 10*6,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string8,  6 + 150, 10 + 10*7,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string9,  6 + 150, 10 + 10*8,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string10, 6 + 150, 10 + 10*9,  FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string11, 6 + 150, 10 + 10*10, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string12, 6 + 150, 10 + 10*11, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string13, 6 + 150, 10 + 10*12, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string14, 6 + 150, 10 + 10*13, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string15, 6 + 150, 10 + 10*14, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string16, 6 + 150, 10 + 10*15, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string17, 6 + 150, 10 + 10*16, FONT_SMALL, COCO_MAGENTA);
	DecalFont_DrawLine(string18, 6 + 150, 10 + 10*17, FONT_SMALL, COCO_MAGENTA);
}
*/

int Hello_Main()
{
	struct GameTracker* gGT = sdata->gGT;

	//if (gGT->numPlyrCurrGame == 1) eggplant(gGT);
	data.menuRacingWheelConfig.rowSelected = 9;
}