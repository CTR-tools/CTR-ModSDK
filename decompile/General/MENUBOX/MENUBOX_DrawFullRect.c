#include <common.h>

void DECOMP_MENUBOX_DrawFullRect(struct MenuBox *mb, RECT *inner)
{
    u_int *rgb;
    RECT outer;
    struct GameTracker *gGT = sdata->gGT;

    // if title text exists
    if ((-1 < mb->stringIndexTitle) && ((mb->state & 4) == 0))
    {
        rgb = (mb->drawStyle & 0x10) ? &sdata->battleSetup_Color_UI_2 : &sdata->battleSetup_Color_UI_1;

        outer.x = inner->x + 3;
        outer.y = inner->y + 6;

        // pixel-height of non-title menu rows
        if ((mb->state & 0x80) == 0)
        {
            outer.y = inner->y + 9 + data.font_charPixHeight[1];
        }
        else if ((mb->state & 0x4000) == 0)
        {
            outer.y += data.font_charPixHeight[2];
        }
        else
        {
            outer.y += data.font_charPixHeight[1];
        }

        outer.h = 2;
        outer.w = inner->w - 6;

        DECOMP_MENUBOX_DrawOuterRect_Edge(&outer, rgb, (mb->drawStyle | 0x20), gGT->backBuffer->otMem.startPlusFour);
    }
    DECOMP_MENUBOX_DrawInnerRect(inner, mb->drawStyle, gGT->backBuffer->otMem.startPlusFour);
}