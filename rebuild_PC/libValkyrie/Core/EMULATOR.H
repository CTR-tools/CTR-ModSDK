#ifndef EMULATOR_H
#define EMULATOR_H

#include "LIBGPU.H"

#include <stdio.h>
#include <stddef.h>

#include "Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"
#include "Debug/EMULATOR_LOG.H"
#include "Core/Render/EMULATOR_RENDER_COMMON.H"
#include "Core/Utility/EMULATOR_UTILITY_COMMON.H"

//#define USE_THREADS

#if defined(USE_THREADS)
#include <thread>
#endif

#if !((defined OGL) || (defined(OGLES) && OGLES_VERSION == 3))
#define glGenVertexArrays       glGenVertexArraysOES
#define glBindVertexArray       glBindVertexArrayOES
#define glDeleteVertexArrays    glDeleteVertexArraysOES
#endif

#if defined(OGL) || defined(OGLES)
#define VRAM_FORMAT            GL_RG
#define VRAM_INTERNAL_FORMAT   GL_RG8
#endif

#define CTR_RUNNING (0)
#define CTR_STOPPED (1)

#define CTR_MODE_TO_FFFF (0)
#define CTR_MODE_TO_TARG (1)

#define CTR_CLOCK_SYS (0)
#define CTR_CLOCK_PIXEL (1)
#define CTR_HORIZ_RETRACE (1)

#define CTR_CLOCK_SYS_ONE (0)
#define CTR_CLOCK_SYS_ONE_EIGHTH (1)

#define GET_TPAGE_X(tpage)      (((tpage << 6) & 0x7C0) % (VRAM_WIDTH))
#define GET_TPAGE_Y(tpage)      (((((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200))) % (VRAM_HEIGHT))
#define GET_TPAGE_FORMAT(tpage) ((TexFormat)((tpage >> 7) & 0x3))
#define GET_TPAGE_BLEND(tpage)  ((BlendMode)(((page >> 5) & 3) + 1))

// TODO
#define GET_TPAGE_DITHER(tpage) 1
//#define GET_TPAGE_DITHER(tpage) 1((tpage >> 9) & 0x1)

#define GET_CLUT_X(clut)        ((clut & 0x3F) << 4)
#define GET_CLUT_Y(clut)        (clut >> 6)

#define SCREENSHOT_MODE_TGA 0
#define SCREENSHOT_MODE_BMP 1

typedef long (*CallbackProc)(void);

typedef struct SysCounter
{
	unsigned int i_cycle;

	union
	{
		int64_t cycle;
		unsigned short unk00;
	};

	unsigned int i_value;

	union
	{
		unsigned short value;
		unsigned short unk01;
	};

	unsigned int i_target;

	union
	{
		unsigned short target;
		unsigned short unk02;
	};

	CallbackProc padding00;
	unsigned int timerIndex;
#if !defined(SN_TARGET_PSP2) && !defined(PLATFORM_NX) && !defined(PLATFORM_NX_ARM) && !defined(_XBOX)
#if defined(UWP_SDL2) || defined(SDL2) && !defined(USE_THREADS)
	SDL_TimerID timerId;
#else
	std::thread timerId;
#endif
#endif
	unsigned int startTick;
} SysCounter;

extern SysCounter counters[3];

extern unsigned short vram[];

struct TouchButtonVRAM
{
	short tpage;
	short clut;
	short u[4];
	short v[4];
	short w;
	short h;
};

extern struct TouchButtonVRAM touchButtonsUI[10];

extern int begin_scene_flag;
extern int vbo_was_dirty_flag;

#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
extern TextureID* rg8lutTexture;
extern TextureID* whiteTexture;
extern TextureID* vramTexture;
#else
extern TextureID rg8lutTexture;
extern TextureID whiteTexture;
extern TextureID vramTexture;
#endif

extern void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer);
extern void Emulator_CopyVRAM(unsigned short* src, int x, int y, int w, int h, int dst_x, int dst_y);
extern void Emulator_ReadVRAM(unsigned short* dst, int x, int y, int dst_w, int dst_h);
extern void Emulator_UpdateVRAM();
extern void Emulator_ShutDown();
extern void Emulator_SetBlendMode(enum BlendMode blendMode);
extern void Emulator_CounterLoop();
extern int Emulator_BeginScene();
extern void Emulator_EndScene();

