#include <common.h>

#ifdef USE_ONLINE
#define SPEEDO_GREEN MakeColor(0, 0xb5, 0)
#define SPEEDO_YELLOW MakeColor(0xdb, 0xb5, 0)
#define SPEEDO_RED MakeColor(0xdb, 0, 0)
#define SPEEDO_PINK MakeColor(0xd8, 0, 0xcb)
#define SPEEDO_PURPLE MakeColor(0xa4, 0x21, 0xff)
#define SPEEDO_BLUE MakeColor(0x18, 0x18, 0xf3)
const Color DrawSpeedBG_Colors[] =
{
  SPEEDO_GREEN, SPEEDO_GREEN,
  SPEEDO_GREEN, SPEEDO_YELLOW,
  SPEEDO_RED, SPEEDO_RED,
  SPEEDO_RED, SPEEDO_PINK,
  SPEEDO_PURPLE, SPEEDO_PURPLE,
  SPEEDO_BLUE,
};

const Point speedometerData[]=
{
  { .x = WIDE_34(-65), .y = 16 },  { .x = WIDE_34(-54), .y = 13 },
  { .x = WIDE_34(-70), .y = 0 },   { .x = WIDE_34(-58), .y = 0 },
  { .x = WIDE_34(-65), .y = -16 }, { .x = WIDE_34(-54), .y = -13 },
  { .x = WIDE_34(-50), .y = -29 }, { .x = WIDE_34(-42), .y = -24 },
  { .x = WIDE_34(-25), .y = -39 }, { .x = WIDE_34(-21), .y = -32 },
  { .x = WIDE_34(0), .y = -42 },   { .x = WIDE_34(0), .y = -35 },
  { .x = WIDE_34(25), .y = -39 },  { .x = WIDE_34(21), .y = -32 },
  { .x = WIDE_34(50), .y = -29 },  { .x = WIDE_34(42), .y = -24 },
  { .x = WIDE_34(65), .y = -16 },  { .x = WIDE_34(54), .y = -13 },
  { .x = WIDE_34(70), .y = 0 },    { .x = WIDE_34(58), .y = 0 },
  { .x = WIDE_34(65), .y = 16 },   { .x = WIDE_34(54), .y = 13 },
};
#else
#define SPEEDO_GREEN MakeColor(0, 0xb5, 0)
#define SPEEDO_YELLOW MakeColor(0xff, 0xd1, 0)
#define SPEEDO_RED MakeColor(0xdb, 0, 0)

const Color DrawSpeedBG_Colors[7] =
{
	SPEEDO_GREEN, SPEEDO_GREEN,
	SPEEDO_GREEN, SPEEDO_GREEN,
	SPEEDO_YELLOW, SPEEDO_RED,
	SPEEDO_RED,
};
#endif

