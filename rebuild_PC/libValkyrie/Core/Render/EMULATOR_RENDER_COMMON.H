#ifndef EMULATOR_RENDER_H
#define EMULATOR_RENDER_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"

#if defined (OGL)
#include "Core/Render/OGL/EMULATOR_RENDER_OGL.H"
#elif defined (OGLES)
#include "Core/Render/OGLES/EMULATOR_RENDER_OGLES.H"
#elif defined(D3D9)
#include "Core/Render/D3D9/EMULATOR_RENDER_D3D9.H"
#elif defined(D3D11)
#include "Core/Render/D3D11/EMULATOR_RENDER_D3D11.H"
#elif defined(D3D12)
#include "Core/Render/D3D12/EMULATOR_RENDER_D3D12.H"
#elif defined(VULKAN)
#include "Core/Render/VULKAN/EMULATOR_RENDER_VULKAN.H"
#elif defined(XED3D)
#include "Core/Render/XED3D/EMULATOR_RENDER_XED3D.H"
#elif defined(SN_TARGET_PSP2)
#include "Core/Render/GXM/EMULATOR_RENDER_GXM.H"
#elif defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
#include "Core/Render/NVN/EMULATOR_RENDER_NVN.H"
#endif

#include "Core/Utility/EMULATOR_UTILITY_COMMON.H"

typedef enum BlendMode
{
	BM_NONE,
	BM_AVERAGE,
	BM_ADD,
	BM_SUBTRACT,
	BM_ADD_QUATER_SOURCE,
	BM_COUNT

} BlendMode;

typedef enum TexFormat 
{
	TF_4_BIT,
	TF_8_BIT,
	TF_16_BIT,
	TF_COUNT,

} TexFormat;

#pragma pack(push,1)
struct Vertex
{
#if defined(PGXP)
	float  x, y, page, clut;
#else
	short  x, y, page, clut;
#endif
	unsigned char u, v, bright, dither;
	unsigned char r, g, b, a;
#if defined(PGXP)
	float z, w;
#endif
};
#pragma pack(pop)

struct VertexBufferSplit
{
#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
	TextureID*      textureId;
#else
	TextureID      textureId;
#endif
	unsigned short vIndex;
	unsigned short iIndex;
	unsigned short vCount;
	unsigned short iCount;
	enum BlendMode blendMode;
	enum TexFormat texFormat;
	int isNew;
};

extern void Emulator_BlitVRAM();
extern void Emulator_ClearVBO();
extern void Emulator_UpdateVBO(int new_start_vertex_index, int new_start_face_index);
extern void Emulator_ResetPolyState();
extern void Emulator_AggregatePTAGsToSplits(unsigned int* p, int singlePrimitive);
extern void Emulator_DrawSplit(const struct VertexBufferSplit* split);
extern void Emulator_DrawAggregatedSplits();

#if defined(TOUCH_UI)
extern void Emulator_DrawTouchUI();
#endif

extern int g_swapInterval;
extern int g_wireframeMode;
extern int64_t g_swapTime;
extern int g_PreviousBlendMode;
extern int g_texturelessMode;
extern int windowWidth;
extern int windowHeight;
extern int g_overrideWidth;
extern int g_overrideHeight;
#if defined(D3D11) || (defined(OGL) && defined(_WINDOWS))
#include <Windows.h>//OGL
extern HWND g_overrideHWND;
#endif
extern unsigned int g_resetDeviceOnNextFrame;
extern unsigned int g_closeOnNextFrame;
extern unsigned int g_resettingDevice;
#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
extern TextureID* g_lastBoundTexture[];
#else
extern TextureID g_lastBoundTexture[];
#endif
extern int begin_scene_flag;
extern int vbo_was_dirty_flag;

#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
extern ShaderID* g_gte_shader_4;
extern ShaderID* g_gte_shader_8;
extern ShaderID* g_gte_shader_16;
extern ShaderID* g_blit_shader;

extern TextureID* vramTexture;
extern TextureID* whiteTexture;
extern TextureID* rg8lutTexture;
#else
extern ShaderID g_gte_shader_4;
extern ShaderID g_gte_shader_8;
extern ShaderID g_gte_shader_16;
extern ShaderID g_blit_shader;

extern TextureID vramTexture;
extern TextureID whiteTexture;
extern TextureID rg8lutTexture;
#endif

extern unsigned short vram[];
extern unsigned char rgLUT[];

extern int vram_need_update;

extern int g_vertexIndex;
extern int g_indicesIndex;

#define LUT_WIDTH (256)
#define LUT_HEIGHT (256)

#define VRAM_WIDTH (1024)
#define VRAM_HEIGHT (512)

#define TPAGE_WIDTH (256)
#define TPAGE_HEIGHT (256)

#define CLUT_WIDTH (16)
#define CLUT_HEIGHT (1)

#define MAX_NUM_POLY_BUFFER_VERTICES (8192*2)
#define MAX_NUM_INDEX_BUFFER_INDICES (8192*2)
#define MAX_NUM_INDEX_BUFFER_SPLITS  (4096*2)

#define VRAM_FORMAT            GL_RG
#define VRAM_INTERNAL_FORMAT   GL_RG8

#if defined(_DEBUG) && 0//60FPS
#define FIXED_TIME_STEP    16
#else
#define FIXED_TIME_STEP    33
#endif
#define SWAP_INTERVAL      1

extern void* Emulator_GenerateRG8LUT();
extern void Emulator_SwapWindow();
extern void Emulator_ResetDevice(int recreate);
#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
extern void Emulator_SetShader(ShaderID* shader);
extern void Emulator_SetTextureAndShader(TextureID* texture, ShaderID* shader);
extern ShaderID* Emulator_GetGTEShader(TexFormat texFormat);
#else
extern void Emulator_SetTextureAndShader(TextureID texture, ShaderID shader);
extern ShaderID Emulator_GetGTEShader(TexFormat texFormat);
#endif

