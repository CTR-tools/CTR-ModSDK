#include "LIBGPU.H"
#include "Core/EMULATOR.H"
#include "Core/EMULATOR_GLOBALS.H"
#include "Core/Public/EMULATOR_PUBLIC.H"

#include <stdint.h>

#include "LIBETC.H"


DISPENV activeDispEnv;
DRAWENV activeDrawEnv;	// word_33BC
DRAWENV byte_9CCA4;
int dword_3410 = 0;
char byte_3352 = 0;
int g_blitAfterDrawPrim = 1;

#if defined(USE_32_BIT_ADDR)

struct OrderingTable
{
	uintptr_t addr;
	unsigned int len;
};

extern uintptr_t terminatorOT[];

#else
extern unsigned int terminatorOT = -1;
#endif

extern int g_splitIndex;

//#define WIREFRAME_MODE

static char unk_1B00[1024];//unk_1B00
static char unk_1F00[16384];//unk_1F00
static unsigned int fontStreamCount = 0;//dword_E80
static unsigned int fontCurrentStream = 0;//dword_E84
static unsigned int fontUsedCharacterCount = 0;//dword_1888
static DR_MODE fontMode = { 0, 0, 0, 0 };//unk_D10
static unsigned short fontTpage = getTPage(2, 0, 0, 0);//word_5F00
static unsigned short fontClut = getClut(960, 384);//word_5F02
#define MAX_NUM_FONT_STREAMS (8)
#define MAX_FONT_CHARACTER_COUNT (1024)

#pragma pack(push,1)

struct Font
{
	TILE tile;
	unsigned int unk01;
	unsigned int unk02;
	unsigned int characterCount;
	SPRT_8* pSprites;
	char* unk05;
	unsigned int unk06;
	unsigned int unk07;
};

#pragma pack(pop)

struct Font font[MAX_NUM_FONT_STREAMS];//dword_D00

void(*drawsync_callback)(void) = NULL;

void* off_3348[] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

int ClearImage(RECT16* rect, u_char r, u_char g, u_char b)
{
	Emulator_Clear(rect->x, rect->y, rect->w, rect->h, r, g, b);
	return 0;
}

int ClearImage2(RECT16* rect, u_char r, u_char g, u_char b)
{
	Emulator_Clear(rect->x, rect->y, rect->w, rect->h, r, g, b);
	return 0;
}

int DrawSync(int mode)
{
#if defined(D3D12)
	int closeBuffer = FALSE;
	if (!begin_commands_flag)
	{
		Emulator_BeginCommandBuffer();
		closeBuffer = TRUE;
	}
#endif

	// Update VRAM seems needed to be here
	Emulator_UpdateVRAM();

#if defined(D3D12)
	if (closeBuffer == TRUE)
	{
		Emulator_EndCommandBuffer();
	}
#endif

	if (drawsync_callback != NULL)
	{
		drawsync_callback();
	}

#if !defined(VULKAN)
	if (g_splitIndex > 1) // don't do flips if nothing to draw.
	{
		Emulator_EndScene();
	}
#endif

	VSync(0);

	return 0;
}

int LoadImagePSX(RECT16* rect, unsigned int* p)
{
	Emulator_CopyVRAM((unsigned short*)p, 0, 0, rect->w, rect->h, rect->x, rect->y);
	return 0;
}

int MargePrim(void* p0, void* p1)
{
#if defined(USE_32_BIT_ADDR)
	int v0 = ((int*)p0)[1];
	int v1 = ((int*)p1)[1];
#else
	int v0 = ((unsigned char*)p0)[3];
	int v1 = ((unsigned char*)p1)[3];
#endif

	v0 += v1;
	v1 = v0 + 1;

#if defined(USE_32_BIT_ADDR)
	if (v1 < 0x12)
#else
	if (v1 < 0x11)
#endif
	{
#if defined(USE_32_BIT_ADDR)
		((int*)p0)[1] = v1;
		((int*)p1)[1] = 0;
#else
		((char*)p0)[3] = v1;
		((int*)p1)[0] = 0;
#endif

		return 0;
	}

	return -1;
}

