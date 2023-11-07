#include "LIBGPU.H"
#include "EMULATOR_RENDER_D3D9.H"
#include "Core/Debug/EMULATOR_LOG.H"
#include "Core/Render/EMULATOR_RENDER_COMMON.H"
#include <stdio.h>


#if defined(D3D9)

extern void Emulator_DoPollEvent();
extern void Emulator_WaitForTimestep(int count);
extern void Emulator_GenerateCommonTextures();
extern void Emulator_CreateGlobalShaders();
extern void Emulator_DestroyTextures();
extern void Emulator_DestroyGlobalShaders();
extern void Emulator_CreateVertexBuffer();
extern void Emulator_CreateIndexBuffer();

const char* renderBackendName = "D3D9";

IDirect3DVertexBuffer9* dynamic_vertex_buffer = NULL;
IDirect3DIndexBuffer9* dynamic_index_buffer = NULL;
IDirect3D9* d3d;
IDirect3DDevice9* d3ddev;
D3DPRESENT_PARAMETERS  d3dpp;

SDL_Window* g_window = NULL;

HWND g_overrideHWND = NULL;
int g_overrideWidth = -1;
int g_overrideHeight = -1;

#include "shaders/D3D9/gte_shader_4_vs.h"
#include "shaders/D3D9/gte_shader_4_ps.h"
#include "shaders/D3D9/gte_shader_8_vs.h"
#include "shaders/D3D9/gte_shader_8_ps.h"
#include "shaders/D3D9/gte_shader_16_vs.h"
#include "shaders/D3D9/gte_shader_16_ps.h"
#include "shaders/D3D9/blit_shader_vs.h"
#include "shaders/D3D9/blit_shader_ps.h"

// shader registers
const int u_Projection = 0;

LPDIRECT3DVERTEXDECLARATION9 vertexDecl;

ShaderID Shader_Compile_Internal(const DWORD* vs_data, const DWORD* ps_data)
{
	ShaderID shader;
	HRESULT hr;
	hr = d3ddev->CreateVertexShader(vs_data, &shader.VS);
	assert(!FAILED(hr));
	hr = d3ddev->CreatePixelShader(ps_data, &shader.PS);
	assert(!FAILED(hr));
	return shader;
}

void Emulator_DestroyVertexBuffer()
{
	if (dynamic_vertex_buffer)
	{
		dynamic_vertex_buffer->Release();
		dynamic_vertex_buffer = NULL;
	}
}

void Emulator_DestroyIndexBuffer()
{
	if (dynamic_index_buffer)
	{
		dynamic_index_buffer->Release();
		dynamic_index_buffer = NULL;
	}
}

void Emulator_ResetDevice(int recreate)
{
	if (!g_resettingDevice)
	{
		g_resettingDevice = TRUE;

		Emulator_DestroyVertexBuffer();

		Emulator_DestroyIndexBuffer();

		Emulator_DestroyTextures();

		Emulator_DestroyGlobalShaders();

		if (recreate)
		{
			Emulator_CreateGlobalShaders();

			Emulator_GenerateCommonTextures();

			d3dpp.PresentationInterval = g_swapInterval ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
			d3dpp.BackBufferWidth = Emulator_GetWindowWidth();
			d3dpp.BackBufferHeight = Emulator_GetWindowHeight();
			HRESULT hr = d3ddev->Reset(&d3dpp);
			assert(!FAILED(hr));

			Emulator_CreateVertexBuffer();

			Emulator_CreateIndexBuffer();
		}

		g_resettingDevice = FALSE;
	}


	d3ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	d3ddev->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	d3ddev->SetSamplerState(1, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
}

void Emulator_DestroyTextures()
{
	if (whiteTexture != NULL)
	{
		whiteTexture->Release();
		whiteTexture = NULL;
	}

	if (rg8lutTexture != NULL)
	{
		rg8lutTexture->Release();
		rg8lutTexture = NULL;
	}

	if (vramTexture != NULL)
	{
		vramTexture->Release();
		vramTexture = NULL;
	}
}

void Emulator_DestroyGlobalShaders()
{
	if (g_gte_shader_4.VS != NULL)
	{
		g_gte_shader_4.VS->Release();
		g_gte_shader_4.VS = NULL;
	}

	if (g_gte_shader_4.PS != NULL)
	{
		g_gte_shader_4.PS->Release();
		g_gte_shader_4.PS = NULL;
	}

	if (g_gte_shader_8.VS != NULL)
	{
		g_gte_shader_8.VS->Release();
		g_gte_shader_8.VS = NULL;
	}

	if (g_gte_shader_8.PS != NULL)
	{
		g_gte_shader_8.PS->Release();
		g_gte_shader_8.PS = NULL;
	}

	if (g_gte_shader_16.VS != NULL)
	{
		g_gte_shader_16.VS->Release();
		g_gte_shader_16.VS = NULL;
	}

	if (g_gte_shader_16.PS != NULL)
	{
		g_gte_shader_16.PS->Release();
		g_gte_shader_16.PS = NULL;
	}

	if (g_blit_shader.VS != NULL)
	{
		g_blit_shader.VS->Release();
		g_blit_shader.VS = NULL;
	}

	if (g_blit_shader.PS != NULL)
	{
		g_blit_shader.PS->Release();
		g_blit_shader.PS = NULL;
	}
}

int Emulator_InitialiseD3D9Context(char* windowName)
{
#if defined(SDL2)
	if (g_overrideHWND == NULL)
	{
		g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
		if (g_window == NULL)
		{
			eprinterr("Failed to initialise SDL window!\n");
			return FALSE;
		}
	}

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);
#endif
	memset(&d3dpp, 0, sizeof(d3dpp));
	
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = Emulator_GetWindowWidth();
	d3dpp.BackBufferHeight = Emulator_GetWindowHeight();
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_overrideHWND == NULL ? wmInfo.info.win.window : g_overrideHWND;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) 
	{
		eprinterr("Failed to initialise D3D9\n");
		return FALSE;
	}

	HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	if (FAILED(hr)) 
	{
		eprinterr("Failed to obtain D3D9 device!\n");
		return FALSE;
	}

	return TRUE;
}

