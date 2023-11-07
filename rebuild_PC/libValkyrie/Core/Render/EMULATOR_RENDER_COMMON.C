#include "LIBGPU.H"
#include "EMULATOR_RENDER_COMMON.H"
#include "Core/EMULATOR_GLOBALS.H"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG_POLY_COUNT
int vram_need_update;

int g_DisableTouchUI;

unsigned short vram[VRAM_WIDTH * VRAM_HEIGHT];

unsigned char rgLUT[LUT_WIDTH * LUT_HEIGHT * sizeof(unsigned int)];

int splitAgain = FALSE;
int64_t g_swapTime;
int g_wireframeMode = 0;
int g_swapInterval = SWAP_INTERVAL;
int g_PreviousBlendMode = BM_NONE;
int windowWidth = 0;
int windowHeight = 0;
unsigned int g_resetDeviceOnNextFrame = FALSE;
unsigned int g_closeOnNextFrame = FALSE;
unsigned int g_resettingDevice = FALSE;

int begin_scene_flag = FALSE;
int vbo_was_dirty_flag = FALSE;

#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)

TextureID* g_lastBoundTexture[2];

ShaderID* g_gte_shader_4;
ShaderID* g_gte_shader_8;
ShaderID* g_gte_shader_16;
ShaderID* g_blit_shader;

TextureID* vramTexture;
TextureID* whiteTexture;
TextureID* rg8lutTexture;
#else
TextureID g_lastBoundTexture[2];

ShaderID g_gte_shader_4;
ShaderID g_gte_shader_8;
ShaderID g_gte_shader_16;
ShaderID g_blit_shader;

TextureID vramTexture;
TextureID whiteTexture;
TextureID rg8lutTexture;
#endif

typedef struct POLY_G3_SEMITRANS 
{
#if defined(USE_32_BIT_ADDR)
	uintptr_t tag;
#if defined(PGXP)
	unsigned short len;
	unsigned short pgxp_index;
#else
	unsigned int len;
#endif
#else
	unsigned long tag;
#endif
	unsigned int dr_tpage; // size=0, offset=4
	unsigned char r0; // size=0, offset=8
	unsigned char g0; // size=0, offset=9
	unsigned char b0; // size=0, offset=10
	unsigned char code; // size=0, offset=11
	short x0; // size=0, offset=12
	short y0; // size=0, offset=14
	unsigned char r1; // size=0, offset=16
	unsigned char g1; // size=0, offset=17
	unsigned char b1; // size=0, offset=18
	unsigned char pad1; // size=0, offset=19
	short x1; // size=0, offset=20
	short y1; // size=0, offset=22
	unsigned char r2; // size=0, offset=24
	unsigned char g2; // size=0, offset=25
	unsigned char b2; // size=0, offset=26
	unsigned char pad2; // size=0, offset=27
	short x2; // size=0, offset=28
	short y2; // size=0, offset=30
} POLY_G3_SEMITRANS;

typedef struct POLY_F4_SEMITRANS
{
#if defined(USE_32_BIT_ADDR)
	uintptr_t tag;
#if defined(PGXP)
	unsigned short len;
	unsigned short pgxp_index;
#else
	unsigned int len;
#endif
#else
	unsigned long tag;
#endif

	unsigned int dr_tpage; // size=0, offset=4
	unsigned char r0; // size=0, offset=8
	unsigned char g0; // size=0, offset=9
	unsigned char b0; // size=0, offset=10
	unsigned char code; // size=0, offset=11
	short x0; // size=0, offset=12
	short y0; // size=0, offset=14
	short x1; // size=0, offset=16
	short y1; // size=0, offset=18
	short x2; // size=0, offset=20
	short y2; // size=0, offset=22
	short x3; // size=0, offset=24
	short y3; // size=0, offset=26
} POLY_F4_SEMITRANS;


#if defined(DEBUG_POLY_COUNT)
static int polygon_count = 0;
#endif

extern int g_emulatorPaused;

struct Vertex g_vertexBuffer[MAX_NUM_POLY_BUFFER_VERTICES];
unsigned short g_indexBuffer[MAX_NUM_INDEX_BUFFER_INDICES];
struct VertexBufferSplit g_splits[MAX_NUM_INDEX_BUFFER_SPLITS];
int g_vertexIndex;
int g_indicesIndex;
int g_splitIndex;
int g_polygonSelected = 0;
unsigned short s_lastSemiTrans = 0xFFFF;
unsigned short s_lastPolyType = 0xFFFF;