int MoveImage(RECT16* rect, int x, int y)
{
	Emulator_CopyVRAM(NULL, x, y, rect->w, rect->h, rect->x, rect->y);
	return 0;
}

int ResetGraph(int mode)
{
	UNIMPLEMENTED();
	return 0;
}

int SetGraphDebug(int level)
{
	UNIMPLEMENTED();
	return 0;
}

int StoreImage(RECT16* rect, u_long* p)
{
	Emulator_ReadVRAM((unsigned short*)p, rect->x, rect->y, rect->w, rect->h);
	return 0;
}

unsigned int* ClearOTag(unsigned int* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

	//last is special terminator
#if defined(USE_32_BIT_ADDR)
	setaddr(&ot[n - 2], &terminatorOT);
	setlen(&ot[n - 2], 0);
#else
	setaddr(&ot[n - 1], &terminatorOT);
	setlen(&ot[n - 1], 0);
#endif


#if defined(USE_32_BIT_ADDR)
	for (int i = n - 4; i >= 0; i -= 2)
#else
	for (int i = n - 2; i >= 0; i--)
#endif
	{
#if defined(USE_32_BIT_ADDR)
		setaddr(&ot[i], (unsigned long)&ot[i + 2]);
#else
		setaddr(&ot[i], (unsigned long)&ot[i + 1]);
#endif
	}

	return NULL;
}

unsigned int* ClearOTagR(unsigned int* ot, int n)
{
	struct OrderingTable* ordt = (struct OrderingTable*)ot;

	//Nothing to do here.
	if (n == 0)
		return NULL;

	//First is special terminator
	setaddr(ordt, &terminatorOT);

	setlen(ordt, 0);

#if defined(USE_32_BIT_ADDR)
	for (int i = 1; i < n; i++)
#else
	for (int i = 1; i < n; i++)
#endif
	{
#if defined(USE_32_BIT_ADDR)
		setaddr(&ordt[i], (uintptr_t)&ordt[i - 1]);
#else
		setaddr(&ot[i], (uintptr_t)&ot[i - 1]);
#endif
		setlen(&ordt[i], 0);
	}

	return NULL;
}

void SetDispMask(int mask)
{
	UNIMPLEMENTED();
}

int FntPrint(char* text, ...)
{
	UNIMPLEMENTED();
	return 0;
}

DISPENV* GetDispEnv(DISPENV* env)//(F)
{
	memcpy(env, &activeDispEnv, sizeof(DISPENV));
	return env;
}

DISPENV* PutDispEnv(DISPENV* env)//To Finish
{
	memcpy((char*)&activeDispEnv, env, sizeof(DISPENV));
	return 0;
}

DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h)//(F)
{
	env->disp.x = x;
	env->disp.y = y;
	env->disp.w = w;
	env->screen.x = 0;
	env->screen.y = 0;
	env->screen.w = 0;
	env->screen.h = 0;
	env->isrgb24 = 0;
	env->isinter = 0;
	env->pad1 = 0;
	env->pad0 = 0;
	env->disp.h = h;
	return 0;
}

DRAWENV* GetDrawEnv(DRAWENV* env)
{
	UNIMPLEMENTED();
	return NULL;
}

DRAWENV* PutDrawEnv(DRAWENV* env)//Guessed
{
	memcpy((char*)&activeDrawEnv, env, sizeof(DRAWENV));
	return 0;
}

DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h)//(F)
{
	env->clip.x = x;
	env->clip.y = y;
	env->clip.w = w;
	env->tw.x = 0;
	env->tw.y = 0;
	env->tw.w = 0;
	env->tw.h = 0;
	env->r0 = 0;
	env->g0 = 0;
	env->b0 = 0;
	env->dtd = 1;
	env->clip.h = h;

	if (GetVideoMode() == 0)
	{
		env->dfe = h < 0x121 ? 1 : 0;
	}
	else
	{
		env->dfe = h < 0x101 ? 1 : 0;
	}

	env->ofs[0] = x;
	env->ofs[1] = y;

	env->tpage = 10;
	env->isbg = 0;

	return env;
}

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env)
{

}

