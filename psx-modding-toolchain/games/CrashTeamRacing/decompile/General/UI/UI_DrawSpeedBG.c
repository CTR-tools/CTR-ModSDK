#include <common.h>

// speedometer background
void DECOMP_UI_DrawSpeedBG(void)
{
  struct GameTracker* gGT;
  u_int color0, color1;
  u_long* primmemCurr;
  POLY_G4 *p;
  short* vertData;
  short* upperHalf;
  struct DB* backDB;
  int i;

  gGT = sdata->gGT;

  vertData = &data.speedometerBG_vertData;
  upperHalf = &vertData[0x1c];
  backDB = gGT->backBuffer;
  for (i = 0; i < 6; i++) {
    CTR_Box_DrawWirePrims(
      (u_short)(upperHalf[0] + 0x1e0),
      (u_short)(upperHalf[1] + 0xbe),
      (u_short)(upperHalf[2] + 0x1e0),
      (u_short)(upperHalf[3] + 0xbe),
        // white borders
        0xff, 0xff, 0xff,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &backDB->primMem);
    
    CTR_Box_DrawWirePrims(
      (u_short)(upperHalf[0] + 0x1e1),
      (u_short)(upperHalf[1] + 0xbf),
      (u_short)(upperHalf[2] + 0x1e1),
      (u_short)(upperHalf[3] + 0xbf),
        // Black background
        0, 0, 0,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &backDB->primMem);
      upperHalf += 4;
  }
  for (i = 0; i < 6; i++) {
    CTR_Box_DrawWirePrims(
      (u_short)(vertData[0] + 0x1e0),
      (u_short)(vertData[1] + 0xbe),
      (u_short)(vertData[4] + 0x1e0),
      (u_short)(vertData[5] + 0xbe),
        // White borders
        0xff, 0xff, 0xff,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);

    CTR_Box_DrawWirePrims(
      (u_short)(vertData[2] + 0x1e0),
      (u_short)(vertData[3] + 0xbe),
      (u_short)(vertData[6] + 0x1e0),
      (u_short)(vertData[7] + 0xbe),
        // white borders
        0xff, 0xff, 0xff,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);

    CTR_Box_DrawWirePrims(
      (u_short)(vertData[0] + 0x1e1),
      (u_short)(vertData[1] + 0xbf),
      (u_short)(vertData[4] + 0x1e1),
      (u_short)(vertData[5] + 0xbf),
        // Black background
        0, 0, 0,

        // pointer to OT memory
        gGT->tileView_UI.ptrOT,

        // pointer to PrimMem struct
        &
        backDB->primMem);

    CTR_Box_DrawWirePrims(
      (u_short)(vertData[2] + 0x1e1),
      (u_short)(vertData[3] + 0xbf),
      (u_short)(vertData[6] + 0x1e1),
      (u_short)(vertData[7] + 0xbf),
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
    if ((1 < i) && (color1 = 0xd1ff, 2 < i)) {
      color0 = 0xd1ff;
      if (i < 4) {
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
    p->x0 = vertData[0] + 0x1e0;
    p->y0 = vertData[1] + 0xbe;
    p->x1 = vertData[2] + 0x1e0;
    p->y1 = vertData[3] + 0xbe;
    p->x2 = vertData[4] + 0x1e0;
    p->y2 = vertData[5] + 0xbe;
    p->x3 = vertData[6] + 0x1e0;
    p->y3 = vertData[7] + 0xbe;

    // pointer to OT memory
    primmemCurr = gGT->tileView_UI.ptrOT;

    *(int*)p = *primmemCurr | 0x8000000;
    *primmemCurr = (u_int)p & 0xffffff;
    vertData += 4;
  }
  
  vertData = &data.speedometerBG_vertData;
  
  for (i = 0; i < 6; i++) {
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
	*(u_int *)&p->x0 = 0;
	*(u_int *)&p->r1 = 0;
	*(u_int *)&p->r2 = 0;
	*(u_int *)&p->r3 = 0;
    p->pad0 = 0x32;
    p->x1 = vertData[2] + 0x1e0;
    p->y1 = vertData[3] + 0xbe;
    p->x2 = vertData[6] + 0x1e0;
    p->y2 = vertData[7] + 0xbe;
    p->x3 = data.speedometerBG_vertData[0x1A] + 0x1e0;
    p->y3 = data.speedometerBG_vertData[3] + 0xbe;

    // pointer to OT memory
    primmemCurr = gGT->tileView_UI.ptrOT;

    *(int*)p = *primmemCurr | 0x8000000;
    *primmemCurr = (u_int)p & 0xffffff;
    vertData += 4;
  }
  return;
}