void Emulator_CreateGlobalShaders()
{
	g_gte_shader_4 = Shader_Compile(gte_shader_4);
	g_gte_shader_8 = Shader_Compile(gte_shader_8);
	g_gte_shader_16 = Shader_Compile(gte_shader_16);
	g_blit_shader = Shader_Compile(blit_shader);
}

unsigned char pixelData[64 * 64 * sizeof(unsigned int)];

void Emulator_GenerateCommonTextures()
{
	memset(pixelData, 0xFF, sizeof(pixelData));

	HRESULT hr = d3ddev->CreateTexture(64, 64, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &whiteTexture, NULL);
	assert(!FAILED(hr));
	D3DLOCKED_RECT rect;
	hr = whiteTexture->LockRect(0, &rect, NULL, 0);
	assert(!FAILED(hr));
	memcpy(rect.pBits, &pixelData, sizeof(pixelData));
	whiteTexture->UnlockRect(0);

	hr = d3ddev->CreateTexture(LUT_WIDTH, LUT_HEIGHT, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &rg8lutTexture, NULL);
	assert(!FAILED(hr));
	hr = rg8lutTexture->LockRect(0, &rect, NULL, 0);
	assert(!FAILED(hr));
	memcpy(rect.pBits, Emulator_GenerateRG8LUT(), 256 * 256 * 4);
	rg8lutTexture->UnlockRect(0);

	hr = d3ddev->CreateTexture(VRAM_WIDTH, VRAM_HEIGHT, 1, 0, D3DFMT_A8L8, D3DPOOL_MANAGED, &vramTexture, NULL);
	assert(!FAILED(hr));

	vram_need_update = TRUE;
}