#if defined(USE_32_BIT_ADDR)
uintptr_t actualTerminator[2] = { (uintptr_t)-1, (uintptr_t)0};
uintptr_t terminatorOT[2] = { (uintptr_t)&actualTerminator, 0};
#else
unsigned int actualTerminator = -1;
unsigned int terminatorOT = (unsigned int)&actualTerminator;
#endif

int IsValidCode(int code)
{
	return code >= 0x20 && code <= 0x80;
}

extern int splitAgain;

#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
void Emulator_AddSplit(int semiTrans, int page, TextureID* textureId)
#else
void Emulator_AddSplit(int semiTrans, int page, TextureID textureId)
#endif
{
	struct VertexBufferSplit* curSplit = &g_splits[g_splitIndex];
	BlendMode curBlendMode = semiTrans ? GET_TPAGE_BLEND(page) : BM_NONE;
	TexFormat curTexFormat = GET_TPAGE_FORMAT(page);

#if defined(VULKAN)
	if (curSplit->blendMode == curBlendMode && curSplit->texFormat == curTexFormat && curSplit->textureId.textureImage == textureId.textureImage)
#elif defined(D3D12)
	if (curSplit->blendMode == curBlendMode && curSplit->texFormat == curTexFormat && curSplit->textureId.m_textureResource == textureId.m_textureResource)
#elif defined(GXM)
	if (curSplit->blendMode == curBlendMode && curSplit->texFormat == curTexFormat && curSplit->textureId.Uid == textureId.Uid)
#else
	if (curSplit->blendMode == curBlendMode && curSplit->texFormat == curTexFormat && curSplit->textureId == textureId && !splitAgain)
#endif
	{
		return;
	}

	curSplit->vCount = (unsigned short)(g_vertexIndex - curSplit->vIndex);
	curSplit->iCount = (unsigned short)(g_indicesIndex - curSplit->iIndex);

	struct VertexBufferSplit* split = &g_splits[++g_splitIndex];

	split->textureId = textureId;
	split->vIndex = (unsigned short)g_vertexIndex;
	split->iIndex = (unsigned short)g_indicesIndex;
	split->vCount = 0;
	split->iCount = 0;
	split->blendMode = curBlendMode;
	split->texFormat = curTexFormat;
}

void Emulator_MakeIndex(int indexCount)
{
	struct VertexBufferSplit* split = &g_splits[g_splitIndex];

	for (int i = 0; i < indexCount; i += 3)
	{
		g_indexBuffer[g_indicesIndex + 0] = (unsigned short)(split->vCount + split->vIndex + i + 0);
		g_indexBuffer[g_indicesIndex + 1] = (unsigned short)(split->vCount + split->vIndex + i + 1);
		g_indexBuffer[g_indicesIndex + 2] = (unsigned short)(split->vCount + split->vIndex + i + 2);

		g_indicesIndex += 3;
	}
}

void Emulator_MakeTriangle()
{
	g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
	g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex + 0];
	g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];
}

