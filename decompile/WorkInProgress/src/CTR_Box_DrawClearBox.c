#include <common.h>

void DECOMP_CTR_Box_DrawClearBox(RECT *r, u_char *highlights, char unkBool, u_long *ot, struct PrimMem *primMem)
{
    void *primmemCurr;
    POLY_G4 *p = NULL;

    primmemCurr = primMem->curr;
    if (primmemCurr <= primMem->endMin100)
    {
        p = (POLY_G4 *)primmemCurr;
        primMem->curr = p + 1;
    }

    if (p == NULL)
        return;

    setlen(p, 7);
    setcode(p, 0xe1);

    // colors
    *(u_int *)&p->r0 = unkBool << 5 | 0x000a00; // probably shadow/transparent?
    setRGB1(p, highlights[0], highlights[1], highlights[2]);
    
    // *(u_int *)((int)p + 8) = 0; // what is this?
    // setRGB2(p, 0, 0, 0); // never set
    // setRGB3(p, 0, 0, 0); // never set

    p->pad0 = 0x2a;

    // the offests are off, but there's no way RECT values are used for colors, right?
    setXY4(p,
           r->x,            r->y,                  // XY0
           (r->x + r->w),   r->y,                  // XY1
           r->x,            (r->y + r->w),         // XY2
           (r->x + r->w),   (r->y + r->w)          // XY3
    );
    AddPrim(ot, p);
}