void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT16* tw)
{
	setDrawMode(p, dfe, dtd, tpage, tw);
}

void SetDrawMove(DR_MOVE* p, RECT16* rect, int x, int y)
{
	char uVar1;
	ulong uVar2;
	
	uVar1 = 5;
	if ((rect->w == 0) || (rect->h == 0)) {
		uVar1 = 0;
	}
	p->code[0] = 0x1000000;
	p->code[1] = 0x80000000;
	*(char *)((intptr_t)&p->tag + 3) = uVar1;
	uVar2 = *(ulong *)rect;
	p->code[3] = y << 0x10 | x & 0xffffU;
	p->code[2] = uVar2;
	p->code[4] = *(ulong *)&rect->w;
}

u_long DrawSyncCallback(void(*func)(void))
{
	drawsync_callback = func;
	return 0;
}

u_short GetClut(int x, int y)
{
	return getClut(x, y);
}

void DrawOTagEnv(unsigned int* p, DRAWENV* env)
{
	do
	{
		PutDrawEnv(env);
		DrawOTag(p);
	} while (g_emulatorPaused);

#if defined(PGXP)
	Emulator_ResetPGXPCache();
#endif
}

void DrawOTag(unsigned int* p)
{
	VSync(0);

	if (Emulator_BeginScene())
	{
		Emulator_ClearVBO();

		Emulator_ResetPolyState();

#if defined(UWP)
		//Emulator_SetDefaultRenderTarget();
#endif
	}

#if defined(DEBUG_POLY_COUNT)
	polygon_count = 0;
#endif

	if (activeDrawEnv.isbg)
	{
		ClearImage(&activeDrawEnv.clip, activeDrawEnv.r0, activeDrawEnv.g0, activeDrawEnv.b0);
	}
	else
	{
		Emulator_BlitVRAM();
	}

	Emulator_AggregatePTAGsToSplits(p, FALSE);

	Emulator_DrawTouchUI();

	Emulator_DrawAggregatedSplits();

	Emulator_EndScene();

#if defined(PGXP)
	Emulator_ResetPGXPCache();
#endif
}

void DrawPrim(void* p)
{
	VSync(0);

	if (Emulator_BeginScene())
	{
		Emulator_ClearVBO();

		Emulator_ResetPolyState();

#if defined(UWP)
		//Emulator_SetDefaultRenderTarget();
#endif

		if (activeDrawEnv.isbg)
		{
			ClearImage(&activeDrawEnv.clip, activeDrawEnv.r0, activeDrawEnv.g0, activeDrawEnv.b0);
		}
		else {
			Emulator_BlitVRAM();
		}
	}

#if defined(DEBUG_POLY_COUNT)
	polygon_count = 0;
#endif

	Emulator_AggregatePTAGsToSplits((unsigned int*)p, TRUE);

	Emulator_DrawAggregatedSplits();

#if defined(_PATCH)
	Emulator_StoreFrameBuffer(activeDrawEnv.clip.x, activeDrawEnv.clip.y, activeDrawEnv.clip.w, activeDrawEnv.clip.h);
#endif

#if defined(PGXP)
	Emulator_ResetPGXPCache();
#endif
}

void SetSprt16(SPRT_16* p)
{
	setSprt16(p);
}

void SetSprt8(SPRT_8* p)
{
	setSprt8(p);
}

void SetTile(TILE* p)
{
	setTile(p);
}

void SetPolyGT4(POLY_GT4* p)
{
	setPolyGT4(p);
}

void SetSemiTrans(void* p, int abe)
{
	setSemiTrans(p, abe);
}

void SetShadeTex(void* p, int tge)
{
	setShadeTex(p, tge);
}

void SetSprt(SPRT* p)
{
	setSprt(p);
}

void SetDumpFnt(int id)
{
	if (id >= 0 && (int)fontStreamCount >= id)
	{
		fontCurrentStream = id;
		//sw v0, GPU_printf///@FIXME?
	}
}

void SetLineF3(LINE_F3* p)
{
	setLineF3(p);
}