// parses primitive and pushes it to VBO
// returns primitive size
// -1 means invalid primitive
int ParsePrimitive(uintptr_t primPtr, int code)
{
	int textured = (code & 0x4) != 0;

	int blend_mode = 0;

	if (textured)
	{
		if ((code & 0x1) != 0)
		{
			blend_mode = 2;
		}
		else
		{
			blend_mode = 1;
		}
	}
	else
	{
		blend_mode = 0;
	}

#if 0
	//BLK_FILL
	if (pTag->code != 2)
	{
		if (IsValidCode(pTag->code))
		{
			code = pTag->code;
		}
		else
		{
			if (IsValidCode(((POLY_F4_SEMITRANS*)pTag)->code))
			{
				dr_tpage = 1;
				code = ((POLY_F4_SEMITRANS*)pTag)->code;
			}
		}
	}
	else
	{
		
	}
#endif

	int semi_transparent = (code & 2) != 0;

	int primitive_size = -1;	// -1

	switch (code & ~0x3)
	{
	case 0x0:
	{
		switch (code)
		{
		case 0x2:
		{
			//Do black fill
			typedef struct IBLK_FILL
			{
				unsigned char r0;
				unsigned char g0;
				unsigned char b0;
				unsigned char code;
				unsigned short x0;
				unsigned short y0;
				unsigned short w;
				unsigned short h;
			} IBLK_FILL;

			IBLK_FILL* poly = (IBLK_FILL*)primPtr;
			RECT16 clip;
			clip.x = poly->x0;
			clip.y = poly->y0;
			clip.w = poly->w;
			clip.h = poly->h;

#if 1///@FIXME should really draw a dimensional quad here, this is a quick hack because the current quad drawing breaks drawing completely.
			ClearImage(&activeDrawEnv.clip, poly->r0, poly->g0, poly->b0);

#else
			poly->r0 = 255;
			Emulator_AddSplit(FALSE, activeDrawEnv.tpage, whiteTexture);

			struct VertexBufferSplit* split = &g_splits[g_splitIndex];

			short p0[2];
			p0[0] = poly->x0;
			p0[1] = poly->y0;

			short p1[2];
			p1[0] = poly->x0 + poly->w;
			p1[1] = poly->y0;

			short p2[2];
			p2[0] = poly->x0 + poly->w;
			p2[1] = poly->y0 + poly->h;

			short p3[2];
			p3[0] = poly->x0;
			p3[1] = poly->y0 + poly->h;

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], p0, p1, p2, p3);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, FALSE);

			Emulator_MakeTriangle();
			Emulator_MakeIndex(6);

			g_vertexIndex += 6;
#endif
			primitive_size = sizeof(IBLK_FILL);

			return primitive_size;
		}
		default:
		{
			primitive_size = 4;

			break;
		}
		}

		break;
	}
	case 0x20:
	{
		IPOLY_F3* poly = (IPOLY_F3*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, &poly->x2);
		Emulator_GenerateTexcoordArrayTriangleZero(&g_vertexBuffer[split->vCount + split->vIndex], 0);
		Emulator_GenerateColourArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0);

		Emulator_MakeIndex(3);

		g_vertexIndex += 3;

		primitive_size = sizeof(IPOLY_F3);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x24:
	{
		IPOLY_FT3* poly = (IPOLY_FT3*)primPtr;
		activeDrawEnv.tpage = poly->tpage;

		Emulator_AddSplit(semi_transparent, poly->tpage, vramTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, &poly->x2);
		Emulator_GenerateTexcoordArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->u0, &poly->u1, &poly->u2, poly->tpage, poly->clut, GET_TPAGE_DITHER(lastTpage));
		Emulator_GenerateColourArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0);

		Emulator_MakeIndex(3);

		g_vertexIndex += 3;

		primitive_size = sizeof(IPOLY_FT3);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x28:
	{
		IPOLY_F4* poly = (IPOLY_F4*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2);
		Emulator_GenerateTexcoordArrayQuadZero(&g_vertexBuffer[split->vCount + split->vIndex], 0);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, blend_mode == 2);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;
		primitive_size = sizeof(IPOLY_F4);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x2C:
	{
		IPOLY_FT4* poly = (IPOLY_FT4*)primPtr;
		
		activeDrawEnv.tpage = poly->tpage;

		Emulator_AddSplit(semi_transparent, poly->tpage, vramTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, poly->tpage, poly->clut, GET_TPAGE_DITHER(lastTpage));
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, blend_mode == 2);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(IPOLY_FT4);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x30:
	{
		IPOLY_G3* poly = (IPOLY_G3*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, &poly->x2);
		Emulator_GenerateTexcoordArrayTriangleZero(&g_vertexBuffer[split->vCount + split->vIndex], 1);
		Emulator_GenerateColourArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r1, &poly->r2);

		Emulator_MakeIndex(3);

		g_vertexIndex += 3;

		primitive_size = sizeof(IPOLY_G3);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x34:
	{
		IPOLY_GT3* poly = (IPOLY_GT3*)primPtr;

		activeDrawEnv.tpage = poly->tpage;

		Emulator_AddSplit(semi_transparent, poly->tpage, vramTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, &poly->x2);
		Emulator_GenerateTexcoordArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->u0, &poly->u1, &poly->u2, poly->tpage, poly->clut, GET_TPAGE_DITHER(lastTpage));
		Emulator_GenerateColourArrayTriangle(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r1, &poly->r2);

		Emulator_MakeIndex(3);

		g_vertexIndex += 3;

		primitive_size = sizeof(IPOLY_GT3);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x38:
	{
		IPOLY_G4* poly = (IPOLY_G4*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2);
		
		Emulator_GenerateTexcoordArrayQuadZero(&g_vertexBuffer[split->vCount + split->vIndex], 1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(IPOLY_G4);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x3C:
	{
		IPOLY_GT4* poly = (IPOLY_GT4*)primPtr;

		activeDrawEnv.tpage = poly->tpage;

		Emulator_AddSplit(semi_transparent, poly->tpage, vramTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, poly->tpage, poly->clut, GET_TPAGE_DITHER(lastTpage));
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(IPOLY_GT4);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x40:
	{
		ILINE_F2* poly = (ILINE_F2*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateLineArray(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1);
		Emulator_GenerateTexcoordArrayLineZero(&g_vertexBuffer[split->vCount + split->vIndex], 0);
		Emulator_GenerateColourArrayLine(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0);

		Emulator_MakeTriangle();

		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ILINE_F2);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x48: // TODO (unused)
	{
        /*ILINE_F3* poly = (ILINE_F3*)primPtr;
		
					for (int i = 0; i < 2; i++)
					{
						Emulator_AddSplit(POLY_TYPE_LINES, semi_transparent, activeDrawEnv.tpage, whiteTexture);

						if (i == 0)
						{
							//First line
							Emulator_GenerateLineArray(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1, NULL, NULL);
							Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, NULL, NULL, NULL);
							g_vertexIndex += 2;
						}
						else
						{
							//Second line
							Emulator_GenerateLineArray(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x1, &poly->x2, NULL, NULL);
							Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, NULL, NULL, NULL);
							g_vertexIndex += 2;
						}
		#if defined(DEBUG_POLY_COUNT)
						polygon_count++;
		#endif
					}
		*/

		primitive_size = sizeof(ILINE_F3);
		break;
	}
	case 0x50:
	{
		ILINE_G2* poly = (ILINE_G2*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateLineArray(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, &poly->x1);
		Emulator_GenerateTexcoordArrayLineZero(&g_vertexBuffer[split->vCount + split->vIndex], 0);
		Emulator_GenerateColourArrayLine(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r1);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ILINE_G2);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x60:
	{
		ITILE* poly = (ITILE*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, poly->w, poly->h);
		Emulator_GenerateTexcoordArrayQuadZero(&g_vertexBuffer[split->vCount + split->vIndex], 0);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ITILE);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif

		break;
	}
	case 0x64:
	{
		ISPRT* poly = (ISPRT*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, vramTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, poly->w, poly->h);
		Emulator_GenerateTexcoordArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->u0, activeDrawEnv.tpage, poly->clut, poly->w, poly->h);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ISPRT);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x68:
	{
		ITILE_1* poly = (ITILE_1*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, 1, 1);
		Emulator_GenerateTexcoordArrayQuadZero(&g_vertexBuffer[split->vCount + split->vIndex], 0);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ITILE_1);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x70:
	{
		ITILE_8* poly = (ITILE_8*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, 8, 8);
		Emulator_GenerateTexcoordArrayQuadZero(&g_vertexBuffer[split->vCount + split->vIndex], 0);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ITILE_8);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x74:
	{
		ISPRT_8* poly = (ISPRT_8*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, vramTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, 8, 8);
		Emulator_GenerateTexcoordArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->u0, activeDrawEnv.tpage, poly->clut, 8, 8);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ISPRT_8);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x78:
	{
		ITILE_16* poly = (ITILE_16*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, whiteTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, 16, 16);
		Emulator_GenerateTexcoordArrayQuadZero(&g_vertexBuffer[split->vCount + split->vIndex], 0);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ITILE_16);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x7C:
	{
		ISPRT_16* poly = (ISPRT_16*)primPtr;

		Emulator_AddSplit(semi_transparent, activeDrawEnv.tpage, vramTexture);

		struct VertexBufferSplit* split = &g_splits[g_splitIndex];

		Emulator_GenerateVertexArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->x0, 16, 16);
		Emulator_GenerateTexcoordArrayRect(&g_vertexBuffer[split->vCount + split->vIndex], &poly->u0, activeDrawEnv.tpage, poly->clut, 16, 16);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[split->vCount + split->vIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, FALSE);

		Emulator_MakeTriangle();
		Emulator_MakeIndex(6);

		g_vertexIndex += 6;

		primitive_size = sizeof(ISPRT_16);
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0xE0:
	{
		switch (code)
		{
		case 0xE1:
		{
			IDR_TPAGE* dr_tpage = (IDR_TPAGE*)primPtr;
	
			activeDrawEnv.tpage = dr_tpage->code[0] & 0xFFFF;

			primitive_size = sizeof(IDR_TPAGE);

#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		default:
		{
			eprinterr("Primitive type error");
			assert(FALSE);
			break;
		}
		}
		break;
	}
	case 0x80: 
	{
		IDR_MOVE* poly = (IDR_MOVE*)primPtr;
		RECT16 r;
		
		int x = poly->code[1] & 0xFFFF;
		int y = ((poly->code[1] >> 16) & 0xFFFF) & 0x1FF;

		r.x = poly->code[2] & 0xFFFF;
		r.y = ((poly->code[2] >> 16) & 0xFFFF) & 0x1FF;
		
		r.w = poly->code[3] & 0xFFFF;
		r.h = ((poly->code[3] >> 16) & 0xFFFF);
		
		MoveImage(&r, x, y);

		primitive_size = sizeof(IDR_MOVE);

		break;
	}
	default:
	{
		//Unhandled poly type
		eprinterr("Unhandled primitive type: %02X type2:%02X\n", code, code & ~3);
		break;
	}
	}

	return primitive_size;
}


int ParseLinkedPrimitiveList(uintptr_t packetStart, uintptr_t packetEnd)
{
	unsigned long* primitiveHeader = (unsigned long*)packetStart;

	IP_TAG* primitiveTag = (IP_TAG*)primitiveHeader + 2;

	uintptr_t currentAddress = (uintptr_t)primitiveTag;

	int lastSize = -1;

	while (currentAddress != packetEnd)
	{
		lastSize = ParsePrimitive(currentAddress, primitiveTag->code);

		if (lastSize == -1)	// no valid packets submitted
			break;

		currentAddress += lastSize;

		primitiveTag = (IP_TAG*)currentAddress;

		g_splits[g_splitIndex].vCount = (unsigned short)(g_vertexIndex - g_splits[g_splitIndex].vIndex);
		g_splits[g_splitIndex].iCount = (unsigned short)(g_indicesIndex - g_splits[g_splitIndex].iIndex);
	}

	return lastSize;
}

void Emulator_UpdateVBO(int new_start_vertex_index, int new_start_face_index)
{
	g_vertexIndex = new_start_vertex_index;
	g_indicesIndex = new_start_face_index;
}

void Emulator_ClearVBO()
{
	g_vertexIndex = 0;
	g_indicesIndex = 0;
	g_splitIndex = 0;
	g_splits[g_splitIndex].texFormat = (enum TexFormat)0xFFFF;
}

void Emulator_ResetPolyState()
{
	s_lastSemiTrans = 0xFFFF;
	s_lastPolyType = 0xFFFF;
}

#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
ShaderID* Emulator_GetGTEShader(TexFormat texFormat)
#else
ShaderID Emulator_GetGTEShader(TexFormat texFormat)
#endif
{
	switch (texFormat)
	{
	case TF_4_BIT:
		return g_gte_shader_4;
		break;
	case TF_8_BIT:
		return g_gte_shader_8;
		break;
	case TF_16_BIT:
		return g_gte_shader_16;
		break;
	}

	return g_blit_shader;
}

void Emulator_DrawSplit(const struct VertexBufferSplit* split)
{
	Emulator_SetBlendMode(split->blendMode);
	Emulator_SetTextureAndShader(split->textureId, Emulator_GetGTEShader(split->texFormat));

	Emulator_DrawTriangles(split->vIndex, split->iIndex, split->vCount / 3);
}

void Emulator_DrawAggregatedSplits()
{
	if (g_emulatorPaused)
	{
		for (int i = 0; i < 3; i++)
		{
			struct Vertex* vert = &g_vertexBuffer[g_polygonSelected + i];
			vert->r = 255;
			vert->g = 0;
			vert->b = 0;

			eprintf("==========================================\n");
			eprintf("POLYGON: %d\n", i);
			eprintf("X: %d Y: %d\n", vert->x, vert->y);
			eprintf("U: %d V: %d\n", vert->u, vert->v);
			eprintf("TP: %d CLT: %d\n", vert->page, vert->clut);
			eprintf("==========================================\n");
		}

		Emulator_UpdateInput(1);
	}


	
	for (int i = 1; i <= g_splitIndex; i++)
	{
		Emulator_UpdateVertexBuffer(g_vertexBuffer, g_splits[i].vCount, g_splits[i].vIndex, TRUE);
		Emulator_UpdateIndexBuffer(g_indexBuffer, g_splits[i].iCount, g_splits[i].iIndex, TRUE);
	}

	for (int i = 1; i <= g_splitIndex; i++)
	{
		Emulator_DrawSplit(&g_splits[i]);
	}
}

void Emulator_AggregatePTAGsToSplits(unsigned int* p, int singlePrimitive)
{
	if (!p)
		return;

	if (singlePrimitive)
	{
		P_TAG* primitiveTag = (P_TAG*)p;

		uintptr_t currentAddress = NULL;
		
		if ((primitiveTag->code & 0x3))
		{
			currentAddress = (uintptr_t)((char*)primitiveTag + sizeof(uintptr_t) + sizeof(unsigned int));
		}
		else
		{
			currentAddress = (uintptr_t)(primitiveTag + 1);
		}
		// single primitive
		ParsePrimitive(currentAddress, primitiveTag->code);
		
		g_splits[g_splitIndex].vCount = (unsigned short)(g_vertexIndex - g_splits[g_splitIndex].vIndex);
		g_splits[g_splitIndex].iCount = (unsigned short)(g_indicesIndex - g_splits[g_splitIndex].iIndex);
	}
	else
	{
		P_TAG* pTag = (P_TAG*)p;

		// P_TAG as primitive list
		//do
		while ((uintptr_t)pTag != (uintptr_t)&terminatorOT)
		{
			if (pTag->len > 0)
			{
				int lastSize = ParseLinkedPrimitiveList((uintptr_t)pTag, (uintptr_t)pTag + (uintptr_t)(pTag->len * 4) + 4 + LEN_OFFSET);
				if (lastSize == -1)
					break; // safe bailout
			}

			pTag = (P_TAG*)pTag->addr;
		}
	}
}

void* Emulator_GenerateRG8LUT()
{
	for (unsigned short y = 0; y < LUT_HEIGHT; y++)
	{
		unsigned char* row = rgLUT + y * (LUT_HEIGHT * 4);

		for (unsigned short x = 0; x < LUT_WIDTH; x++)
		{
			unsigned short c = (y << 8) | x;

			unsigned char* pixel = row + x * 4;
			pixel[0] = (unsigned char)((c & 0x1F)) << 3;
			pixel[1] = (unsigned char)((c & 0x3E0) >> 5) << 3;
			pixel[2] = (unsigned char)(((c & 0x7C00) >> 10) << 3);
			pixel[3] = (unsigned char)0xFF;
		}
	}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__) && defined(DEBUG_RG8LUT)
	FILE* f = fopen("RG8LUT.TGA", "wb");
	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6];
	header[0] = (LUT_WIDTH % 256);
	header[1] = (LUT_WIDTH / 256);
	header[2] = (LUT_HEIGHT % 256);
	header[3] = (LUT_HEIGHT / 256);
	header[4] = 32;
	header[5] = 0;

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);
	fwrite(rgLUT, sizeof(rgLUT), 1, f);
	fclose(f);
