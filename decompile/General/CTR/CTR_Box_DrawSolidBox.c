#include <common.h>

void DECOMP_CTR_Box_DrawSolidBox(RECT * r, Color color, u_long * ot)
{
	PolyF4 * p;
    GetPrimMem(p);
    if (p == nullptr) { return; }

    const PrimCode primCode = { .poly = { .renderCode = RenderCode_Polygon, .quad = 1 } };
    color.code = primCode;

    p->colorCode = color;
    p->v[0].pos.x = r->x;
    p->v[0].pos.y = r->y;
    p->v[1].pos.x = r->x + r->w;
    p->v[1].pos.y = r->y;
    p->v[2].pos.x = r->x;
    p->v[2].pos.y = r->y + r->h;
    p->v[3].pos.x = r->x + r->w;
    p->v[3].pos.y = r->y + r->h;

    AddPrimitive(p, ot);
}