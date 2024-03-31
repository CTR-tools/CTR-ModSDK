#include <common.h>

void CTR_Box_DrawWireBox(RECT* r, int* unk, u_long* ot, struct PrimMem* primMem);

// copy/paste from HelloWorld_Advanced,
// the code is more heavily commented there
void DF_PrintText()
{
  struct GameTracker* gGT;
  u_long* backup;

  #if BUILD == SepReview
  if (sdata->Loading.stage >= 5) return;
  #elif BUILD >= UsaRetail
  if(sdata->Loading.stage == 5) return;
  #endif

  gGT = sdata->gGT;
  backup = gGT->pushBuffer_UI.ptrOT;
  gGT->pushBuffer_UI.ptrOT = gGT->otSwapchainDB[gGT->swapchainIndex];
  DecalFont_DrawLine("Debug View: R1+Select", 10, 208, FONT_SMALL, ORANGE);
  gGT->pushBuffer_UI.ptrOT = backup;
}

void DF_DrawBox()
{
  RECT r;
  unsigned int local_30 [2];

  r.x = 0;
  r.y = 0;
  r.w = 0x200;
  r.h = 0xd8;

  local_30[0] = 0xffff;
  local_30[1] = 0;

  CTR_Box_DrawWireBox(
	&r,local_30,
	sdata->gGT->pushBuffer_UI.ptrOT,
	&sdata->gGT->backBuffer->primMem);
}