#endif

	return rgLUT;
}

#if defined(TOUCH_UI)

extern unsigned short resultTouchKeysPressed;

void Emulator_DrawTouchUI()
{
#if defined(_WINDOWS)
    g_DisableTouchUI = 1;
#endif

	if (g_DisableTouchUI)
	{
		return;
	}

	unsigned short mapper[4] = {
		0x8,
		0x1,
		0x2,
		0x4,
	};

	unsigned short mapperShoulder[4] = {
		0x1,
		0x4,
		0x2,
		0x8,
	};

#define setlen_ST( p, _len) 	(((POLY_F4_SEMITRANS *)(p))->len  = (u_char)(_len))
#define setcode_ST(p, _code)	(((POLY_F4_SEMITRANS *)(p))->code = (u_char)(_code))
#define setPolyF4_ST(p)	setlen_ST(p, 6),  setcode_ST(p, 0x2A)
#define setAbr(p, abr) ((p)->dr_tpage) |= ((short)abr << 5)

	struct OrderingTable
	{
		uintptr_t addr;
		unsigned int len;
	};

	struct OrderingTable OT[32];
	char polygonBuffer[sizeof(POLY_F4_SEMITRANS) * 32];
	char* p = &polygonBuffer[0];

	ClearOTagR((unsigned int*)&OT[0], 4 / 2);

	int dist = 16;
	int cx = 32;
	int cy = 172;

	for (int i = 0; i < 4; i++)
	{
		int dx = (i % 2) ? 0 : 1;
		int dy = dx ? 0 : 1;
		int ndist = (i >= 2) ? dist : -dist;
		
		int mx = dx ? ndist * 2 : 0;
		int my = dy ? ndist * 2 : 0;
		int pressed = (resultTouchKeysPressed & mapper[i] << 4) != 0;
		
		setDrawTPage((POLY_F4_SEMITRANS*)p, 0, 0, 0x18);
		setPolyF4_ST((POLY_F4_SEMITRANS*)p);
		setRGB0((POLY_F4_SEMITRANS*)p, 127, pressed ? 0 : 127, pressed ? 0 : 127);
		setXY4((POLY_F4_SEMITRANS*)p, cx + mx, cy + my, cx + mx + 32, cy + my, cx + mx, cy + my + 32, cx + mx + 32, cy + my + 32);
		addPrim(OT, p);
		p += sizeof(POLY_F4_SEMITRANS);
	}
	
	cx = 512-64;
	cy = 172;

	for (int i = 0; i < 4; i++)
	{
		int dx = (i % 2) ? 0 : 1;
		int dy = dx ? 0 : 1;
		int ndist = (i >= 2) ? dist : -dist;

		int mx = dx ? ndist * 2 : 0;
		int my = dy ? ndist * 2 : 0;

		int pressed = (resultTouchKeysPressed & mapper[i] << 12) != 0;
		
		setDrawTPage((POLY_F4_SEMITRANS*)p, 0, 0, 0x18);
		setPolyF4_ST((POLY_F4_SEMITRANS*)p);
		setRGB0((POLY_F4_SEMITRANS*)p, 127, pressed ? 0 : 127, pressed ? 0 : 127);
		setXY4((POLY_F4_SEMITRANS*)p, cx + mx, cy + my, cx + mx + 32, cy + my, cx + mx, cy + my + 32, cx + mx + 32, cy + my + 32);
		addPrim(OT, p);
		p += sizeof(POLY_F4_SEMITRANS);
	}

	cx = 512 / 2;
	cy = 240 - 32;
	dist = 32;

	for (int i = 0; i < 2; i++)
	{
		int dx = (i % 2) ? 0 : 1;
		int ndist = (i != 0) ? dist : -dist;

		int mx = dx ? ndist * 2 : 0;

		int pressed = (resultTouchKeysPressed & mapper[!i]) != 0;
		setDrawTPage((POLY_F4_SEMITRANS*)p, 0, 0, 0x18);
		setPolyF4_ST((POLY_F4_SEMITRANS*)p);
		setRGB0((POLY_F4_SEMITRANS*)p, 127, pressed ? 0 : 127, pressed ? 0 : 127);
		setXY4((POLY_F4_SEMITRANS*)p, cx + mx, cy, cx + mx + 32, cy, cx + mx, cy + 16, cx + mx + 32, cy + 16);
		addPrim(OT, p);
		p += sizeof(POLY_F4_SEMITRANS);
	}

	cx = 32;
	cy = 32;

	for (int i = 0; i < 2; i++)
	{
		int dy = (i % 2) ? 0 : 1;
		
		int my = dy ? dist : 0;

		int pressed = (resultTouchKeysPressed & mapperShoulder[i] << 8) != 0;
		setDrawTPage((POLY_F4_SEMITRANS*)p, 0, 0, 0x18);
		setPolyF4_ST((POLY_F4_SEMITRANS*)p);
		setRGB0((POLY_F4_SEMITRANS*)p, 127, pressed ? 0 : 127, pressed ? 0 : 127);
		setXY4((POLY_F4_SEMITRANS*)p, cx, cy + my, cx + 32, cy + my, cx, cy + my + 16, cx + 32, cy + my + 16);
		addPrim(OT, p);
		p += sizeof(POLY_F4_SEMITRANS);
	}

	cx = 512-64;
	cy = 32;

	for (int i = 0; i < 2; i++)
	{
		int dy = (i % 2) ? 0 : 1;

		int my = dy ? dist : 0;

		int pressed = (resultTouchKeysPressed & mapperShoulder[i + 2] << 8) != 0;
		setDrawTPage((POLY_F4_SEMITRANS*)p, 0, 0, 0x18);
		setPolyF4_ST((POLY_F4_SEMITRANS*)p);
		setRGB0((POLY_F4_SEMITRANS*)p, 127, pressed ? 0 : 127, pressed ? 0 : 127);
		setXY4((POLY_F4_SEMITRANS*)p, cx, cy + my, cx + 32, cy + my, cx, cy + my + 16, cx + 32, cy + my + 16);
		addPrim(OT, p);
		p += sizeof(POLY_F4_SEMITRANS);
	}

	Emulator_AggregatePTAGsToSplits((unsigned int*)&OT[0], FALSE);
}