void Emulator_CreateVertexBuffer()
{
	HRESULT hr = d3ddev->CreateVertexBuffer(sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, &dynamic_vertex_buffer, NULL);

	assert(!FAILED(hr));

	hr = d3ddev->SetStreamSource(0, dynamic_vertex_buffer, 0, sizeof(struct Vertex));

	assert(!FAILED(hr));

#define OFFSETOF(T, E)     ((size_t)&(((T*)0)->E))

	const D3DVERTEXELEMENT9 VERTEX_DECL[] = {
#if defined(PGXP)
		{0, OFFSETOF(Vertex, x), D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // a_position
#else
		{0, OFFSETOF(Vertex, x), D3DDECLTYPE_SHORT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // a_position
#endif
		{0, OFFSETOF(Vertex, u), D3DDECLTYPE_UBYTE4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0}, // a_texcoord
		{0, OFFSETOF(Vertex, r), D3DDECLTYPE_UBYTE4N,  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0}, // a_color
		D3DDECL_END()
	};

	d3ddev->CreateVertexDeclaration(VERTEX_DECL, &vertexDecl);

#undef OFFSETOF
}

void Emulator_CreateIndexBuffer()
{
	HRESULT hr = d3ddev->CreateIndexBuffer(sizeof(unsigned short) * MAX_NUM_INDEX_BUFFER_INDICES, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &dynamic_index_buffer, NULL);

	assert(!FAILED(hr));

	d3ddev->SetIndices(dynamic_index_buffer);
}

int Emulator_CreateCommonResources()
{
	memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

	Emulator_GenerateCommonTextures();
	
	Emulator_CreateGlobalShaders();

	Emulator_CreateVertexBuffer();

	Emulator_CreateIndexBuffer();

	Emulator_ResetDevice(TRUE);

	return TRUE;
}

void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
{
	float a = 2.0f / (right - left);
	float b = 2.0f / (top - bottom);
	float c = 2.0f / (znear - zfar);

	float x = (left + right) / (left - right);
	float y = (bottom + top) / (bottom - top);
	float z = znear / (znear - zfar);


	float ortho[16] = {
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		x, y, z, 1
	};

	d3ddev->SetVertexShaderConstantF(u_Projection, ortho, 4);
}

void Emulator_SetShader(const ShaderID shader)
{
	d3ddev->SetVertexShader(shader.VS);
	d3ddev->SetPixelShader(shader.PS);

	Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0.0f, 0.0f, 1.0f);
}

void Emulator_SetTextureAndShader(TextureID texture, ShaderID shader)
{
	Emulator_SetShader(shader);

	if (g_texturelessMode) {
		texture = whiteTexture;
	}

	if (g_lastBoundTexture[0] == texture && g_lastBoundTexture[1] == rg8lutTexture) {
		//return;
	}

	d3ddev->SetTexture(0, texture);
	d3ddev->SetTexture(1, rg8lutTexture);

	g_lastBoundTexture[0] = texture;
	g_lastBoundTexture[1] = rg8lutTexture;
}

void Emulator_SetTexture(TextureID texture, TexFormat texFormat)
{
	switch (texFormat)
	{
	case TF_4_BIT:
		Emulator_SetShader(g_gte_shader_4);
		break;
	case TF_8_BIT:
		Emulator_SetShader(g_gte_shader_8);
		break;
	case TF_16_BIT:
		Emulator_SetShader(g_gte_shader_16);
		break;
	}

	if (g_texturelessMode) {
		texture = whiteTexture;
	}

	if (g_lastBoundTexture[0] == texture && g_lastBoundTexture[1] == rg8lutTexture) {
		//return;
	}

	d3ddev->SetTexture(0, texture);
	d3ddev->SetTexture(1, rg8lutTexture);

	g_lastBoundTexture[0] = texture;
	g_lastBoundTexture[1] = rg8lutTexture;
}

void Emulator_DestroyTexture(TextureID texture)
{
	texture->Release();
}

void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000 | (r << 16) | (g << 8) | (b), 1.0f, 0);
}

#define NOFILE 0

void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif
	FILE* f = fopen(outputFileName, "wb");

	if (f == NULL)
	{
		return;
	}

	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6];
	header[0] = (width % 256);
	header[1] = (width / 256);
	header[2] = (height % 256);
	header[3] = (height / 256);
	header[4] = 16;
	header[5] = 0;

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);

	//512 const is hdd sector size
	int numSectorsToWrite = (width * height * sizeof(unsigned short)) / 512;
	int numRemainingSectorsToWrite = (width * height * sizeof(unsigned short)) % 512;

	for (int i = 0; i < numSectorsToWrite; i++)
	{
		fwrite(&vram[i * 512 / sizeof(unsigned short)], 512, 1, f);
	}

	for (int i = 0; i < numRemainingSectorsToWrite; i++)
	{
		fwrite(&vram[numSectorsToWrite * 512 / sizeof(unsigned short)], numRemainingSectorsToWrite, 1, f);
	}

	fclose(f);
}

void Emulator_StoreFrameBuffer(int x, int y, int w, int h)
{
	short* fb = (short*)malloc(w * h * sizeof(short));

	IDirect3DSurface9* srcSurface, * dstSurface;
	HRESULT hr;
	D3DLOCKED_RECT rect;
	hr = d3ddev->GetRenderTarget(0, &srcSurface);
	assert(!FAILED(hr));
	
	hr = d3ddev->CreateOffscreenPlainSurface(windowWidth, windowHeight, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &dstSurface, NULL);
	assert(!FAILED(hr));
	hr = d3ddev->GetRenderTargetData(srcSurface, dstSurface);
	assert(!FAILED(hr));
	
	hr = dstSurface->LockRect(&rect, NULL, D3DLOCK_READONLY);
	assert(!FAILED(hr));
	assert(windowWidth * 4 == rect.Pitch);

	int* data = (int*)rect.pBits;

#define FLIP_Y (fy)
	
	unsigned int* data_src = (unsigned int*)data;
	unsigned short* data_dst = (unsigned short*)fb;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			unsigned int  c = *data_src++;
			unsigned char b = ((c >> 3) & 0x1F);
			unsigned char g = ((c >> 11) & 0x1F);
			unsigned char r = ((c >> 19) & 0x1F);
#if defined(SWAP_RB)
			*data_dst++ = b | (g << 5) | (r << 10) | 0x8000;
#else
			* data_dst++ = r | (g << 5) | (b << 10) | 0x8000;
#endif
		}
	}

	short* ptr = (short*)vram + VRAM_WIDTH * y + x;

	for (int fy = 0; fy < h; fy++) {
		short* fb_ptr = fb + (h * FLIP_Y / h) * w;

		for (int fx = 0; fx < w; fx++) {
			ptr[fx] = fb_ptr[w * fx / w];
		}

		ptr += VRAM_WIDTH;
	}

	dstSurface->UnlockRect();
	dstSurface->Release();
	srcSurface->Release();

