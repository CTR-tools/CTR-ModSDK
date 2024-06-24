#include <common.h>

void DECOMP_CTR_Box_DrawWireBox(RECT * r, Color color, void * ot)
{
    LineF3 * p;
    GetPrimMem(p);
    if (p == nullptr) { return; }

    const PrimCode primCode = { .line = { .renderCode = RenderCode_Line, .polyline = 1 } };
    color.code = primCode;

    p->colorCode = color;
    p->v[0].pos.x = r->x;
    p->v[0].pos.y = r->y;
    p->v[1].pos.x = r->x + r->w;
    p->v[1].pos.y = r->y;
    p->v[2].pos.x = r->x + r->w;
    p->v[2].pos.y = r->y + r->h;
    p->end = 0x55555555;

    AddPrimitive(p, ot);
    GetPrimMem(p);
    if (p == nullptr) { return; }

    p->colorCode = color;
    p->v[0].pos.x = r->x;
    p->v[0].pos.y = r->y;
    p->v[1].pos.x = r->x;
    p->v[1].pos.y = r->y + r->h;
    p->v[2].pos.x = r->x + r->w;
    p->v[2].pos.y = r->y + r->h;
    p->end = 0x55555555;

    AddPrimitive(p, ot);
}