#include <common.h>
// called "CTR" for no good reason,
// come back to this later

void DECOMP_CTR_Box_DrawWirePrims(Point p1, Point p2, Color color, void *ot)
{
    LineF2 * p;
    GetPrimMem(p);
    if (p == nullptr) { return; }

    const PolyCode polyCode = { .renderCode = RenderCode_Line };
    color.code = polyCode;
    p->colorCode = color;
    p->v[0].pos = p1;
    p->v[1].pos = p2;

    AddPrimitive(p, ot);
}