#if defined(USE_THREADS)
extern void Emulator_CounterWrapper(int timerID);
#else
extern unsigned int Emulator_CounterWrapper(unsigned int interval, void* pTimerID);
#endif

extern void Emulator_GenerateLineArray(struct Vertex* vertex, short* p0, short* p1);
#if defined(PGXP)
extern void Emulator_ResetPGXPCache();
#endif

extern void Emulator_GenerateVertexArrayTriangle(struct Vertex* vertex, short* p0, short* p1, short* p2);
extern void Emulator_GenerateVertexArrayQuad(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3);
extern void Emulator_DoSplitHackQuad(short* p0, short* p1, short* p2, short* p3);
extern void Emulator_GenerateVertexArrayRect(struct Vertex* vertex, short* p0, short w, short h);

extern void Emulator_GenerateTexcoordArrayTriangle(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, short page, short clut, unsigned char dither);
extern void Emulator_GenerateTexcoordArrayQuad(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short page, short clut, unsigned char dither);
extern void Emulator_GenerateTexcoordArrayRect(struct Vertex* vertex, unsigned char* uv, short page, short clut, short w, short h);
extern void Emulator_GenerateTexcoordArrayLineZero(struct Vertex* vertex, unsigned char dither);
extern void Emulator_GenerateTexcoordArrayTriangleZero(struct Vertex* vertex, unsigned char dither);
extern void Emulator_GenerateTexcoordArrayQuadZero(struct Vertex* vertex, unsigned char dither);

extern void Emulator_GenerateColourArrayLine(struct Vertex* vertex, unsigned char* col0, unsigned char* col1);
extern void Emulator_GenerateColourArrayTriangle(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2);
extern void Emulator_GenerateColourArrayQuad(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, int bMaxCol);

extern void Emulator_DestroyTexture(TextureID texture);
extern void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b);
extern void Emulator_SetViewPort(int x, int y, int width, int height);
extern void Emulator_SetRenderTarget(const RenderTargetID render_target);
extern void Emulator_SetWireframe(int enable);
extern void Emulator_DrawTriangles(int start_vertex, int start_index, int triangles);
extern void Emulator_UpdateToActiveDrawEnv();

extern void Emulator_CreateGlobalShaders();
extern void Emulator_DestroyGlobalShaders();
extern void Emulator_GenerateCommonTextures();

extern void Emulator_DoPollEvent();
extern void Emulator_UpdateInput(int poll);
extern void Emulator_CreateMemoryCard(int channel);

#if defined(OGL)
extern int Emulator_InitialiseGLContext(char* windowName);
#elif defined(D3D11)
extern void Emulator_CreateConstantBuffers();
extern void Emulator_UpdateProjectionConstantBuffer(float* ortho);
extern void Emulator_SetConstantBuffers();
extern void Emulator_DestroyConstantBuffers();
extern void Emulator_CreateRasterState(int wireframe);
//extern void Emulator_SetDefaultRenderTarget();
#elif defined(D3D12)
extern void Emulator_CreateConstantBuffers();
extern void Emulator_UpdateProjectionConstantBuffer(float* ortho);
extern void Emulator_SetConstantBuffers();
extern void Emulator_CreateRasterState(int wireframe);
extern void Emulator_SetDefaultRenderTarget();
extern void Emulator_WaitForPreviousFrame();
extern void Emulator_BeginPass();
extern void Emulator_EndPass();
extern int Emulator_BeginCommandBuffer();
extern void Emulator_EndCommandBuffer();
extern void Emulator_SetShader(const ShaderID shader);
extern void Emulator_DestroyGlobalShaders();
void Emulator_CreateGraphicsPipelineState(ShaderID* shader, D3D12_GRAPHICS_PIPELINE_STATE_DESC* pso);
#endif

extern int Emulator_GetWindowWidth();
extern int Emulator_GetWindowHeight();


#if defined(D3D9) || defined(XED3D)
extern IDirect3DDevice9* d3ddev;
#endif

#endif