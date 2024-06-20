#ifndef REDHOT_GPU_H
#define REDHOT_GPU_H

#include <macros.h>

typedef union Tag
{
    struct
    {
        u32 addr : 24;
        u32 size : 8;
    };
    u32 self;
} Tag;

/* Primitives */

#define TRI_SIZE  3
#define QUAD_SIZE 4

#define GetPrimitiveMem(pPrim, PrimType, pMem, pEndMem) \
	if (pMem <= pEndMem) { \
		pPrim = (PrimType *) pMem; \
		pMem = pPrim + 1; \
		pPrim->tag.size = (sizeof(PrimType) - sizeof(Tag)) >> 2; \
	} else { pPrim = nullptr; }

#define AddPrimitive(pPrim, pOt) \
    pPrim->tag.addr = ((Tag *)pOt)->addr; \
    ((Tag *)pOt)->addr = (u32) pPrim

#define fPolyCode color.code
#define gPolyCode v[0].color.code
#define polyClut v[0].clut
#define polyTpage v[1].tpage

typedef union Texpage
{
    struct
    {
        u32 x                : 4; /* x * 64 */
        u32 y                : 1; /* y * 256 */
        u32 semiTransparency : 2; /* (0=B/2+F/2, 1=B+F, 2=B-F, 3=B+F/4) */
        u32 texpageColors    : 2; /* (0=4bit, 1=8bit, 2=15bit, 3=Reserved) */
        u32 dither           : 1; /* (0=Off/strip LSBs, 1=24bit to 15bit Dither Enabled) */
        u32 drawDisplayArea  : 1; /* bool */
        u32 y_VRAM_EXP       : 1; /* ununsed in retail */
        u32 texFlipX         : 1; /* bool */
        u32 texFlipY         : 1; /* bool */
        u32 unused           : 10;
        u32 code             : 8; /* 0xE1 */
    };
    u32 self;
} Texpage;

#define RENDER_CODE_POLYGON 1
#define RENDER_CODE_LINE 2
#define RENDER_CODE_RECTANGLE 3

typedef union PolyCode
{
    struct
    {
        u8 rawTex           : 1; /* raw texture / modulation */
        u8 semiTransparency : 1; /* semi-transparent / opaque */
        u8 textured         : 1; /* textured / untextured */
        u8 quad             : 1; /* 4 / 3 vertices */
        u8 gouraud          : 1; /* gouraud / flat shading */
        u8 renderCode       : 3; /* 0b001 = Polygon */
    };
    u8 code;
} PolyCode;

typedef union ColorCode
{
    struct
    {
        u8 r;
        u8 g;
        u8 b;
        PolyCode code;
    };
    u32 self;
} ColorCode;

#define MakeColorCode(red, green, blue, renderCode) (ColorCode){.r = red, .g = green, .b = blue, .code = renderCode}

typedef union Point
{
    struct
    {
        s16 x;
        s16 y;
    };
    s32 self;
} Point;

typedef union UV
{
    struct
    {
        u8 u;
        u8 v;
    };
    u16 self;
} UV;

typedef union PolyTexpage
{
    struct
    {
        u16 x                : 4; /* x * 64 */
        u16 y                : 1; /* y * 256 */
        u16 semiTransparency : 2; /* (0=B/2+F/2, 1=B+F, 2=B-F, 3=B+F/4) */
        u16 texpageColors    : 2; /* (0=4bit, 1=8bit, 2=15bit, 3=Reserved) */
        u16 unused           : 2;
        u16 y_VRAM_EXP       : 1; /* ununsed in retail */
        u16 unused2          : 2;
        u16 nop              : 2;
    };
    u16 self;
} PolyTexpage;

typedef union CLUT
{
    struct
    {
        u16 x   : 6; /* X/16  (ie. in 16-halfword steps) */
        u16 y   : 9; /* 0-511 (ie. in 1-line steps) */
        u16 nop : 1; /* Should be 0 */
    };
    u16 self;
} CLUT;

/* Vertex types */

typedef struct FVertex
{
	Point pos;
} FVertex;

typedef struct GVertex
{
    ColorCode color;
    Point pos;
} GVertex;

typedef struct FTVertex
{
    Point pos;
    UV texCoords;
    union
    {
        CLUT clut;
        PolyTexpage tpage;
    };
} FTVertex;

typedef struct GTVertex
{
    ColorCode color;
    Point pos;
    UV texCoords;
    union
    {
        CLUT clut;
        PolyTexpage tpage;
    };
} GTVertex;

/* Primitive types */

typedef struct PolyG3
{
    Tag tag;
    GVertex v[TRI_SIZE];
} PolyG3;

typedef struct PolyG4
{
    Tag tag;
    GVertex v[QUAD_SIZE];
} PolyG4;

typedef struct PolyGT3
{
    Tag tag;
    GTVertex v[TRI_SIZE];
} PolyGT3;

typedef struct PolyGT4
{
    Tag tag;
    GTVertex v[QUAD_SIZE];
} PolyGT4;

typedef struct PolyF3
{
	Tag tag;
	ColorCode colorCode;
	FVertex v[TRI_SIZE];
} PolyF3;

typedef struct PolyF4
{
	Tag tag;
	ColorCode colorCode;
	FVertex v[QUAD_SIZE];
} PolyF4;

typedef struct PolyFT3
{
    Tag tag;
    ColorCode colorCode;
    FTVertex v[TRI_SIZE];
} PolyFT3;

typedef struct PolyFT4
{
    Tag tag;
    ColorCode colorCode;
    FTVertex v[QUAD_SIZE];
} PolyFT4;

#endif