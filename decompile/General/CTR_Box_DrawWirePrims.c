#include <common.h>
// called "CTR" for no good reason,
// come back to this later

void DECOMP_CTR_Box_DrawWirePrims(u_short x0, u_short y0, u_short x1, u_short y1,
                                  u_char red, u_char green, u_char blue, void *ot, struct PrimMem *primMem)
{
    LINE_F2 *p = NULL;
    void *primmemCurr = primMem->curr;

    if (primmemCurr <= primMem->endMin100)
    {
        p = (LINE_F2 *)primmemCurr;
        primMem->curr = p + 1;
    }

    if (p == NULL)
        return;

    setLineF2(p);

    setRGB0(p, red, green, blue);

    // two points (x,y)
    setXY2(p, x0, y0, x1, y1);

    AddPrim(ot, p);
}