#undef FLIP_Y

	free(fb);

	vram_need_update = TRUE;
}

void Emulator_UpdateVRAM()
{
	if (!vram_need_update) {
		return;
	}
	vram_need_update = FALSE;

	D3DLOCKED_RECT rect;
	HRESULT hr = vramTexture->LockRect(0, &rect, NULL, 0);
	assert(!FAILED(hr));
	memcpy(rect.pBits, vram, VRAM_WIDTH * VRAM_HEIGHT * sizeof(short));
	vramTexture->UnlockRect(0);
}

void Emulator_SetWireframe(int enable)
{
	d3ddev->SetRenderState(D3DRS_FILLMODE, enable ? D3DFILL_WIREFRAME : D3DFILL_SOLID);
}

void Emulator_SetBlendMode(BlendMode blendMode)
{
	if (g_PreviousBlendMode == blendMode)
	{
		return;
	}

	if (g_PreviousBlendMode == BM_NONE)
	{
		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	switch (blendMode)
	{
	case BM_NONE:
		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		break;
	case BM_AVERAGE:
		d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(128, 128, 128, 128));
		d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);
		break;
	case BM_ADD:
		d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case BM_SUBTRACT:
		d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case BM_ADD_QUATER_SOURCE:
		d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(64, 64, 64, 64));
		d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	}

	g_PreviousBlendMode = blendMode;
}

void Emulator_DrawTriangles(int start_vertex, int start_index, int triangles)
{
	if (triangles <= 0)
		return;
	
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, triangles * 3, start_index, triangles);
}

void Emulator_UpdateVertexBuffer(const struct Vertex* vertices, int num_vertices, int vertex_start_index, int use_offset)
{
	assert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);

	if (num_vertices <= 0)
		return;

	void* ptr;
	dynamic_vertex_buffer->Lock(vertex_start_index * sizeof(Vertex), num_vertices * sizeof(Vertex), &ptr, 0);

	if (use_offset)
	{
		vertices += vertex_start_index;
	}

	memcpy(ptr, vertices, num_vertices * sizeof(Vertex));
	dynamic_vertex_buffer->Unlock();

	vbo_was_dirty_flag = TRUE;
}

void Emulator_UpdateIndexBuffer(const unsigned short* indices, int num_indices, int face_start_index, int use_offset)
{
	assert(num_indices <= MAX_NUM_INDEX_BUFFER_INDICES);

	if (num_indices <= 0)
		return;

	void* ptr;
	dynamic_index_buffer->Lock(face_start_index * sizeof(unsigned short), num_indices * sizeof(unsigned short), &ptr, 0);
	
	if (use_offset)
	{
		indices += face_start_index;
	}
	
	memcpy(ptr, indices, num_indices * sizeof(unsigned short));
	dynamic_index_buffer->Unlock();
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
	short offset_x = activeDispEnv.screen.x;
	short offset_y = activeDispEnv.screen.y;

	D3DVIEWPORT9 viewport;
	viewport.X = x + offset_x;
	viewport.Y = y + offset_y;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	d3ddev->SetViewport(&viewport);
}

void Emulator_SwapWindow()
{
	unsigned int timer = 1;

	Emulator_WaitForTimestep(1);

	if (d3ddev->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST) {
		Emulator_ResetDevice(TRUE);
	}
}

void Emulator_WaitForTimestep(int count)
{
	if (g_swapInterval > 0)
	{
		int delta = g_swapTime + FIXED_TIME_STEP * count - Emulator_GetTicks();

		if (delta > 0) {
			SDL_Delay(delta);
		}
	}

	g_swapTime = Emulator_GetTicks();
}

void Emulator_SetRenderTarget(const RenderTargetID& frameBufferObject)
{
	d3ddev->SetRenderTarget(0, frameBufferObject);
}

#endif