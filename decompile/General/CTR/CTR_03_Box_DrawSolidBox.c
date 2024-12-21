#include <common.h>

void DECOMP_CTR_Box_DrawSolidBox(RECT * r, Color color, u_long * ot)
{
	PolyF4 * p;
    GetPrimMem(p);
    if (p == nullptr) { return; }

    const PrimCode primCode = { .poly = { .renderCode = RenderCode_Polygon, .quad = 1 } };
    color.code = primCode;
    p->colorCode = color;

    s16 topX = r->x;
    s16 topY = r->y;
    s16 bottomX = r->x + r->w;
    s16 bottomY = r->y + r->h;
    p->v[0].pos.x = topX;
    p->v[0].pos.y = topY;
    p->v[1].pos.x = bottomX;
    p->v[1].pos.y = topY;
    p->v[2].pos.x = topX;
    p->v[2].pos.y = bottomY;
    p->v[3].pos.x = bottomX;
    p->v[3].pos.y = bottomY;

    AddPrimitive(p, ot);
}