extern void Emulator_UpdateVertexBuffer(const struct Vertex* vertices, int num_vertices, int vertex_start_index, int use_offset);
extern void Emulator_UpdateIndexBuffer(const unsigned short* indices, int num_indices, int face_start_index, int use_offset);
extern int Emulator_CreateCommonResources();
extern void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar);
extern const char* renderBackendName;

extern int Emulator_GetWindowWidth();
extern int Emulator_GetWindowHeight();

extern void Emulator_DestroyRender();

/*
 * Polygon Primitive Definitions
 */
typedef struct {
	u_char		r0, g0, b0, code;
} IP_TAG;

typedef struct {
	u_char	r0, g0, b0, code;
} IP_CODE;

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	short	x1, y1;
	short	x2, y2;
} IPOLY_F3;				/* Flat Triangle */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	short	x1, y1;
	short	x2, y2;
	short	x3, y3;
} IPOLY_F4;				/* Flat Quadrangle */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	u0, v0;	u_short	clut;
	short	x1, y1;
	u_char	u1, v1;	u_short	tpage;
	short	x2, y2;
	u_char	u2, v2;	u_short	pad1;
} IPOLY_FT3;				/* Flat Textured Triangle */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	u0, v0;	u_short	clut;
	short	x1, y1;
	u_char	u1, v1;	u_short	tpage;
	short	x2, y2;
	u_char	u2, v2;	u_short	pad1;
	short	x3, y3;
	u_char	u3, v3;	u_short	pad2;
} IPOLY_FT4;				/* Flat Textured Quadrangle */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	r1, g1, b1, pad1;
	short	x1, y1;
	u_char	r2, g2, b2, pad2;
	short	x2, y2;
} IPOLY_G3;				/* Gouraud Triangle */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	r1, g1, b1, pad1;
	short	x1, y1;
	u_char	r2, g2, b2, pad2;
	short	x2, y2;
	u_char	r3, g3, b3, pad3;
	short	x3, y3;
} IPOLY_G4;				/* Gouraud Quadrangle */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	u0, v0;	u_short	clut;
	u_char	r1, g1, b1, p1;
	short	x1, y1;
	u_char	u1, v1;	u_short	tpage;
	u_char	r2, g2, b2, p2;
	short	x2, y2;
	u_char	u2, v2;	u_short	pad2;
} IPOLY_GT3;				/* Gouraud Textured Triangle */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	u0, v0;	u_short	clut;
	u_char	r1, g1, b1, p1;
	short	x1, y1;
	u_char	u1, v1;	u_short	tpage;
	u_char	r2, g2, b2, p2;
	short	x2, y2;
	u_char	u2, v2;	u_short	pad2;
	u_char	r3, g3, b3, p3;//10
	short	x3, y3;//11
	u_char	u3, v3;	u_short	pad3;
} IPOLY_GT4;				/* Gouraud Textured Quadrangle */

/*
 * Line Primitive Definitions
 */
typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	short	x1, y1;
} ILINE_F2;				/* Unconnected Flat Line */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	r1, g1, b1, p1;
	short	x1, y1;
} ILINE_G2;				/* Unconnected Gouraud Line */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	short	x1, y1;
	short	x2, y2;
	u_long	pad;
} ILINE_F3;				/* 2 connected Flat Line */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	r1, g1, b1, p1;
	short	x1, y1;
	u_char	r2, g2, b2, p2;
	short	x2, y2;
	u_long	pad;
} ILINE_G3;				/* 2 connected Gouraud Line */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	short	x1, y1;
	short	x2, y2;
	short	x3, y3;
	u_long	pad;
} ILINE_F4;				/* 3 connected Flat Line Quadrangle */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	r1, g1, b1, p1;
	short	x1, y1;
	u_char	r2, g2, b2, p2;
	short	x2, y2;
	u_char	r3, g3, b3, p3;
	short	x3, y3;
	u_long	pad;
} ILINE_G4;				/* 3 connected Gouraud Line */

/*
 * Sprite Primitive Definitions
 */
typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	u0, v0;	u_short	clut;
	short	w, h;
} ISPRT;					/* free size Sprite */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	u0, v0;	u_short	clut;
} ISPRT_16;				/* 16x16 Sprite */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	u_char	u0, v0;	u_short	clut;
} ISPRT_8;				/* 8x8 Sprite */

/*
 * Tile Primitive Definitions
 */
typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
	short	w, h;
} ITILE;					/* free size Tile */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
} ITILE_16;				/* 16x16 Tile */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
} ITILE_8;				/* 8x8 Tile */

typedef struct {
	u_char	r0, g0, b0, code;
	short	x0, y0;
} ITILE_1;				/* 1x1 Tile */

/*
 *  Special Primitive Definitions
 */
typedef struct {
	u_long	code[2];
} IDR_MODE;				/* Drawing Mode */

typedef struct {
	u_long	code[2];
} IDR_TWIN;				/* Texture Window */

typedef struct {
	u_long	code[2];
} IDR_AREA;				/* Drawing Area */

typedef struct {
	u_long	code[2];
} IDR_OFFSET;				/* Drawing Offset */

typedef struct {			/* MoveImage */
	u_long	code[3];
} IDR_MOVE;

typedef struct {			/* LoadImage */
	u_long	code[3];
	u_long	p[13];
} IDR_LOAD;

typedef	struct {
	u_long	code[1];
} IDR_TPAGE;				/* Drawing TPage */

typedef struct {
	u_long  code[2];
} IDR_STP;                               /* Drawing STP */

#endif