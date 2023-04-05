#include <common.h>

void NumbersToString(char * str, int value, int digits, int hexadecimal);

void DECOMP_UI_DrawDriverIcon(struct Icon* icon, short posX, short posY, struct PrimMem* primMem, u_long* ot, char transparency, short scale, u_int color)
{
	short height;
	short width;
	short rightX;
	short topY;
	short bottomY;
	char bottomV;
	POLY_FT4* p;

	int margintop = 10;
	int marginleft = 6;
	char s_x0[] = "     ";
	char s_x1[] = "     ";
	char s_x2[] = "     ";
	char s_x3[] = "     ";
	char s_y0[] = "     ";
	char s_y1[] = "     ";
	char s_y2[] = "     ";
	char s_y3[] = "     ";
	char s_tpage[] = "     ";
	char s_u0[] = "    ";
	char s_u1[] = "    ";
	char s_u2[] = "    ";
	char s_u3[] = "    ";
	char s_v0[] = "    ";
	char s_v1[] = "    ";
	char s_v2[] = "    ";
	char s_v3[] = "    ";
	char s_clut[] = "     ";

	p = (POLY_FT4*)primMem->curr;

	width = icon->texLayout.u1 - icon->texLayout.u0;
	height = icon->texLayout.v2 - icon->texLayout.v0;
	rightX = posX + (width * scale >> 12);
	topY = (posY < 166) ? posY : 165;
	bottomY = ((posY + (height * scale >> 12)) < 166) ? (posY + (height * scale >> 12)) : 165;
	bottomV = (icon->texLayout.v0 + bottomY) - posY;

	setPolyFT4(p);
	setRGB0(p, color & 0xff, (color & 0xff00) >> 8, (color & 0xff0000) >> 16);
	setXY4(p, posX, topY, rightX, topY, posX, bottomY, rightX, bottomY);
	setUV4(p, icon->texLayout.u0, icon->texLayout.v0, icon->texLayout.u1, icon->texLayout.v1, icon->texLayout.u2, bottomV, icon->texLayout.u3, bottomV);
	p->clut = icon->texLayout.clut;
	p->tpage = icon->texLayout.tpage;

	if (transparency != 0)
	{
		// disable blending mode bits of the texpage using AND, then set them using OR
		// then set image to use semi-transparent mode using the setSemiTrans macro
		// blending mode bits on most Icon images are set to 11 (Mode 3, which is no blending)
		// this function is always called with this parameter set to 1 (which is Mode 0, equivalent to 50% transparency)

		p->tpage = p->tpage & 0xff9f | (transparency - 1) << 5;
		setSemiTrans(p, true);
	}

	// could also use the psn00bsdk macro, there is no difference
	AddPrim(ot, p);

	// POLY_FT4 is 0x28 bytes large
	primMem->curr = p + 1;

	NumbersToString(s_x0, p->x0, 3, 0);
	NumbersToString(s_y0, p->y0, 3, 0);
	NumbersToString(s_x1, p->x1, 3, 0);
	NumbersToString(s_y1, p->y1, 3, 0);
	NumbersToString(s_x2, p->x2, 3, 0);
	NumbersToString(s_y2, p->y2, 3, 0);
	NumbersToString(s_x3, p->x3, 3, 0);
	NumbersToString(s_y3, p->y3, 3, 0);
	NumbersToString(s_u0, p->u0, 3, 0);
	NumbersToString(s_v0, p->v0, 3, 0);
	NumbersToString(s_u1, p->u1, 3, 0);
	NumbersToString(s_v1, p->v1, 3, 0);
	NumbersToString(s_u2, p->u2, 3, 0);
	NumbersToString(s_v2, p->v2, 3, 0);
	NumbersToString(s_u3, p->u3, 3, 0);
	NumbersToString(s_v3, p->v3, 3, 0);
	NumbersToString(s_tpage, p->tpage, 4, 1);
	NumbersToString(s_clut, p->clut, 4, 1);

	if (!(sdata->gGT->gameMode1 & LOADING))
	{
		DecalFont_DrawLine("NAME:", marginleft, margintop+10*0, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("X0:", marginleft, margintop+10*1, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("Y0:", marginleft, margintop+10*2, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("u0:", marginleft, margintop+10*3, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("v0:", marginleft, margintop+10*4, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("clut:", marginleft, margintop+10*5, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("x1:", marginleft, margintop+10*6, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("y1:", marginleft, margintop+10*7, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("u1:", marginleft, margintop+10*8, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("v1:", marginleft, margintop+10*9, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("tpage:", marginleft, margintop+10*10, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("x2:", marginleft, margintop+10*11, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("y2:", marginleft, margintop+10*12, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("u2:", marginleft, margintop+10*13, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("v2:", marginleft, margintop+10*14, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("x3:", marginleft, margintop+10*15, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("y3:", marginleft, margintop+10*16, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("u3:", marginleft, margintop+10*17, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine("v3:", marginleft, margintop+10*18, FONT_SMALL, COCO_MAGENTA);

		DecalFont_DrawLine(icon->name, marginleft+70, margintop+10*0, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_x0, marginleft+70, margintop+10*1, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_y0, marginleft+70, margintop+10*2, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_u0, marginleft+70, margintop+10*3, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_v0, marginleft+70, margintop+10*4, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_clut, marginleft+70, margintop+10*5, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_x1, marginleft+70, margintop+10*6, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_y1, marginleft+70, margintop+10*7, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_u1, marginleft+70, margintop+10*8, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_v1, marginleft+70, margintop+10*9, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_tpage, marginleft+70, margintop+10*10, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_x2, marginleft+70, margintop+10*11, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_y2, marginleft+70, margintop+10*12, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_u2, marginleft+70, margintop+10*13, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_v2, marginleft+70, margintop+10*14, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_x3, marginleft+70, margintop+10*15, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_y3, marginleft+70, margintop+10*16, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_u3, marginleft+70, margintop+10*17, FONT_SMALL, COCO_MAGENTA);
		DecalFont_DrawLine(s_v3, marginleft+70, margintop+10*18, FONT_SMALL, COCO_MAGENTA);
	}

	return;
}