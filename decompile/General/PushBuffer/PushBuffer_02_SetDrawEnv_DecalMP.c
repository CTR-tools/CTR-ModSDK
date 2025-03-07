#include <common.h>

void DECOMP_PushBuffer_SetDrawEnv_DecalMP(void* ot, struct DB* backBuffer, RECT viewport,
                                   u_short offsetX, u_short offsetY,
                                   u_char dtd, u_char dfe, u_char isbg,
                                   u_char tpageUpper, u_char tpageLower)
{
    void *p;

    DRAWENV newDrawEnv;

    // Copy DrawEnv from gGT->backBuffer
    int *dst = (int *)&newDrawEnv;
    int *src = (int *)&backBuffer->drawEnv;

    for (unsigned int i = 0; i < sizeof(DRAWENV) / 4; i++)
        dst[i] = src[i];

    // Now modify DrawEnv...

    // RECT viewport (startX, startY, endX, endY)
    newDrawEnv.clip.x = viewport.x;
    newDrawEnv.clip.y = viewport.y;
    newDrawEnv.clip.w = viewport.w;
    newDrawEnv.clip.h = viewport.h;

    // ofs[X]
    newDrawEnv.ofs[0] = offsetX;

    // ofs[Y]
    newDrawEnv.ofs[1] = offsetY;

    // tpage
    newDrawEnv.tpage = (uint16_t)((tpageUpper << 8) | tpageLower);

    // dtd (dithering)
    newDrawEnv.dtd = dtd;

    // dfe (blocked or permitted)
    newDrawEnv.dfe = dfe;

    // isbg (always 0)
    newDrawEnv.isbg = isbg;

    p = backBuffer->primMem.curr;

    // curr < endMin100
    if (p <= backBuffer->primMem.endMin100)
    {
        // advance curr
        backBuffer->primMem.curr = (void *)((unsigned int)backBuffer->primMem.curr + 0x40);

        // DrawEnv just built
        SetDrawEnv(p, &newDrawEnv);

        // This doesn't really draw a primitive,
        // it links the ptrOT from the camera,
        // into the ptrOT of backBuffer DB, allowing
        // this camera's primitives to draw
        AddPrim(ot, p);
    }
}