// speedometer background
void DECOMP_UI_DrawSpeedBG(void)
{
  #ifdef USE_ONLINE
  Point * vertexes = &speedometerData;
  Point * vertexesExtLine = &speedometerData;
  int pointCount = len(speedometerData);
  const short xOffset = 453;
  #else
  Point * vertexes = &data.speedometerBG_vertData[0];
  Point * vertexesExtLine = &data.speedometerBG_vertData[1];
  int pointCount = sizeof(data.speedometerBG_vertData) / (sizeof(Point) * 2);
  const short xOffset = 480;
  #endif
  const short yOffset = 190;

  /* Draw the horizontal lines - they're a bit wider than the speedometer width */
  for (int i = 0; i < pointCount; i += 2)
  {
    Point pt[2];
    pt[0] = MakePoint(vertexesExtLine[i].x + xOffset, vertexesExtLine[i].y + yOffset);
    pt[1] = MakePoint(vertexesExtLine[i + 1].x + xOffset, vertexesExtLine[i + 1].y + yOffset);
    DECOMP_CTR_Box_DrawWirePrims(pt[0], pt[1], MakeColor(0xff, 0xff, 0xff), sdata->gGT->pushBuffer_UI.ptrOT);
    DECOMP_CTR_Box_DrawWirePrims(MakePoint(pt[0].x + 1, pt[0].y + 1), MakePoint(pt[1].x + 1, pt[1].y + 1), MakeColor(0, 0, 0), sdata->gGT->pushBuffer_UI.ptrOT);
  }

  /* Draw the vertical lines and colors */
  int colorIndex = 0;
  for (int i = 0; i < pointCount - 2; i += 2)
  {
    Point pt[4];
    for (int j = 0; j < 4; j++) {
      pt[j] = MakePoint(vertexes[i + j].x + xOffset, vertexes[i + j].y + yOffset);
    }
    DECOMP_CTR_Box_DrawWirePrims(pt[0], pt[2], MakeColor(0xff, 0xff, 0xff), sdata->gGT->pushBuffer_UI.ptrOT);
    DECOMP_CTR_Box_DrawWirePrims(pt[1], pt[3], MakeColor(0xff, 0xff, 0xff), sdata->gGT->pushBuffer_UI.ptrOT);
    DECOMP_CTR_Box_DrawWirePrims(MakePoint(pt[0].x + 1, pt[0].y + 1), MakePoint(pt[2].x + 1, pt[2].y + 1), MakeColor(0, 0, 0), sdata->gGT->pushBuffer_UI.ptrOT);
    DECOMP_CTR_Box_DrawWirePrims(MakePoint(pt[1].x + 1, pt[1].y + 1), MakePoint(pt[3].x + 1, pt[3].y + 1), MakeColor(0, 0, 0), sdata->gGT->pushBuffer_UI.ptrOT);

    PolyG4 * p;
    GetPrimMem(p);
    if (p == nullptr) { return; }

    const PrimCode primCode = { .poly = { .renderCode = RenderCode_Polygon, .gouraud = 1, .quad = 1 } };
    ColorCode colorBottom = DrawSpeedBG_Colors[colorIndex];
    ColorCode colorTop = DrawSpeedBG_Colors[colorIndex + 1];
    ++colorIndex;
    for (int j = 0; j < 2; j++)
    {
      p->v[j].pos = pt[j];
      p->v[j].color = colorBottom;
      p->v[j + 2].pos = pt[j + 2];
      p->v[j + 2].color = colorTop;
    }
    p->gPolyCode = primCode;
    AddPrimitive(p, sdata->gGT->pushBuffer_UI.ptrOT);
  }

  typedef struct TPage_PolyG3
  {
    TPage t;
		PolyG3 p;
  } TPage_PolyG3;

  /* Draw transparent background */
  s16 p2x = vertexes[pointCount - 1].x + xOffset;
  s16 p2y = vertexes[1].y + yOffset;
  for (int i = 0; i < pointCount - 2; i += 2)
  {
    TPage_PolyG3 * p;
    GetPrimMem(p);
    if (p == nullptr) { return; }

    p->t.texpage = (Texpage){ .code = 0xE1, .dither = 1 };
    p->p.tag.self = 0;

    Color color = MakeColor(0, 0, 0);
    const PrimCode primCode = { .poly = { .renderCode = RenderCode_Polygon, .gouraud = 1, .semiTransparency = 1 } };

    for (int j = 0; j < 3; j++) {
      p->p.v[j].color = color;
    }
    p->p.gPolyCode = primCode;

    p->p.v[0].pos.x = vertexes[i + 1].x + xOffset;
    p->p.v[0].pos.y = vertexes[i + 1].y + yOffset;
    p->p.v[1].pos.x = vertexes[i + 3].x + xOffset;
    p->p.v[1].pos.y = vertexes[i + 3].y + yOffset;
    p->p.v[2].pos.x = p2x;
    p->p.v[2].pos.y = p2y;
    AddPrimitive(p, sdata->gGT->pushBuffer_UI.ptrOT);
  }
}