#include <common.h>

// speedometer background
void DECOMP_UI_DrawSpeedBG(void)

{
  char *puVar1;
  char uVar2;
  short sVar3;
  struct GameTracker *gGT;
  u_int uVar5;
  u_long *primmemCurr;
  u_int uVar7;
  POLY_G4 *p;
  int iVar9;
  struct DB* backDB_1;
  char *puVar11;
  struct DB* backDB_2;
  int iVar13;

  puVar11 = data.speedometerBG_vertData[0x38];
  backDB_1 = 1;
  iVar9 = 0;
  do {
    iVar13 = iVar9 + 2;

    CTR_Box_DrawWirePrims((((u_int)*puVar11 + 0x1e0) * 0x10000) >> 0x10,
                 (((u_int)puVar11[1] + 0xbe) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[0x38])[backDB_1 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[0x3a])[backDB_1 * 2] + 0xbe) * 0x10000) >> 0x10,
                 // white borders
                 0xff,0xff,0xff,

				 // pointer to OT memory
				 gGT->tileView_UI.ptrOT,

				 // pointer to PrimMem struct
        &gGT->backBuffer->primMem);

    uVar2 = *puVar11;
    puVar1 = puVar11 + 1;
    puVar11 = puVar11 + 4;

    CTR_Box_DrawWirePrims((((u_int)uVar2 + 0x1e1) * 0x10000) >> 0x10,
                 (((u_int)*puVar1 + 0xbf) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[0x38])[backDB_1 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[0x3a])[backDB_1 * 2] + 0xbf) * 0x10000) >> 0x10,
                 // Black background
                 0,0,0,

				 // pointer to OT memory
				 gGT->tileView_UI.ptrOT,

				 // pointer to PrimMem struct
				 &gGT->backBuffer->primMem);
    backDB_1 = iVar9 + 3;
    iVar9 = iVar13;
  } while (iVar13 < 0xe);
  iVar9 = 0;
  do {
    backDB_2 = iVar9 + 2;
	
    CTR_Box_DrawWirePrims((((data.speedometerBG_vertData[0])[iVar9 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[2])[iVar9 * 2] + 0xbe) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[0])[backDB_2 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[2])[backDB_2 * 2] + 0xbe) * 0x10000) >> 0x10,
                 // White borders
                 0xff,0xff,0xff,

				 // pointer to OT memory
				 gGT->tileView_UI.ptrOT,

				 // pointer to PrimMem struct
         &gGT->backBuffer->primMem);

    iVar13 = iVar9 + 1;
    backDB_1 = iVar9 + 3;

    CTR_Box_DrawWirePrims((((data.speedometerBG_vertData[0])[iVar13 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[2])[iVar13 * 2] + 0xbe) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[0])[backDB_1 * 2] + 0x1e0) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[2])[backDB_1 * 2] + 0xbe) * 0x10000) >> 0x10,
                 // white borders
                 0xff,0xff,0xff,

				 // pointer to OT memory
				 gGT->tileView_UI.ptrOT,

				 // pointer to PrimMem struct
         &gGT->backBuffer->primMem);

    CTR_Box_DrawWirePrims((((data.speedometerBG_vertData[0])[iVar9 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[2])[iVar9 * 2] + 0xbf) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[0])[backDB_2 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[2])[backDB_2 * 2] + 0xbf) * 0x10000) >> 0x10,
                 // Black background
                 0,0,0,

				 // pointer to OT memory
				 gGT->tileView_UI.ptrOT,

				 // pointer to PrimMem struct
				 &gGT->backBuffer->primMem);

    CTR_Box_DrawWirePrims((((data.speedometerBG_vertData[0])[iVar13 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[2])[iVar13 * 2] + 0xbf) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[0])[backDB_1 * 2] + 0x1e1) * 0x10000) >> 0x10,
                 (((data.speedometerBG_vertData[2])[backDB_1 * 2] + 0xbf) * 0x10000) >> 0x10,
                 // Black background
                 0,0,0,

				 // pointer to OT memory
				 gGT->tileView_UI.ptrOT,

				 // pointer to PrimMem struct
				 &gGT->backBuffer->primMem);

    backDB_1 = gGT->backBuffer;
    primmemCurr = backDB_1->primMem.curr;
    p = 0;
    if (primmemCurr <= (u_long *)backDB_1->primMem.endMin100) {
      backDB_1->primMem.curr = &primmemCurr[9];
      p = primmemCurr;
    }
    if (p == 0) {
      return;
    }
    uVar5 = 0xb500;
    uVar7 = uVar5;
    if ((2 < iVar9) && (uVar7 = 0xd1ff, 4 < iVar9)) {
      uVar5 = 0xd1ff;
      if (iVar9 < 7) {
        uVar7 = 0xdb;
      }
      else {
        uVar5 = 0xdb;
        uVar7 = uVar5;
      }
    }
    p->r0 = uVar5 | 0x38000000;
    p->r1 = uVar5 | 0x38000000;
    p->r2 = uVar7 | 0x38000000;
    p->r3 = uVar7 | 0x38000000;
    backDB_1 = iVar9 + 2;
    p->x0 = (data.speedometerBG_vertData[0])[iVar9 * 2] + 0x1e0;
    p->x1 = (data.speedometerBG_vertData[2])[iVar9 * 2] + 0xbe;
    p->x1 = (data.speedometerBG_vertData[0])[(iVar9 + 1) * 2] + 0x1e0;
    p->y1 = (data.speedometerBG_vertData[2])[(iVar9 + 1) * 2] + 0xbe;
    p->x2 = (data.speedometerBG_vertData[0])[backDB_1 * 2] + 0x1e0;
    p->y2 = (data.speedometerBG_vertData[2])[backDB_1 * 2] + 0xbe;
    p->x3 = (data.speedometerBG_vertData[0])[(iVar9 + 3) * 2] + 0x1e0;
    gGT = gGT;
    p->y3 = (data.speedometerBG_vertData[2])[(iVar9 + 3) * 2] + 0xbe;

	// pointer to OT memory
	primmemCurr = gGT->tileView_UI.ptrOT;

	*(int*)p = *primmemCurr | 0x8000000;
    *primmemCurr = (u_int)p & 0xffffff;
    iVar9 = backDB_1;
  } while (backDB_1 < 0xc);
  iVar13 = 0;
  backDB_1 = 0xc;
  iVar9 = 4;
  while( true )
  {
	// &gGT->backbuffer
    backDB_2 = &gGT->backBuffer;

	// PrimMem ptrCurrent
	primmemCurr = backDB_2->primMem.curr;

    p = 0;

	// if there is room for more
	if (primmemCurr <= backDB_2->primMem.endMin100)
	{
	  // increment primitive pointer
      backDB_2->primMem.curr = primmemCurr[9];
      p = (POLY_G4 *)primmemCurr;
    }
    if (p == 0) break;
    p->x1 = (data.speedometerBG_vertData[0] + iVar9) + 0x1e0;
    p->y1 = (data.speedometerBG_vertData[2] + iVar9) + 0xbe;
    p->x2 = (data.speedometerBG_vertData[0] + backDB_1) + 0x1e0;
    iVar9 = iVar9 + 8;
    p->y2 = (data.speedometerBG_vertData[2] + backDB_1) + 0xbe;
    iVar13 = iVar13 + 2;
    p->x3 = data.speedometerBG_vertData[0x34] + 0x1e0;
    sVar3 = data.speedometerBG_vertData[6];
    p->tag->len = 8; // (p + 3) ?
    p->pad0 = 0x32;
    p->r2 = 0;
    p->g2 = 0;
    p->b2 = 0;
    p->r1 = 0;
    p->g1 = 0;
    p->b1 = 0;
    p->r3 = 0;
    p->g3 = 0;
    p->b3 = 0;
    gGT = gGT;
    p->r0 = 0xe1000a00;
    p->g0 = 0;
    p->y3 = sVar3 + 0xbe;

	// pointer to OT memory
    primmemCurr = gGT->tileView_UI.ptrOT;

	backDB_1 = backDB_1 + 8;
    *(int*)p = *primmemCurr | 0x8000000;
    *primmemCurr = (u_int)p & 0xffffff;
    if (0xb < iVar13) {
      return;
    }
  }
  return;
}