#include <common.h>

void DECOMP_CTR_Box_DrawWireBox(RECT * r, Color color, void * ot)
{
    LineF3 * p;
    GetPrimMem(p);
    if (p == nullptr) { return; }

    const PrimCode primCode = { .line = { .renderCode = RenderCode_Line, .polyline = 1 } };
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
    p->v[2].pos.x = bottomX;
    p->v[2].pos.y = bottomY;
    p->end = 0x55555555;

    AddPrimitive(p, ot);
    GetPrimMem(p);
    if (p == nullptr) { return; }

    p->colorCode = color;
    p->v[0].pos.x = topX;
    p->v[0].pos.y = topY;
    p->v[1].pos.x = topX;
    p->v[1].pos.y = bottomY;
    p->v[2].pos.x = bottomX;
    p->v[2].pos.y = bottomY;
    p->end = 0x55555555;

    AddPrimitive(p, ot);
}