#include <common.h>

// at bottom of file
#ifdef USE_ONLINE
extern unsigned int DrawSpeedBG_Colors[11];
extern short speedometerBG_vertData[108];
#else
extern unsigned short DrawSpeedBG_Colors[6*2];
#endif

// speedometer background
void DECOMP_UI_DrawSpeedBG(void)
{
  struct GameTracker* gGT;
  u_int color_gradient0, color_gradient1;
  u_long* ot;
  POLY_G4 *p;
  short* vertData;
  short* upperHalf;
  struct DB* backDB;
  int i, numColors, offset;

  gGT = sdata->gGT;

  #ifdef USE_ONLINE
  vertData = &speedometerBG_vertData;
  upperHalf = &vertData[0];
  #else
  vertData = &data.speedometerBG_vertData;
  upperHalf = &vertData[sizeof(data.speedometerBG_vertData) / (sizeof(short) * 2)];
  #endif
  backDB = gGT->backBuffer;

  #ifdef USE_ONLINE
  numColors = 10;
  #else
  numColors = 6;
  #endif
  #ifdef USE_ONLINE
  offset = 0x1C5;
  #else
  offset = 0x1e0;
  #endif
  for (i = 0; i < numColors + 1; i++)
  {
	// white
    DECOMP_CTR_Box_DrawWirePrims(
		upperHalf[0] + offset, upperHalf[1] + 0xbe,
		upperHalf[2] + offset, upperHalf[3] + 0xbe,
		0xff, 0xff, 0xff,
		gGT->pushBuffer_UI.ptrOT,
		&backDB->primMem);

	// black
    DECOMP_CTR_Box_DrawWirePrims(
		upperHalf[0] + offset + 1, upperHalf[1] + 0xbf,
		upperHalf[2] + offset + 1, upperHalf[3] + 0xbf,
		0, 0, 0,
		gGT->pushBuffer_UI.ptrOT,
		&backDB->primMem);

	upperHalf += 4;
  }

  for (i = 0; i < numColors; i++)
  {
	// white
    DECOMP_CTR_Box_DrawWirePrims(
		vertData[0] + offset, vertData[1] + 0xbe,
		vertData[4] + offset, vertData[5] + 0xbe,
		0xff, 0xff, 0xff,
		gGT->pushBuffer_UI.ptrOT,
		&backDB->primMem);

	// white
    DECOMP_CTR_Box_DrawWirePrims(
		vertData[2] + offset, vertData[3] + 0xbe,
		vertData[6] + offset, vertData[7] + 0xbe,
		0xff, 0xff, 0xff,
		gGT->pushBuffer_UI.ptrOT,
		&backDB->primMem);

	// black
    DECOMP_CTR_Box_DrawWirePrims(
		vertData[0] + offset + 1, vertData[1] + 0xbf,
		vertData[4] + offset + 1, vertData[5] + 0xbf,
		0, 0, 0,
		gGT->pushBuffer_UI.ptrOT,
		&backDB->primMem);

	// black
    DECOMP_CTR_Box_DrawWirePrims(
		vertData[2] + offset + 1, vertData[3] + 0xbf,
		vertData[6] + offset + 1, vertData[7] + 0xbf,
		0, 0, 0,
		gGT->pushBuffer_UI.ptrOT,
		&backDB->primMem);

    // reset prim
    p = backDB->primMem.curr;
    if (p > (u_long *)backDB->primMem.endMin100)
		return;
    backDB->primMem.curr = p + 1;

    #ifdef USE_ONLINE
    color_gradient0 = DrawSpeedBG_Colors[i + 0];
    color_gradient1 = DrawSpeedBG_Colors[i + 1];
    #else
    color_gradient0 = DrawSpeedBG_Colors[i*2 + 0];
    color_gradient1 = DrawSpeedBG_Colors[i*2 + 1];
    #endif

    *(int*)&p->r0 = color_gradient0; // RGB0
    *(int*)&p->r1 = color_gradient0; // RGB1
    *(int*)&p->r2 = color_gradient1; // RGB2
    *(int*)&p->r3 = color_gradient1; // RGB3

    setPolyG4(p);
    setXY4(p,
    vertData[0] + offset, vertData[1] + 0xbe,
    vertData[2] + offset, vertData[3] + 0xbe,
    vertData[4] + offset, vertData[5] + 0xbe,
    vertData[6] + offset, vertData[7] + 0xbe);

	// inline AddPrim
    ot = gGT->pushBuffer_UI.ptrOT;
    *(int*)p = *ot | 0x8000000;
    *ot = (u_int)p & 0xffffff;

	vertData += 4;
  }

  #ifdef USE_ONLINE
  vertData = &speedometerBG_vertData;
  #else
  vertData = &data.speedometerBG_vertData;
  #endif

  for (i = 0; i < numColors; i++)
  {
    p = backDB->primMem.curr;
    if (p > (u_long *)backDB->primMem.endMin100)
		return;
    backDB->primMem.curr = p + 1;

    setlen(p, 8);
    setcode(p, 0xe1);
    setRGB0(p, 0, 0xa, 0);
    setRGB1(p, 0, 0, 0);
    setRGB2(p, 0, 0, 0);
    setRGB3(p, 0, 0, 0);
#ifndef REBUILD_PC
    p->pad0 = 0x32;
#else
	p->pad1 = 0x32; // PsyCross numbers 1,2,3 instead of 0,1,2
#endif
    setXY4(p, 0, 0,
    vertData[2] + offset, vertData[3] + 0xbe,
    vertData[6] + offset, vertData[7] + 0xbe,
    data.speedometerBG_vertData[0x1a] + offset, data.speedometerBG_vertData[3] + 0xbe);

	ot = gGT->pushBuffer_UI.ptrOT;

	// inline AddPrim
    *(int*)p = *ot | 0x8000000;
    *ot = (u_int)p & 0xffffff;

	vertData += 4;
  }
  return;
}