void DF_ParseOT(u_long* param_1)
{
  u_int* header;

  int screenX;
  int screenY;
  int centerX;
  int centerY;

  // divide by two (more zoom out)
  // #define DIVIDE 0x200 >> 0xc

  // divide by four (original from june 1999)
  // #define DIVIDE 0x400 >> 0xc

  // divide by eight (less zoom out)
  #define DIVIDE 0x800 >> 0xc

  // yellow wireframe box
  DF_DrawBox();

  // original resolution
  screenX = 0x200;
  screenY = 0xd8;

  // center
  centerX = screenX >> 1;
  centerY = screenY >> 1;

  // start at beginning of OT
  header = (u_int*)param_1;

  // parse all PrimMem and OT
  while(1)
  {
	// OrderTabl header = XX-YYYYYY,
	//		Y is addr of Prim

	// Primitive header = XX-YYYYYY,
	//		if(XX==0)	Y is addr of next OT
	//		else		Y is addr of next Prim, XX = size

	// 24 bits address
	// 8 bits length
	// header = header->next
    header = (u_int *)(*header & 0xffffff | 0x80000000);

	// end loop condition
    if (header == (u_int *)0x80ffffff) break;

	// if header->length (8 bits in libgpu.h) == 0,
	// then this is not a pointer to next prim, must be ptr to OT,
	// so "continue" loop to get the next prim from this OT
	if ((*header & 0xff000000) == 0) continue;

	// 7th u_char of every primitive is a prim "code" that defines type,
	// ND's code was & 0xfc, but 0x7c is the correct logic
	switch(((P_TAG*)header)->code & 0x7c)
	{

	// 0x20 PolyF3
	// 0x48 LineF3
    case 0x20:
    case 0x48:
      ((POLY_F3*)header)->x0 = ((((POLY_F3*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((POLY_F3*)header)->y0 = ((((POLY_F3*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((POLY_F3*)header)->x1 = ((((POLY_F3*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((POLY_F3*)header)->y1 = ((((POLY_F3*)header)->y1 -centerY) * DIVIDE) + centerY;
      ((POLY_F3*)header)->x2 = ((((POLY_F3*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((POLY_F3*)header)->y2 = ((((POLY_F3*)header)->y2 -centerY) * DIVIDE) + centerY;
      break;

	// 0x24 PolyFT3
	// 0x30 PolyG3
    case 0x24:
    case 0x30:
      ((POLY_FT3*)header)->x0 = ((((POLY_FT3*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((POLY_FT3*)header)->y0 = ((((POLY_FT3*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((POLY_FT3*)header)->x1 = ((((POLY_FT3*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((POLY_FT3*)header)->y1 = ((((POLY_FT3*)header)->y1 -centerY) * DIVIDE) + centerY;
      ((POLY_FT3*)header)->x2 = ((((POLY_FT3*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((POLY_FT3*)header)->y2 = ((((POLY_FT3*)header)->y2 -centerY) * DIVIDE) + centerY;
      break;

	// 0x28 PolyF4
	// 0x4c LineF4
    case 0x28:
    case 0x4c:
      ((POLY_F4*)header)->x0 = ((((POLY_F4*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((POLY_F4*)header)->y0 = ((((POLY_F4*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((POLY_F4*)header)->x1 = ((((POLY_F4*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((POLY_F4*)header)->y1 = ((((POLY_F4*)header)->y1 -centerY) * DIVIDE) + centerY;
      ((POLY_F4*)header)->x2 = ((((POLY_F4*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((POLY_F4*)header)->y2 = ((((POLY_F4*)header)->y2 -centerY) * DIVIDE) + centerY;
      ((POLY_F4*)header)->x3 = ((((POLY_F4*)header)->x3 -centerX) * DIVIDE) + centerX;
      ((POLY_F4*)header)->y3 = ((((POLY_F4*)header)->y3 -centerY) * DIVIDE) + centerY;
      break;

	// 0x2C PolyFT4
	// 0x38 PolyG4
    case 0x2c:
    case 0x38:
      ((POLY_FT4*)header)->x0 = ((((POLY_FT4*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((POLY_FT4*)header)->y0 = ((((POLY_FT4*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((POLY_FT4*)header)->x1 = ((((POLY_FT4*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((POLY_FT4*)header)->y1 = ((((POLY_FT4*)header)->y1 -centerY) * DIVIDE) + centerY;
      ((POLY_FT4*)header)->x2 = ((((POLY_FT4*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((POLY_FT4*)header)->y2 = ((((POLY_FT4*)header)->y2 -centerY) * DIVIDE) + centerY;
      ((POLY_FT4*)header)->x3 = ((((POLY_FT4*)header)->x3 -centerX) * DIVIDE) + centerX;
      ((POLY_FT4*)header)->y3 = ((((POLY_FT4*)header)->y3 -centerY) * DIVIDE) + centerY;
	  break;

	// PolyGT3
    case 0x34:
      ((POLY_GT3*)header)->x0 = ((((POLY_GT3*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((POLY_GT3*)header)->y0 = ((((POLY_GT3*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((POLY_GT3*)header)->x1 = ((((POLY_GT3*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((POLY_GT3*)header)->y1 = ((((POLY_GT3*)header)->y1 -centerY) * DIVIDE) + centerY;
      ((POLY_GT3*)header)->x2 = ((((POLY_GT3*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((POLY_GT3*)header)->y2 = ((((POLY_GT3*)header)->y2 -centerY) * DIVIDE) + centerY;
	  break;

	// PolyGT4
    case 0x3c:
      ((POLY_GT4*)header)->x0 = ((((POLY_GT4*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((POLY_GT4*)header)->y0 = ((((POLY_GT4*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((POLY_GT4*)header)->x1 = ((((POLY_GT4*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((POLY_GT4*)header)->y1 = ((((POLY_GT4*)header)->y1 -centerY) * DIVIDE) + centerY;
      ((POLY_GT4*)header)->x2 = ((((POLY_GT4*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((POLY_GT4*)header)->y2 = ((((POLY_GT4*)header)->y2 -centerY) * DIVIDE) + centerY;
      ((POLY_GT4*)header)->x3 = ((((POLY_GT4*)header)->x3 -centerX) * DIVIDE) + centerX;
      ((POLY_GT4*)header)->y3 = ((((POLY_GT4*)header)->y3 -centerY) * DIVIDE) + centerY;
      break;

	// LineF2
    case 0x40:
      ((LINE_F2*)header)->x0 = ((((LINE_F2*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((LINE_F2*)header)->y0 = ((((LINE_F2*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((LINE_F2*)header)->x1 = ((((LINE_F2*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((LINE_F2*)header)->y1 = ((((LINE_F2*)header)->y1 -centerY) * DIVIDE) + centerY;
	  break;

	// LineG2
    case 0x50:
      ((LINE_G2*)header)->x0 = ((((LINE_G2*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((LINE_G2*)header)->y0 = ((((LINE_G2*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((LINE_G2*)header)->x1 = ((((LINE_G2*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((LINE_G2*)header)->y1 = ((((LINE_G2*)header)->y1 -centerY) * DIVIDE) + centerY;
	  break;

	// LineG4
	case 0x5C:
	  ((LINE_G4*)header)->x0 = ((((LINE_G4*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->y0 = ((((LINE_G4*)header)->y0 -centerY) * DIVIDE) + centerY;
      ((LINE_G4*)header)->x1 = ((((LINE_G4*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->y1 = ((((LINE_G4*)header)->y1 -centerY) * DIVIDE) + centerY;
      ((LINE_G4*)header)->x2 = ((((LINE_G4*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->y2 = ((((LINE_G4*)header)->y2 -centerY) * DIVIDE) + centerY;
      ((LINE_G4*)header)->x3 = ((((LINE_G4*)header)->x3 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->y3 = ((((LINE_G4*)header)->y3 -centerY) * DIVIDE) + centerY;
	  break;
	}
  };
}

void DF_DrawOTag(u_long* ot)
{
	// store in kernel cause whatever
	#define toggle *(int*)0x8000FFF0

	#define R1_SELECT (BTN_R1 | BTN_SELECT)

	int buttonHoldCurr = sdata->gGamepads->
							gamepad[0].buttonsHeldCurrFrame;

	int buttonHoldPrev = sdata->gGamepads->
							gamepad[0].buttonsHeldPrevFrame;

	if(
		// if held this frame, and not previous
		((buttonHoldCurr & R1_SELECT) == R1_SELECT) &&
		((buttonHoldPrev & R1_SELECT) != R1_SELECT)
	  )
	{
		toggle = !toggle;
	}

	if(toggle)
	{
		DF_ParseOT(ot);
	}

	DrawOTag(ot);
}