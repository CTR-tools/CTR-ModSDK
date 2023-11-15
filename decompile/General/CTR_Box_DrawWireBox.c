#include <common.h>

void DECOMP_CTR_Box_DrawWireBox(RECT *r, u_char *rgb, void *ot, struct PrimMem *primMem)
{
  LINE_F3 *p;

  p = primMem->curr;
  if (p > primMem->endMin100)
	return;
  primMem->curr = p + 1;

  // set Poly_LineF3 len, code, and padding
  setLineF3(p);
  
  // RGB
  setRGB0(p, rgb[0], rgb[1], rgb[2]);
  
  setXY3(p,
         r->x, r->y,                    // XY0
         (r->x + r->w), r->y,           // XY1
         (r->x + r->w), (r->y + r->h)); // XY2
  
  AddPrim(ot, p);

  p = primMem->curr;
  if (p > primMem->endMin100)
	return;
  primMem->curr = p + 1;

  // set Poly_LineF3 len, code, and padding
  setLineF3(p);
  
  // RGB
  setRGB0(p, rgb[0], rgb[1], rgb[2]);
  
  setXY3(p,
         r->x, r->y,                    // XY0
         r->x, (r->y + r->h),           // XY1
         (r->x + r->w), (r->y + r->h)); // XY2
  
  AddPrim(ot, p);
}