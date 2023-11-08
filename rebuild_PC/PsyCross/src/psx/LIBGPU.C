#include "psx/libgte.h"
#include "psx/libgpu.h"
#include "psx/libetc.h"

#include "../gpu/PsyX_GPU.h"
#include "PsyX/PsyX_render.h"
#include "PsyX/PsyX_public.h"

#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#include "PsyX/PsyX_globals.h"
#include "../PsyX_main.h"
#include "../gpu/font.h"

int g_dbg_emulatorPaused = 0;

void(*drawsync_callback)(void) = NULL;

int ClearImage(RECT16* rect, u_char r, u_char g, u_char b)
{
	GR_ClearVRAM(rect->x, rect->y, rect->w, rect->h, r, g, b);

	// TODO: clear all affected backbuffers
	GR_Clear(rect->x, rect->y, rect->w, rect->h, r, g, b);
	return 0;
}

int ClearImage2(RECT16* rect, u_char r, u_char g, u_char b)
{
	GR_ClearVRAM(rect->x, rect->y, rect->w, rect->h, r, g, b);

	// TODO: clear all affected backbuffers
	GR_Clear(rect->x, rect->y, rect->w, rect->h, r, g, b);
	return 0;
}

int DrawSync(int mode)
{
	// Update VRAM seems needed to be here
	GR_UpdateVRAM();
	GR_ReadFramebufferDataToVRAM();

	if (g_splitIndex > 0)// && g_GPUDisabledState == 0) // don't do flips if nothing to draw.
	{
		DrawAllSplits();
		//PsyX_EndScene();
	}

	if (drawsync_callback != NULL)
	{
		drawsync_callback();
	}

	return 0;
}

int LoadImagePSX(RECT16* rect, u_long* p)
{
	GR_CopyVRAM((unsigned short*)p, 0, 0, rect->w, rect->h, rect->x, rect->y);
	return 0;
}

int LoadImage(RECT16* rect, u_long* p)
{
	LoadImagePSX(rect, p);
	return 0;
}

int LoadImage2(RECT16* rect, u_long* p)
{
	LoadImagePSX(rect, p);

	// simulate immediate mode
	GR_UpdateVRAM();
	GR_ReadFramebufferDataToVRAM();

	return 0;
}

int MargePrim(void* p0, void* p1)
{
#if 0
	int v0 = ((unsigned char*)p0)[3];
	int v1 = ((unsigned char*)p1)[3];

	v0 += v1;
	v1 = v0 + 1;

	if (v1 < 0x11)
	{
		((char*)p0)[3] = v1;
		((int*)p1)[0] = 0;
		return 0;
	}

	return -1;
#endif //0

#if USE_EXTENDED_PRIM_POINTERS
	int v0 = ((int*)p0)[1];
	int v1 = ((int*)p1)[1];
#else
	int v0 = ((unsigned char*)p0)[3];
	int v1 = ((unsigned char*)p1)[3];
#endif

	v0 += v1;
	v1 = v0 + 1;

#if USE_EXTENDED_PRIM_POINTERS
	if (v1 < 0x12)
#else
	if (v1 < 0x11)
#endif
	{
#if USE_EXTENDED_PRIM_POINTERS
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
	GR_CopyVRAM(NULL, rect->x, rect->y, rect->w, rect->h, x, y);
	return 0;
}

int ResetGraph(int mode)
{
	if (mode == 0)
	{
		// reset GPU state
		g_GPUDisabledState = 0;
		ClearImage(&activeDrawEnv.clip, 0, 0, 0);

		ClearSplits();
		PsyX_EndScene();
	}
	else if (mode == 1)
	{
		// cancell all rendering
		ClearSplits();
		PsyX_EndScene();
	}
	else if (mode == 3)
	{

	}

	return 0;
}

int SetGraphDebug(int level)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int StoreImage(RECT16* rect, u_long* p)
{
	GR_ReadVRAM((unsigned short*)p, rect->x, rect->y, rect->w, rect->h);
	return 0;
}

int StoreImage2(RECT16* RECT16, u_long* p)
{
	int result = StoreImage(RECT16, p);
	// GPU reset?

	return result;
}


u_long* ClearOTag(u_long* ot, int n)
{
	OT_TAG* ptag_list;

	if (n == 0)
		return NULL;
	ptag_list = (OT_TAG*)ot;

	// last is  aspecial terminator
	setaddr(&ptag_list[n-1], &prim_terminator);
	setlen(&ptag_list[n-1], 0);

	// make a linked list with it's next items
	for (int i = (n-1); i >= 0; --i)
	{
		setaddr(&ptag_list[i], &ptag_list[i+1]);
		setlen(&ptag_list[i], 0);
	}

	return NULL;
}

u_long* ClearOTagR(u_long* ot, int n)
{
	OT_TAG* ptag_list;

	if (n == 0)
		return NULL;
	ptag_list = (OT_TAG*)ot;

	// first is a special terminator
	setaddr(ptag_list, &prim_terminator);
	setlen(ptag_list, 0);

	// initialize a linked list with it's previous items
	for (int i = 1; i < n; ++i)
	{
		setaddr(&ptag_list[i], &ptag_list[i-1]);
		setlen(&ptag_list[i], 0);
	}

	return NULL;
}

void SetDispMask(int mask)
{
	g_GPUDisabledState = (mask == 0);
}

int FntPrint(char* fmt, ...)
{
	int n;
	va_list ap;

	int id = _nstreams - 1;

	n = strlen(_stream[id].txtbuff);

	if (n >= _stream[id].maxchars) {
		return n;
	}

	va_start(ap, fmt);

	n = vsnprintf(_stream[id].txtnext, _stream[id].maxchars - n, fmt, ap);

	_stream[id].txtnext += n;

	va_end(ap);

	return strlen(_stream[id].txtbuff);
}

int GetODE(void)
{
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
	env->disp.h = h;

	env->screen.x = 0;
	env->screen.y = 0;
	env->screen.w = 0;
	env->screen.h = 0;

	env->isrgb24 = 0;
	env->isinter = 0;

	env->pad1 = 0;
	env->pad0 = 0;

	return 0;
}

DRAWENV* GetDrawEnv(DRAWENV* env)
{
	PSYX_UNIMPLEMENTED();
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
	env->clip.h = h;

	env->tw.x = 0;
	env->tw.y = 0;
	env->tw.w = 0;
	env->tw.h = 0;
	env->r0 = 0;
	env->g0 = 0;
	env->b0 = 0;
	env->dtd = 1;

	if (GetVideoMode() == MODE_NTSC)
		env->dfe = h < 289 ? 1 : 0;
	else
		env->dfe = h < 257 ? 1 : 0;

	env->ofs[0] = x;
	env->ofs[1] = y;

	env->tpage = 10;
	env->isbg = 0;

	return env;
}

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env)
{
	dr_env->code[0] = ((env->clip.y & 0x3FF) << 10) | env->clip.x & 0x3FF | 0xE3000000;
	dr_env->code[1] = (((env->clip.y + env->clip.h - 1) & 0x3FF) << 10) | (env->clip.x + env->clip.w - 1) & 0x3FF | 0xE4000000;
	dr_env->code[2] = ((env->ofs[1] & 0x3FF) << 11) | env->ofs[0] & 0x7FF | 0xE5000000;
	dr_env->code[3] = 32 * (((256 - env->tw.h) >> 3) & 0x1F) | ((256 - env->tw.w) >> 3) & 0x1F | (((env->tw.y >> 3) & 0x1F) << 15) | (((env->tw.x >> 3) & 0x1F) << 10) | 0xE2000000;
	dr_env->code[4] = ((env->dtd != 0) << 9) | ((env->dfe != 0) << 10) | env->tpage & 0x1FF | 0xE1000000;

	// TODO: add missing logic when env->isbg != 0

	setlen(dr_env, 5);
}

