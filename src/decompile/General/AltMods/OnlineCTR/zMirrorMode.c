#include <common.h>
#include "global.h"

#define COLOR 1
void ParseOT(u_long* startOT)
{
  u_int* header;

  int screenX;
  int screenY;
  int centerX;
  int centerY;
  int backup;

  unsigned int endOT;
  int windowWidth;

  struct GameTracker* gGT = sdata->gGT;

  // if TitleFlag is drawn in background
  if(RaceFlag_IsFullyOnScreen() == 1)
  {
	// dont flip TitleFlag
	startOT-=4;
  }

  // stop when ptrOT-4 is in tag, so ptrOT-0 is flipped
  endOT = (unsigned int)gGT->pushBuffer[gGT->numPlyrCurrGame-1].ptrOT-4;

  windowWidth = gGT->pushBuffer[0].rect.w;

  // divide by two (more zoom out)
  // #define DIVIDE 0x200 >> 0xc

  // divide by four (original from june 1999)
  // #define DIVIDE 0x400 >> 0xc

  // divide by eight (less zoom out)
  #define DIVIDE 0x800 >> 0xc

  // original resolution
  screenX = 0x200;
  screenY = 0xd8;

  // center
  centerX = screenX >> 1;
  centerY = screenY >> 1;

  // start at beginning of OT
  header = (u_int*)startOT;

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
    if (header == endOT) break;

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
      ((POLY_F3*)header)->x0 = (windowWidth - ((POLY_F3*)header)->x0);
      ((POLY_F3*)header)->x1 = (windowWidth - ((POLY_F3*)header)->x1);
      ((POLY_F3*)header)->x2 = (windowWidth - ((POLY_F3*)header)->x2);
	  backup = ((POLY_F3*)header)->x0;
	  ((POLY_F3*)header)->x0 = ((POLY_F3*)header)->x1;
	  ((POLY_F3*)header)->x1 = backup;
	  backup = ((POLY_F3*)header)->y0;
	  ((POLY_F3*)header)->y0 = ((POLY_F3*)header)->y1;
	  ((POLY_F3*)header)->y1 = backup;
      break;

	// 0x24 PolyFT3
    case 0x24:
      ((POLY_FT3*)header)->x0 = (windowWidth - ((POLY_FT3*)header)->x0);
      ((POLY_FT3*)header)->x1 = (windowWidth - ((POLY_FT3*)header)->x1);
      ((POLY_FT3*)header)->x2 = (windowWidth - ((POLY_FT3*)header)->x2);
	  backup = ((POLY_FT3*)header)->x0;
	  ((POLY_FT3*)header)->x0 = ((POLY_FT3*)header)->x1;
	  ((POLY_FT3*)header)->x1 = backup;
	  backup = ((POLY_FT3*)header)->y0;
	  ((POLY_FT3*)header)->y0 = ((POLY_FT3*)header)->y1;
	  ((POLY_FT3*)header)->y1 = backup;
	  backup = ((POLY_FT3*)header)->u0;
	  ((POLY_FT3*)header)->u0 = ((POLY_FT3*)header)->u1;
	  ((POLY_FT3*)header)->u1 = backup;
	  backup = ((POLY_FT3*)header)->v0;
	  ((POLY_FT3*)header)->v0 = ((POLY_FT3*)header)->v1;
	  ((POLY_FT3*)header)->v1 = backup;
      break;

	// 0x30 PolyG3
    case 0x30:
      ((POLY_G3*)header)->x0 = (windowWidth - ((POLY_G3*)header)->x0);
      ((POLY_G3*)header)->x1 = (windowWidth - ((POLY_G3*)header)->x1);
      ((POLY_G3*)header)->x2 = (windowWidth - ((POLY_G3*)header)->x2);
	  backup = ((POLY_G3*)header)->x0;
	  ((POLY_G3*)header)->x0 = ((POLY_G3*)header)->x1;
	  ((POLY_G3*)header)->x1 = backup;
	  backup = ((POLY_G3*)header)->y0;
	  ((POLY_G3*)header)->y0 = ((POLY_G3*)header)->y1;
	  ((POLY_G3*)header)->y1 = backup;
#if COLOR
	  backup = ((POLY_G3*)header)->r0;
	  ((POLY_G3*)header)->r0 = ((POLY_G3*)header)->r1;
	  ((POLY_G3*)header)->r1 = backup;
	  backup = ((POLY_G3*)header)->g0;
	  ((POLY_G3*)header)->g0 = ((POLY_G3*)header)->g1;
	  ((POLY_G3*)header)->g1 = backup;
	  backup = ((POLY_G3*)header)->b0;
	  ((POLY_G3*)header)->b0 = ((POLY_G3*)header)->b1;
	  ((POLY_G3*)header)->b1 = backup;
#endif
      break;

	// 0x28 PolyF4
	// 0x4c LineF4
    case 0x28:
    case 0x4c:
      ((POLY_F4*)header)->x0 = (windowWidth - ((POLY_F4*)header)->x0);
      ((POLY_F4*)header)->x1 = (windowWidth - ((POLY_F4*)header)->x1);
      ((POLY_F4*)header)->x2 = (windowWidth - ((POLY_F4*)header)->x2);
      ((POLY_F4*)header)->x3 = (windowWidth - ((POLY_F4*)header)->x3);
	  backup = ((POLY_F4*)header)->x0;
	  ((POLY_F4*)header)->x0 = ((POLY_F4*)header)->x3;
	  ((POLY_F4*)header)->x3 = backup;
	  backup = ((POLY_F4*)header)->x1;
	  ((POLY_F4*)header)->x1 = ((POLY_F4*)header)->x2;
	  ((POLY_F4*)header)->x2 = backup;
	  backup = ((POLY_F4*)header)->y0;
	  ((POLY_F4*)header)->y0 = ((POLY_F4*)header)->y3;
	  ((POLY_F4*)header)->y3 = backup;
	  backup = ((POLY_F4*)header)->y1;
	  ((POLY_F4*)header)->y1 = ((POLY_F4*)header)->y2;
	  ((POLY_F4*)header)->y2 = backup;
      break;

	// 0x38 PolyG4
    case 0x38:
      ((POLY_G4*)header)->x0 = (windowWidth - ((POLY_G4*)header)->x0);
      ((POLY_G4*)header)->x1 = (windowWidth - ((POLY_G4*)header)->x1);
      ((POLY_G4*)header)->x2 = (windowWidth - ((POLY_G4*)header)->x2);
      ((POLY_G4*)header)->x3 = (windowWidth - ((POLY_G4*)header)->x3);
	  backup = ((POLY_G4*)header)->x0;
	  ((POLY_G4*)header)->x0 = ((POLY_G4*)header)->x3;
	  ((POLY_G4*)header)->x3 = backup;
	  backup = ((POLY_G4*)header)->x1;
	  ((POLY_G4*)header)->x1 = ((POLY_G4*)header)->x2;
	  ((POLY_G4*)header)->x2 = backup;
	  backup = ((POLY_G4*)header)->y0;
	  ((POLY_G4*)header)->y0 = ((POLY_G4*)header)->y3;
	  ((POLY_G4*)header)->y3 = backup;
	  backup = ((POLY_G4*)header)->y1;
	  ((POLY_G4*)header)->y1 = ((POLY_G4*)header)->y2;
	  ((POLY_G4*)header)->y2 = backup;
#if COLOR
	  backup = ((POLY_G4*)header)->r0;
	  ((POLY_G4*)header)->r0 = ((POLY_G4*)header)->r3;
	  ((POLY_G4*)header)->r3 = backup;
	  backup = ((POLY_G4*)header)->r1;
	  ((POLY_G4*)header)->r1 = ((POLY_G4*)header)->r2;
	  ((POLY_G4*)header)->r2 = backup;
	  backup = ((POLY_G4*)header)->g0;
	  ((POLY_G4*)header)->g0 = ((POLY_G4*)header)->g3;
	  ((POLY_G4*)header)->g3 = backup;
	  backup = ((POLY_G4*)header)->g1;
	  ((POLY_G4*)header)->g1 = ((POLY_G4*)header)->g2;
	  ((POLY_G4*)header)->g2 = backup;
	  backup = ((POLY_G4*)header)->b0;
	  ((POLY_G4*)header)->b0 = ((POLY_G4*)header)->b3;
	  ((POLY_G4*)header)->b3 = backup;
	  backup = ((POLY_G4*)header)->b1;
	  ((POLY_G4*)header)->b1 = ((POLY_G4*)header)->b2;
	  ((POLY_G4*)header)->b2 = backup;
#endif
	  break;

	// 0x2C PolyFT4
    case 0x2c:
      ((POLY_FT4*)header)->x0 = (windowWidth - ((POLY_FT4*)header)->x0);
      ((POLY_FT4*)header)->x1 = (windowWidth - ((POLY_FT4*)header)->x1);
      ((POLY_FT4*)header)->x2 = (windowWidth - ((POLY_FT4*)header)->x2);
      ((POLY_FT4*)header)->x3 = (windowWidth - ((POLY_FT4*)header)->x3);
	  backup = ((POLY_FT4*)header)->x0;
	  ((POLY_FT4*)header)->x0 = ((POLY_FT4*)header)->x3;
	  ((POLY_FT4*)header)->x3 = backup;
	  backup = ((POLY_FT4*)header)->x1;
	  ((POLY_FT4*)header)->x1 = ((POLY_FT4*)header)->x2;
	  ((POLY_FT4*)header)->x2 = backup;
	  backup = ((POLY_FT4*)header)->y0;
	  ((POLY_FT4*)header)->y0 = ((POLY_FT4*)header)->y3;
	  ((POLY_FT4*)header)->y3 = backup;
	  backup = ((POLY_FT4*)header)->y1;
	  ((POLY_FT4*)header)->y1 = ((POLY_FT4*)header)->y2;
	  ((POLY_FT4*)header)->y2 = backup;
	  backup = ((POLY_FT4*)header)->u0;
	  ((POLY_FT4*)header)->u0 = ((POLY_FT4*)header)->u3;
	  ((POLY_FT4*)header)->u3 = backup;
	  backup = ((POLY_FT4*)header)->u1;
	  ((POLY_FT4*)header)->u1 = ((POLY_FT4*)header)->u2;
	  ((POLY_FT4*)header)->u2 = backup;
	  backup = ((POLY_FT4*)header)->v0;
	  ((POLY_FT4*)header)->v0 = ((POLY_FT4*)header)->v3;
	  ((POLY_FT4*)header)->v3 = backup;
	  backup = ((POLY_FT4*)header)->v1;
	  ((POLY_FT4*)header)->v1 = ((POLY_FT4*)header)->v2;
	  ((POLY_FT4*)header)->v2 = backup;
	  break;

	// PolyGT3
    case 0x34:
      ((POLY_GT3*)header)->x0 = (windowWidth - ((POLY_GT3*)header)->x0);
      ((POLY_GT3*)header)->x1 = (windowWidth - ((POLY_GT3*)header)->x1);
      ((POLY_GT3*)header)->x2 = (windowWidth - ((POLY_GT3*)header)->x2);
	  backup = ((POLY_GT3*)header)->x0;
	  ((POLY_GT3*)header)->x0 = ((POLY_GT3*)header)->x1;
	  ((POLY_GT3*)header)->x1 = backup;
	  backup = ((POLY_GT3*)header)->y0;
	  ((POLY_GT3*)header)->y0 = ((POLY_GT3*)header)->y1;
	  ((POLY_GT3*)header)->y1 = backup;
	  backup = ((POLY_GT3*)header)->u0;
	  ((POLY_GT3*)header)->u0 = ((POLY_GT3*)header)->u1;
	  ((POLY_GT3*)header)->u1 = backup;
	  backup = ((POLY_GT3*)header)->v0;
	  ((POLY_GT3*)header)->v0 = ((POLY_GT3*)header)->v1;
	  ((POLY_GT3*)header)->v1 = backup;
#if COLOR
	  backup = ((POLY_GT3*)header)->r0;
	  ((POLY_GT3*)header)->r0 = ((POLY_GT3*)header)->r1;
	  ((POLY_GT3*)header)->r1 = backup;
	  backup = ((POLY_GT3*)header)->g0;
	  ((POLY_GT3*)header)->g0 = ((POLY_GT3*)header)->g1;
	  ((POLY_GT3*)header)->g1 = backup;
	  backup = ((POLY_GT3*)header)->b0;
	  ((POLY_GT3*)header)->b0 = ((POLY_GT3*)header)->b1;
	  ((POLY_GT3*)header)->b1 = backup;
#endif
	  break;

	// PolyGT4
    case 0x3c:
      ((POLY_GT4*)header)->x0 = (windowWidth - ((POLY_GT4*)header)->x0);
      ((POLY_GT4*)header)->x1 = (windowWidth - ((POLY_GT4*)header)->x1);
      ((POLY_GT4*)header)->x2 = (windowWidth - ((POLY_GT4*)header)->x2);
      ((POLY_GT4*)header)->x3 = (windowWidth - ((POLY_GT4*)header)->x3);
	  backup = ((POLY_GT4*)header)->x0;
	  ((POLY_GT4*)header)->x0 = ((POLY_GT4*)header)->x3;
	  ((POLY_GT4*)header)->x3 = backup;
	  backup = ((POLY_GT4*)header)->x1;
	  ((POLY_GT4*)header)->x1 = ((POLY_GT4*)header)->x2;
	  ((POLY_GT4*)header)->x2 = backup;
	  backup = ((POLY_GT4*)header)->y0;
	  ((POLY_GT4*)header)->y0 = ((POLY_GT4*)header)->y3;
	  ((POLY_GT4*)header)->y3 = backup;
	  backup = ((POLY_GT4*)header)->y1;
	  ((POLY_GT4*)header)->y1 = ((POLY_GT4*)header)->y2;
	  ((POLY_GT4*)header)->y2 = backup;
	  backup = ((POLY_GT4*)header)->u0;
	  ((POLY_GT4*)header)->u0 = ((POLY_GT4*)header)->u3;
	  ((POLY_GT4*)header)->u3 = backup;
	  backup = ((POLY_GT4*)header)->u1;
	  ((POLY_GT4*)header)->u1 = ((POLY_GT4*)header)->u2;
	  ((POLY_GT4*)header)->u2 = backup;
	  backup = ((POLY_GT4*)header)->v0;
	  ((POLY_GT4*)header)->v0 = ((POLY_GT4*)header)->v3;
	  ((POLY_GT4*)header)->v3 = backup;
	  backup = ((POLY_GT4*)header)->v1;
	  ((POLY_GT4*)header)->v1 = ((POLY_GT4*)header)->v2;
	  ((POLY_GT4*)header)->v2 = backup;
#if COLOR
	  backup = ((POLY_GT4*)header)->r0;
	  ((POLY_GT4*)header)->r0 = ((POLY_GT4*)header)->r3;
	  ((POLY_GT4*)header)->r3 = backup;
	  backup = ((POLY_GT4*)header)->r1;
	  ((POLY_GT4*)header)->r1 = ((POLY_GT4*)header)->r2;
	  ((POLY_GT4*)header)->r2 = backup;
	  backup = ((POLY_GT4*)header)->g0;
	  ((POLY_GT4*)header)->g0 = ((POLY_GT4*)header)->g3;
	  ((POLY_GT4*)header)->g3 = backup;
	  backup = ((POLY_GT4*)header)->g1;
	  ((POLY_GT4*)header)->g1 = ((POLY_GT4*)header)->g2;
	  ((POLY_GT4*)header)->g2 = backup;
	  backup = ((POLY_GT4*)header)->b0;
	  ((POLY_GT4*)header)->b0 = ((POLY_GT4*)header)->b3;
	  ((POLY_GT4*)header)->b3 = backup;
	  backup = ((POLY_GT4*)header)->b1;
	  ((POLY_GT4*)header)->b1 = ((POLY_GT4*)header)->b2;
	  ((POLY_GT4*)header)->b2 = backup;
#endif
	  break;

	// LineF2
    case 0x40:
      ((LINE_F2*)header)->x0 = (windowWidth - ((LINE_F2*)header)->x0);
      ((LINE_F2*)header)->x1 = (windowWidth - ((LINE_F2*)header)->x1);
	  break;

	// LineG2
    case 0x50:
      ((LINE_G2*)header)->x0 = (windowWidth - ((LINE_G2*)header)->x0);
      ((LINE_G2*)header)->x1 = (windowWidth - ((LINE_G2*)header)->x1);
	  break;

	// does this even exist?
	#if 0
	// LineG4
	case 0x5C:
	  ((LINE_G4*)header)->x0 = ((((LINE_G4*)header)->x0 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->x1 = ((((LINE_G4*)header)->x1 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->x2 = ((((LINE_G4*)header)->x2 -centerX) * DIVIDE) + centerX;
      ((LINE_G4*)header)->x3 = ((((LINE_G4*)header)->x3 -centerX) * DIVIDE) + centerX;
	  break;
	#endif
	default:
		break;
	}
  };
}

void SwapDirection(u_int toggle)
{
	char normal[] = {BTN_LEFT, BTN_RIGHT};
	char swap[] = {BTN_RIGHT, BTN_LEFT};
	for (char i = 0; i < 2; i++)
		data.gamepadMapBtn[i + 2].output = (toggle) ? swap[i] : normal[i];
}

void OnlineMirrorMode(u_long* startOT)
{
	// restore default
	data.hud_1P_P1[0xC].x = 286;
	// do NOT set 2p3p4p, this is online only

	SwapDirection(0);

	// Mirror Mode Disabled
	#if 0
	// no special event
	if (octr->special == 0)
	#endif	
	
		return;

	// no mirroring on this track
	if (sdata->gGT->levelID >= INTRO_RACE_TODAY)
		return;

	// flip the wumpa shine manually
	// I know this sucks, whatever
	data.hud_1P_P1[0xC].x = 0xAA;
	// do NOT set 2p3p4p, this is online only

	SwapDirection(1);

	ParseOT(startOT);
}