#ifndef USE_ONLINE
#define SPEEDO_GREEN 0xb500
#define SPEEDO_YELLOW 0xd1ff
#define SPEEDO_RED 0xdb

unsigned short DrawSpeedBG_Colors[6*2] =
{
	SPEEDO_GREEN, SPEEDO_GREEN,
	SPEEDO_GREEN, SPEEDO_GREEN,
	SPEEDO_GREEN, SPEEDO_YELLOW,
	SPEEDO_YELLOW, SPEEDO_RED,
	SPEEDO_RED, SPEEDO_RED,
	SPEEDO_RED, SPEEDO_RED
};
#else
#define SPEEDO_GREEN 0x00b500
#define SPEEDO_YELLOW 0x00b5db
#define SPEEDO_RED 0x0000db
#define SPEEDO_VIOLET 0xFF00A1
#define SPEEDO_BLUE 0xF56600
#define SPEEDO_CYAN 0xE6E600
unsigned int DrawSpeedBG_Colors[11] =
{
  SPEEDO_GREEN, SPEEDO_GREEN,
  SPEEDO_GREEN, SPEEDO_YELLOW,
  SPEEDO_RED, SPEEDO_RED,
  SPEEDO_VIOLET, SPEEDO_VIOLET,
  SPEEDO_BLUE, SPEEDO_CYAN,
  SPEEDO_CYAN
};
short speedometerBG_vertData[108] =
{
  WIDE_34(-65), 16, WIDE_34(-54), 13, WIDE_34(-70), 0, WIDE_34(-58), 0,
  WIDE_34(-65), -16, WIDE_34(-54), -13, WIDE_34(-50), -29, WIDE_34(-42), -24,
  WIDE_34(-25), -39, WIDE_34(-21), -32, WIDE_34(0), -42, WIDE_34(0), -35,
  WIDE_34(25), -39, WIDE_34(21), -32, WIDE_34(50), -29, WIDE_34(42), -24,
  WIDE_34(65), -16, WIDE_34(54), -13, WIDE_34(70), 0,    WIDE_34(58), 0,
  WIDE_34(65), 16, WIDE_34(54), 13, WIDE_34(25), 39, WIDE_34(21), 32,
  WIDE_34(50), 29, WIDE_34(42), 24, WIDE_34(-65), 16, WIDE_34(-48), 11,
  WIDE_34(-70), 0, WIDE_34(-51), 0, WIDE_34(-65), -16, WIDE_34(-48), -11,
  WIDE_34(-50), -29, WIDE_34(-37), -21, WIDE_34(-25), -39, WIDE_34(-18), -29,
  WIDE_34(0), -42, WIDE_34(0), -31, WIDE_34(25), -39, WIDE_34(18), -29,
  WIDE_34(50), -29, WIDE_34(37), -21,    WIDE_34(65), -16, WIDE_34(48), -11,
  WIDE_34(70), 0, WIDE_34(51), 0, WIDE_34(65), 16, WIDE_34(48), 11,
  WIDE_34(50), 29, WIDE_34(37), 21, WIDE_34(25), 39, WIDE_34(37), 29,
  WIDE_34(25), -39, WIDE_34(18), -29,
};
#endif