void FntLoad(int tx, int ty)
{
	unsigned int FontClut[] = { 0xFFFF0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	unsigned int FontTex[] = {
	  0x00000000,0x00010000,0x00101000,0x00000000,0x00111000,0x01111100,0x00001000,0x00011000,0x01000000,0x00000100,0x00010000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00010000,0x00101000,0x00101000,0x01010100,0x01001100,0x00010100,0x00001100,0x00100000,0x00001000,0x01010100,0x00010000,0x00000000,0x00000000,0x00000000,0x01000000,
	  0x00000000,0x00010000,0x00000000,0x01111100,0x00010100,0x00100000,0x00010100,0x00000000,0x00010000,0x00010000,0x00111000,0x00010000,0x00000000,0x00000000,0x00000000,0x00100000,0x00000000,0x00010000,0x00000000,0x00101000,0x00111000,0x00010000,0x00001000,0x00000000,0x00010000,0x00010000,0x00010000,0x01111100,0x00000000,0x01111100,0x00000000,
	  0x00010000,0x00000000,0x00010000,0x00000000,0x00101000,0x01010000,0x00001000,0x01010100,0x00000000,0x00010000,0x00010000,0x00111000,0x00010000,0x00000000,0x00000000,0x00000000,0x00001000,0x00000000,0x00000000,0x00000000,0x01111100,0x01010100,0x01100100,0x00100100,0x00000000,0x00100000,0x00001000,0x01010100,0x00010000,0x00011000,0x00000000,
	  0x00011000,0x00000100,0x00000000,0x00010000,0x00000000,0x00101000,0x00111000,0x01100100,0x01011000,0x00000000,0x01000000,0x00000100,0x00010000,0x00000000,0x00011000,0x00000000,0x00011000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00010000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00001100,
	  0x00000000,0x00000000,0x00000000,0x00111000,0x00010000,0x00111000,0x00111000,0x00100000,0x01111100,0x00110000,0x01111100,0x00111000,0x00111000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111000,0x01000100,0x00011000,0x01000100,0x01000100,0x00110000,0x00000100,0x00001000,0x01000000,0x01000100,0x01000100,0x00000000,0x00000000,
	  0x00100000,0x00000000,0x00001000,0x01000100,0x01100100,0x00010000,0x01000000,0x01000000,0x00101000,0x00111100,0x00000100,0x00100000,0x01000100,0x01000100,0x00011000,0x00011000,0x00010000,0x01111100,0x00010000,0x00100000,0x01010100,0x00010000,0x00100000,0x00110000,0x00100100,0x01000000,0x00111100,0x00100000,0x00111000,0x01111000,0x00011000,
	  0x00011000,0x00001000,0x00000000,0x00100000,0x00010000,0x01001100,0x00010000,0x00010000,0x01000000,0x01111100,0x01000000,0x01000100,0x00010000,0x01000100,0x01000000,0x00000000,0x00000000,0x00010000,0x01111100,0x00010000,0x00010000,0x01000100,0x00010000,0x00001000,0x01000100,0x00100000,0x01000100,0x01000100,0x00010000,0x01000100,0x00100000,
	  0x00011000,0x00011000,0x00100000,0x00000000,0x00001000,0x00000000,0x00111000,0x00111000,0x01111100,0x00111000,0x00100000,0x00111000,0x00111000,0x00010000,0x00111000,0x00011000,0x00011000,0x00011000,0x00000000,0x00000000,0x00000000,0x00010000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	  0x00000000,0x00000000,0x00001100,0x00000000,0x00000000,0x00000000,0x00000000,0x00111000,0x00111000,0x00111100,0x00111000,0x00111100,0x01111100,0x01111100,0x00111000,0x01000100,0x00111000,0x01000000,0x01000100,0x00000100,0x01000100,0x01000100,0x00111000,0x01000100,0x01000100,0x01000100,0x01000100,0x01001000,0x00000100,0x00000100,0x01000100,
	  0x01000100,0x00010000,0x01000000,0x00100100,0x00000100,0x01101100,0x01000100,0x01000100,0x01110100,0x01000100,0x01000100,0x00000100,0x01001000,0x00000100,0x00000100,0x00000100,0x01000100,0x00010000,0x01000000,0x00010100,0x00000100,0x01010100,0x01001100,0x01000100,0x01010100,0x01111100,0x00111100,0x00000100,0x01001000,0x00111100,0x00111100,
	  0x00000100,0x01111100,0x00010000,0x01000000,0x00001100,0x00000100,0x01000100,0x01010100,0x01000100,0x01110100,0x01000100,0x01000100,0x00000100,0x01001000,0x00000100,0x00000100,0x01100100,0x01000100,0x00010000,0x01000000,0x00010100,0x00000100,0x01000100,0x01100100,0x01000100,0x00000100,0x01000100,0x01000100,0x01000100,0x01001000,0x00000100,
	  0x00000100,0x01000100,0x01000100,0x00010000,0x01000100,0x00100100,0x00000100,0x01000100,0x01000100,0x01000100,0x00111000,0x01000100,0x00111100,0x00111000,0x00111100,0x01111100,0x00000100,0x00111000,0x01000100,0x00111000,0x00111000,0x01000100,0x01111100,0x01000100,0x01000100,0x00111000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	  0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111100,0x00111000,0x00111100,0x00111000,0x01111100,0x01000100,0x01000100,0x01000100,0x01000100,0x01000100,0x01111100,0x00010000,0x00000000,0x00010000,0x00101000,0x00000000,0x01000100,0x01000100,0x01000100,0x01000100,
	  0x00010000,0x01000100,0x01000100,0x01000100,0x01000100,0x01000100,0x01000000,0x00010000,0x00000100,0x00010000,0x01000100,0x00000000,0x01000100,0x01000100,0x01000100,0x00000100,0x00010000,0x01000100,0x01000100,0x01000100,0x00101000,0x00101000,0x00100000,0x00010000,0x00001000,0x00010000,0x00000000,0x00000000,0x00111100,0x01000100,0x00111100,
	  0x00111000,0x00010000,0x01000100,0x01000100,0x01000100,0x00010000,0x00010000,0x01111100,0x00010000,0x00010000,0x00010000,0x00000000,0x00000000,0x00000100,0x01010100,0x00010100,0x01000000,0x00010000,0x01000100,0x00101000,0x01010100,0x00101000,0x00010000,0x00001000,0x00010000,0x00100000,0x00010000,0x00000000,0x00000000,0x00000100,0x00100100,
	  0x00100100,0x01000100,0x00010000,0x01000100,0x00101000,0x01101100,0x01000100,0x00010000,0x00000100,0x00010000,0x01000000,0x00010000,0x00000000,0x00000000,0x00000100,0x01011000,0x01000100,0x00111000,0x00010000,0x00111000,0x00010000,0x01000100,0x01000100,0x00010000,0x01111100,0x00010000,0x00000000,0x00010000,0x00000000,0x00000000,0x00000000,
	  0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01110000,0x00000000,0x00011100,0x00000000,0x00000000 };
	
	LoadClut2(FontClut, tx, ty + 128);
	LoadTPage(FontTex, 0, 0, tx, ty, 128, 32);
}

void AddPrim(void* ot, void* p)
{
	addPrim(ot, p);
}

void AddPrims(void* ot, void* p0, void* p1)
{
	addPrims(ot, p0, p1);
}

void CatPrim(void* p0, void* p1)
{
	catPrim(p0, p1);
}

u_short LoadTPage(unsigned int* pix, int tp, int abr, int x, int y, int w, int h)
{
	RECT16 imageArea;
	imageArea.x = x;
	imageArea.y = y;
	imageArea.h = h;

	enum
	{
		TP_4BIT,
		TP_8BIT,
		TP_16BIT
	};

	switch (tp)
	{
	case TP_4BIT:
	{
		//loc_278
		if (w >= 0)
		{
			imageArea.w = w >> 2;
		}
		else
		{
			imageArea.w = (w + 3) >> 2;
		}
		break;
	}
	case TP_8BIT:
	{
		//loc_290
		imageArea.w = (w + (w >> 31)) >> 1;
		break;
	}
	case TP_16BIT:
	{
		//loc_2A4
		imageArea.w = w;
		break;
	}
	}

	//loc_2AC
	LoadImagePSX(&imageArea, pix);
	return GetTPage(tp, abr, x, y) & 0xFFFF;
}

u_short GetTPage(int tp, int abr, int x, int y)
{
	return getTPage(tp, abr, x, y);
}

u_short LoadClut(unsigned int* clut, int x, int y)
{
	RECT16 rect;//&var_18
	setRECT16(&rect, x, y, 256, 1);
	LoadImagePSX(&rect, clut);
	return GetClut(x, y) & 0xFFFF;
}

u_short LoadClut2(unsigned int* clut, int x, int y)
{
	RECT16 drawArea;
	drawArea.x = x;
	drawArea.y = y;
	drawArea.w = 16;
	drawArea.h = 1;
	LoadImagePSX(&drawArea, clut);
	return getClut(x, y);
}

u_long* KanjiFntFlush(int id)
{
	UNIMPLEMENTED();
	return 0;
}

u_long* FntFlush(int id)
{
	UNIMPLEMENTED();
	return 0;
}

int KanjiFntOpen(int x, int y, int w, int h, int dx, int dy, int cx, int cy, int isbg, int n)
{
	UNIMPLEMENTED();
	return 0;
}

int FntOpen(int x, int y, int w, int h, int isbg, int n)
{
	RECT16 rect;
	int characterCount = n;
	SPRT_8* pSprite;

	//Maximum number of font streams is 8.
	if (fontStreamCount >= MAX_NUM_FONT_STREAMS)
	{
		return -1;
	}

	//loc_338
	if (fontStreamCount == 0)
	{
		fontUsedCharacterCount = 0;
	}

	//loc_348
	font[fontStreamCount].unk07 = w < 1;

	if (characterCount + fontUsedCharacterCount >= MAX_FONT_CHARACTER_COUNT)
	{
		characterCount = MAX_FONT_CHARACTER_COUNT - fontUsedCharacterCount;
	}

	//loc_37C
	rect.x = 0;
	rect.x = 0;
	rect.w = 256;
	rect.h = 256;
	SetDrawMode(&fontMode, 0, 0, fontTpage, &rect);

	//Should we clear the draw area?
	if (isbg != FALSE)
	{
		SetTile(&font[fontStreamCount].tile);
		setRGB0(&font[fontStreamCount].tile, 0, 0, 0);
		SetSemiTrans(&font[fontStreamCount].tile, (isbg ^ 2) < 1);
	}

	//loc_460
	setXY0(&font[fontStreamCount].tile, x, y);
	setWH(&font[fontStreamCount].tile, w, h);

	font[fontStreamCount].characterCount = n;
	font[fontStreamCount].unk06 = 0;
	font[fontStreamCount].unk05 = &unk_1B00[fontUsedCharacterCount];
	font[fontStreamCount].pSprites = (SPRT_8*)&unk_1F00[fontUsedCharacterCount << 4];
	font[fontStreamCount].unk05[0] = 0;
	
	if (n > 0)
	{
		pSprite = &font[fontStreamCount].pSprites[0];

		for (int i = 0; i < n; i++, pSprite++)
		{
			SetSprt8(pSprite);
			pSprite->clut = fontClut;
		}
	}

	fontUsedCharacterCount += n;
	fontStreamCount += 1;

	return fontStreamCount - 1;
}

void SetPolyF4(POLY_F4* p)
{
	setPolyF4(p);
}

void SetPolyFT4(POLY_FT4* p)
{
	setPolyFT4(p);
}

void SetPolyG4(POLY_G4* p)
{
	setPolyG4(p);
}

void TermPrim(void* p)
{
	termPrim(p);
}

u_long* BreakDraw(void)
{
	return (u_long*)0xFFFFFFFF;
}

void ContinueDraw(u_long* insaddr, u_long* contaddr)
{
	UNIMPLEMENTED();
}
