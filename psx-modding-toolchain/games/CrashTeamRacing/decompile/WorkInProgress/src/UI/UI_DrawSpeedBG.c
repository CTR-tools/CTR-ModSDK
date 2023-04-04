#include <common.h>

// speedometer background
void DECOMP_UI_DrawSpeedBG(void)
{
  struct GameTracker* gGT;
  u_int color0, color1;
  u_long* primmemCurr;
  POLY_G4 *p;
  char* upperHalf; // I think?
  struct DB* backDB;
  int i, j, k;

  gGT = sdata->gGT;
  upperHalf = &data.speedometerBG_vertData[0x38];
  backDB = gGT->backBuffer;
  for (i = 0; i < 0xe; i += 2) {
    j = i + 1;
    CTR_Box_DrawWirePrims(
      (upperHalf[0] + 0x1e0),
      (upperHalf[1] + 0xbe),
      (data.speedometerBG_vertData[0x38 + (j * 2)] + 0x1e0),
      (data.speedometerBG_vertData[0x3a + (j * 2)] + 0xbe),
        // white borders
        0xff, 0xff, 0xff,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);
    
    CTR_Box_DrawWirePrims(
      (upperHalf[0] + 0x1e1),
      (upperHalf[1] + 0xbf),
      (data.speedometerBG_vertData[0x38 + (j * 2)] + 0x1e1),
      (data.speedometerBG_vertData[0x3a + (j * 2)] + 0xbf),
        // Black background
        0, 0, 0,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);
      upperHalf += 4;
  }
  for (i = 0; i < 0xc; i +=2 ) {
    j = i + 2;

    CTR_Box_DrawWirePrims(
      (data.speedometerBG_vertData[i * 2] + 0x1e0),
      (data.speedometerBG_vertData[2 + (i * 2)] + 0xbe),
      (data.speedometerBG_vertData[j * 2] + 0x1e0),
      (data.speedometerBG_vertData[2 + (j * 2)] + 0xbe),
        // White borders
        0xff, 0xff, 0xff,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);

    k = i + 1;

    CTR_Box_DrawWirePrims(
      (data.speedometerBG_vertData[k * 2] + 0x1e0),
      (data.speedometerBG_vertData[2 + (k * 2)] + 0xbe),
      (data.speedometerBG_vertData[(j + 1) * 2] + 0x1e0),
      (data.speedometerBG_vertData[2 + ((j + 1) * 2)] + 0xbe),
        // white borders
        0xff, 0xff, 0xff,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);

    CTR_Box_DrawWirePrims(
      (data.speedometerBG_vertData[i * 2] + 0x1e1),
      (data.speedometerBG_vertData[2 + (i * 2)] + 0xbf),
      (data.speedometerBG_vertData[j * 2] + 0x1e1),
      (data.speedometerBG_vertData[2 + (j * 2)] + 0xbf),
        // Black background
        0, 0, 0,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);

    CTR_Box_DrawWirePrims(
      (data.speedometerBG_vertData[k * 2] + 0x1e1),
      (data.speedometerBG_vertData[2 + (k * 2)] + 0xbf),
      (data.speedometerBG_vertData[(j + 1) * 2] + 0x1e1),
      (data.speedometerBG_vertData[2 + ((j + 1) * 2)] + 0xbf),
        // Black background
        0, 0, 0,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);

    // reset prim
    primmemCurr = backDB->primMem.curr;

    if (primmemCurr <= (u_long *)backDB->primMem.endMin100) {
      backDB->primMem.curr = primmemCurr + 9;
      p = (POLY_G4*)primmemCurr;
    }
    if (p == 0) return;

    color0 = 0xb500;
    color1 = color0;
    if ((2 < i) && (color1 = 0xd1ff, 4 < i)) {
      color0 = 0xd1ff;
      if (i < 7) {
        color1 = 0xdb;
      } else {
        color0 = 0xdb;
        color1 = color0;
      }
    }

    *(u_int *)&p->r0 = color0 | 0x38000000;
    *(u_int *)&p->r1 = color0 | 0x38000000;
    *(u_int *)&p->r2 = color1 | 0x38000000;
    *(u_int *)&p->r3 = color1 | 0x38000000;
    p->x0 = data.speedometerBG_vertData[i * 2] + 0x1e0;
    p->x1 = data.speedometerBG_vertData[2 + (i * 2)] + 0xbe;
    p->x1 = data.speedometerBG_vertData[(i + 1) * 2] + 0x1e0;
    p->y1 = data.speedometerBG_vertData[2 + ((i + 1) * 2)] + 0xbe;
    p->x2 = data.speedometerBG_vertData[j * 2] + 0x1e0;
    p->y2 = data.speedometerBG_vertData[2 + (j * 2)] + 0xbe;
    p->x3 = data.speedometerBG_vertData[(i + 3) * 2] + 0x1e0;
    p->y3 = data.speedometerBG_vertData[2 + ((i + 3) * 2)] + 0xbe;

    // pointer to OT memory
    primmemCurr = gGT->tileView_UI.ptrOT;

    *(int*)p = *primmemCurr | 0x8000000;
    *primmemCurr = (u_int)p & 0xffffff;
  }
  j = 0xc;
  k = 4;

  for (i = 0; i < 0xc; i += 2) {
    // prim reset
    primmemCurr = backDB->primMem.curr;
    p = 0;

    // if there is room for more
    if (primmemCurr <= (u_long *)backDB->primMem.endMin100) {
      // increment primitive pointer
      backDB->primMem.curr = primmemCurr + 9;
      p = (POLY_G4*)primmemCurr;
    }
    if (p == 0) return;
    ((P_TAG *)p)->len = 8;
    *(u_int *)&p->r0 = 0xe1000a00;
    p->g0 = 0;
    p->r1 = 0;
    p->g1 = 0;
    p->b1 = 0;
    p->r2 = 0;
    p->g2 = 0;
    p->b2 = 0;
    p->pad0 = 0x32;
    p->r3 = 0;
    p->g3 = 0;
    p->b3 = 0;
    p->x1 = data.speedometerBG_vertData[k] + 0x1e0;
    p->y1 = data.speedometerBG_vertData[2 + k] + 0xbe;
    p->x2 = data.speedometerBG_vertData[j] + 0x1e0;
    p->y2 = data.speedometerBG_vertData[2 + j] + 0xbe;
    p->x3 = data.speedometerBG_vertData[0x34] + 0x1e0;
    p->y3 = data.speedometerBG_vertData[6] + 0xbe;

    k += 8;
    j += 8;

    // pointer to OT memory
    primmemCurr = gGT->tileView_UI.ptrOT;

    *(int*)p = *primmemCurr | 0x8000000;
    *primmemCurr = (u_int)p & 0xffffff;
  }
  return;
}