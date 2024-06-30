#include <common.h>

void DECOMP_CTR_Box_DrawClearBox(RECT * r, Color color, int transparency, u_long * ot)
{
	typedef struct TPage_PolyF4
	{
		TPage t;
		PolyF4 p;
	} TPage_PolyF4;

	TPage_PolyF4 * p;
	GetPrimMem(p);
	if (p == nullptr) { return; }

	p->t.texpage = (Texpage){ .code = 0xE1, .semiTransparency = transparency, .dither = 1 };
	p->p.tag.self = 0;

	const PrimCode primCode = { .poly = { .renderCode = RenderCode_Polygon, .quad = 1, .semiTransparency = 1 } };
	color.code = primCode;
	p->p.colorCode = color;

	s16 topX = r->x;
	s16 topY = r->y;
	s16 bottomX = r->x + r->w;
	s16 bottomY = r->y + r->h;
	p->p.v[0].pos.x = topX;
	p->p.v[0].pos.y = topY;
	p->p.v[1].pos.x = bottomX;
	p->p.v[1].pos.y = topY;
	p->p.v[2].pos.x = topX;
	p->p.v[2].pos.y = bottomY;
	p->p.v[3].pos.x = bottomX;
	p->p.v[3].pos.y = bottomY;

	AddPrimitive(p, ot);
}