void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT16* tw)
{
	setDrawMode(p, dfe, dtd, tpage, tw);
}

void SetDrawArea(DR_AREA* p, RECT16* r)
{
	p->code[0] = (r->x & 0x3FF | ((r->y & 0x3FF) << 10)) | 0xE3000000;
	p->code[1] = (((r->x + r->w) & 0x3FF) | (((r->y + r->h) & 0x3FF) << 10)) | 0xE4000000;

	setlen(p, 2);
}

void SetDrawMove(DR_MOVE* p, RECT16* rect, int x, int y)
{
	char len;

	len = 5;

	if (rect->w == 0 || rect->h == 0)
		len = 0;

	p->code[0] = 0x1000000;
	p->code[1] = 0x80000000;
	p->code[2] = *(ulong*)&rect->x;
	p->code[3] = y << 0x10 | x & 0xffffU;
	p->code[4] = *(ulong*)&rect->w;

	setlen(p, len);
}

void SetDrawLoad(DR_LOAD* p, RECT16* RECT16)
{
	setDrawLoad(p, RECT16);
}

void SetDrawTPage(DR_TPAGE* p, int dfe, int dtd, int tpage)
{
	setDrawTPage(p, dfe, dtd, tpage);
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
//------------------------------------------------------------------

void DrawOTagEnv(u_long* p, DRAWENV* env)
{
	PutDrawEnv(env);
	DrawOTag(p);
}

void DrawOTag(u_long* p)
{
	do
	{
		if (g_GPUDisabledState)
		{
			ClearSplits();
			return;
		}

		if (PsyX_BeginScene())
		{
			ClearSplits();
		}

		//if (activeDrawEnv.isbg)
		//	ClearImage(&activeDrawEnv.clip, activeDrawEnv.r0, activeDrawEnv.g0, activeDrawEnv.b0);

		ParsePrimitivesToSplits(p, 0);

		DrawAllSplits();
	} while (g_dbg_emulatorPaused);
}
 
void DrawPrim(void* p)
{
	if (g_GPUDisabledState)
	{
		ClearSplits();
		return;
	}

	if (PsyX_BeginScene())
	{
		ClearSplits();
	}

	//if (activeDrawEnv.isbg)
	//	ClearImage(&activeDrawEnv.clip, activeDrawEnv.r0, activeDrawEnv.g0, activeDrawEnv.b0);

 	ParsePrimitivesToSplits((u_long*)p, 1);
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
	PSYX_UNIMPLEMENTED();
}

void SetLineF3(LINE_F3* p)
{
	setLineF3(p);
}

void FntLoad(int x, int y)
{
	RECT16 pos;
	TIM_IMAGE tim;

	GetTimInfo((u_long*)dbugfont, &tim);

	// Load font image
	pos = *tim.pRECT16;
	pos.x = x;
	pos.y = y;

	_font_tpage = getTPage(0, 0, pos.x, pos.y);

	LoadImage(&pos, tim.paddr);
	DrawSync(0);

	// Load font clut
	pos = *tim.cRECT16;
	pos.x = x;
	pos.y = y + tim.pRECT16->h;

	_font_clut = getClut(pos.x, pos.y);

	LoadImage(&pos, tim.caddr);
	DrawSync(0);

	// Clear previously opened text streams
	if (_nstreams) {

		int i;

		for (i = 0; i < _nstreams; i++) {
			free(_stream[i].txtbuff);
			free(_stream[i].pribuff);
		}

		_nstreams = 0;

	}
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

u_short LoadTPage(u_long* pix, int tp, int abr, int x, int y, int w, int h)
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

u_short LoadClut(u_long* clut, int x, int y)
{
	RECT16 rect;//&var_18
	setRECT(&rect, x, y, 256, 1);
	LoadImagePSX(&rect, clut);
	return GetClut(x, y) & 0xFFFF;
}

u_short LoadClut2(u_long* clut, int x, int y)
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
	PSYX_UNIMPLEMENTED();
	return 0;
}

u_long* FntFlush()
{
	_fnt_stream* str;
	char* opri;
	SPRT_8* sprt;
	char* text;
	int	i, sx, sy;

	int	id = _nstreams - 1;
	str = &_stream[id];

	sx = str->x;
	sy = str->y;

	opri = str->pribuff;

	// Create TPage primitive
	setDrawTPage(opri, 1, 0, _font_tpage);

	// Create a black rectangle background when enabled
	if (str->bg)
	{
		TILE* tile;
		tile = (TILE*)(opri + sizeof(DR_TPAGE));

		setTile(tile);

		if (str->bg == 2)
			setSemiTrans(tile, 1);

		setXY0(tile, _HF(str->x), _HF(str->y));
		setWH(tile, _HF(str->w), _HF(str->h));
		setRGB0(tile, 0, 0, 0);

		setaddr(opri, tile);
		opri = (char*)tile;

		sprt = (SPRT_8*)(opri + sizeof(TILE));
	}
	else 
	{
		sprt = (SPRT_8*)(opri + sizeof(DR_TPAGE));
	}

	text = str->txtbuff;

	// Create the sprite primitives
	while (*text != 0) 
	{
		if ((*text == '\n') || ((sx - str->x) > str->w - 8))
		{
			sx = str->x;
			sy += 8;

			if (*text == '\n')
				text++;

			continue;
		}

		if ((sy - str->y) > str->h - 8)
			break;

		i = toupper(*text) - 32;

		if (i > 0)
		{
			i--;
			setSprt8(sprt);
			setRGB0(sprt, 128, 128, 128);
			setXY0(sprt, _HF(sx), _HF(sy));
			setUV0(sprt, (i % 16) << 3, (i >> 4) << 3);
			sprt->clut = _font_clut;

			setaddr(opri, sprt);
			opri = (char*)sprt;

			sprt++;
		}

		sx += 8;
		text++;
	}

	// Set a terminator value to the last primitive
	termPrim(opri);

	// Draw the primitives
	//DrawSync(0);
	DrawOTag((u_long*)str->pribuff);
	//DrawSync(0);

	str->txtnext = str->txtbuff;
	str->txtbuff[0] = 0;

	return (u_long*)str->pribuff;
}

int KanjiFntOpen(int x, int y, int w, int h, int dx, int dy, int cx, int cy, int isbg, int n)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int FntOpen(int x, int y, int w, int h, int isbg, int n)
{
	_fnt_stream* str;
	int i;

	// Initialize a text stream
	str = &_stream[_nstreams];
	
	str->x = x;
	str->y = y;
	str->w = w;
	str->h = h;

	i = (sizeof(SPRT_8) * n) + sizeof(DR_TPAGE);

	if (isbg)
		i += sizeof(TILE);

	str->pribuff = (char*)malloc(i);
	str->maxchars = n;

	str->txtbuff = (char*)malloc(n + 1);
	str->txtbuff[0] = '\0';

	str->txtnext = str->txtbuff;
	str->bg = isbg;

	return _nstreams++;
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

void SetPsyXTexture(DR_PSYX_TEX* p, uint grTextureId, int width, int height)
{
	setlen(p, 2);
	p->code[0] = 0xB1000000 | grTextureId;
	p->code[1] = width | (height << 16);
}

u_long* BreakDraw(void)
{
	PSYX_UNIMPLEMENTED();
}