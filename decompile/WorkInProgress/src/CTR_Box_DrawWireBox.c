#include <common.h>

void DECOMP_CTR_Box_DrawWireBox(RECT *r, u_char *rgb, void *ot, struct PrimMem *primMem)
{
  void *primmemCurr = primMem->curr;
  LINE_F3 *p = NULL;

  if (primmemCurr <= primMem->endMin100)
  {
    p = (LINE_F3 *)primmemCurr;
    primMem->curr = p + 1;
  }

  if (p != NULL)
  {
    // set Poly_LineF3 len, code, and padding
    setLineF3(p);

    // RGB
    setRGB0(p, rgb[0], rgb[1], rgb[2]);

    setXY3(p,
           r.x, r->x,                    // XY0
           (r.x + r->x), r->x,           // XY1
           (r.x + r->w), (r->x + r->h)); // XY2

    AddPrim(ot, p);
  }

  primmemCurr = primMem->curr;

  if (primmemCurr <= primMem->endMin100)
  {
    p = (LINE_F3 *)primmemCurr;
    primMem->curr = p + 1;
  }

  if (p == null)
    return;

  // set Poly_LineF3 len, code, and padding
  setLineF3(p);

  // RGB
  setRGB0(p, rgb[0], rgb[1], rgb[2]);

  setXY3(p,
         r.x, r->x,                    // XY0
         r.x, (r->x + r->h),           // XY1
         (r.x + r->w), (r->x + r->h)); // XY2

  AddPrim(ot, p);
}