void Emulator_DestroyRender()
{
	Emulator_ResetDevice(FALSE);
}

void Emulator_BlitVRAM()
{
	if (activeDispEnv.isinter)
	{
		//Emulator_StoreFrameBuffer(activeDispEnv.disp.x, activeDispEnv.disp.y, activeDispEnv.disp.w, activeDispEnv.disp.h);
		return;
	}

	Emulator_SetTextureAndShader(vramTexture, Emulator_GetGTEShader(TF_COUNT));
	Emulator_SetBlendMode(BM_NONE);

#if defined(_PATCH2)
	u_char l, t, r, b;

	if (activeDispEnv.disp.x != activeDrawEnv.clip.x || activeDispEnv.disp.y != activeDrawEnv.clip.y)
	{
		l = activeDrawEnv.clip.x / 8;
		t = activeDrawEnv.clip.y / 8;
		r = activeDrawEnv.clip.w / 8 + l;
		b = activeDrawEnv.clip.h / 8 + t;
	}
	else
	{
		l = activeDispEnv.disp.x / 8;
		t = activeDispEnv.disp.y / 8;
		r = activeDispEnv.disp.w / 8 + l;
		b = activeDispEnv.disp.h / 8 + t;
	}
#else
	u_char l = (u_char)(activeDispEnv.disp.x / 8);
	u_char t = (u_char)(activeDispEnv.disp.y / 8);
	u_char r = (u_char)(activeDispEnv.disp.w / 8 + l);
	u_char b = (u_char)(activeDispEnv.disp.h / 8 + t);
#endif

	struct Vertex blit_vertices[] =
	{
		{ +1, +1,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
		{ -1, -1,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ -1, +1,    0, 0,    l, t,    0, 0,    0, 0, 0, 0 },

		{ +1, -1,    0, 0,    r, b,    0, 0,    0, 0, 0, 0 },
		{ -1, -1,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ +1, +1,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
	};

	unsigned short blit_indices[] =
	{
		0, 1, 2,
		3, 5, 4,
	};

#if defined(_PATCH)
	Emulator_SetViewPort(0.0f, 0.0f, windowWidth, windowHeight);
	Emulator_Ortho2D(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
#endif

	Emulator_UpdateVertexBuffer(blit_vertices, sizeof(blit_vertices) / sizeof(Vertex), g_vertexIndex, FALSE);
	Emulator_UpdateIndexBuffer(blit_indices, sizeof(blit_indices) / sizeof(unsigned short), g_indicesIndex, FALSE);

	Emulator_SetWireframe(FALSE);

	Emulator_DrawTriangles(g_vertexIndex, g_indicesIndex, 2);

	g_vertexIndex += 6;
	g_indicesIndex += 6;

	Emulator_SetWireframe(g_wireframeMode);
}

#endif
