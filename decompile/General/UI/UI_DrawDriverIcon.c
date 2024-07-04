#include <common.h>

void DECOMP_UI_DrawDriverIcon(struct Icon* icon, Point point, u_long* ot, unsigned transparency, int scale, Color color)
{
	PolyFT4 * p;
	GetPrimMem(p);
	if (p == nullptr) { return; }

	const PrimCode primCode = { .poly = { .renderCode = RenderCode_Polygon, .quad = 1, .textured = 1 } };
	color.code = primCode;
	p->colorCode = color;

	int width = icon->texLayout.u1 - icon->texLayout.u0;
	int height = icon->texLayout.v2 - icon->texLayout.v0;
	int topX = point.x;
	int bottomX = topX + FP_Mult(width, scale);
	#ifdef USE_ONLINE
		int topY = point.y;
		int bottomY = topY + FP_Mult(height, scale);
	#else
		#if BUILD != EurRetail
			int topY = (point.y < 166) ? point.y : 165;
			int bottomY = ((topY + FP_Mult(height, scale)) < 166) ? (topY + FP_Mult(height, scale)) : 165;
		#else
			int topY = (point.y < 176) ? point.y : 175;
			int bottomY = ((topY + FP_Mult(height, scale)) < 176) ? (topY + FP_Mult(height, scale)) : 175;
		#endif
	#endif

	#ifdef USE_16BY9
	int len = ((bottomX - topX) * 125) / 1000;
	topX += len;
	bottomX -= len;
	#endif

	p->v[0].pos.x = topX;
	p->v[0].pos.y = topY;
	p->v[1].pos.x = bottomX;
	p->v[1].pos.y = topY;
	p->v[2].pos.x = topX;
	p->v[2].pos.y = bottomY;
	p->v[3].pos.x = bottomX;
	p->v[3].pos.y = bottomY;

	p->polyClut.self = icon->texLayout.clut;
	p->polyTpage.self = icon->texLayout.tpage;

	if (transparency)
	{
		p->polyTpage.semiTransparency = transparency - 1;
		p->colorCode.code.poly.semiTransparency = 1;
	}

	#ifdef USE_ONLINE
	p->v[0].texCoords.u = icon->texLayout.u0;
	p->v[0].texCoords.v = icon->texLayout.v0;
	p->v[1].texCoords.u = icon->texLayout.u1;
	p->v[1].texCoords.v = icon->texLayout.v1;
	p->v[2].texCoords.u = icon->texLayout.u2;
	p->v[2].texCoords.v = icon->texLayout.v2;
	p->v[3].texCoords.u = icon->texLayout.u3;
	p->v[3].texCoords.v = icon->texLayout.v3;
	#else
	unsigned int bottomV = (icon->texLayout.v0 + bottomY) - point.y;
	p->v[0].texCoords.u = icon->texLayout.u0;
	p->v[0].texCoords.v = icon->texLayout.v0;
	p->v[1].texCoords.u = icon->texLayout.u1;
	p->v[1].texCoords.v = icon->texLayout.v1;
	p->v[2].texCoords.u = icon->texLayout.u2;
	p->v[2].texCoords.v = bottomV;
	p->v[3].texCoords.u = icon->texLayout.u3;
	p->v[3].texCoords.v = bottomV;
	#endif

	AddPrimitive(p, ot);
}