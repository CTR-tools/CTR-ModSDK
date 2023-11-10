#include "LIBGPU.H"
#include "EMULATOR_RENDER_D3D11.H"
#include "Core/Debug/EMULATOR_LOG.H"
#include "Core/Render/EMULATOR_RENDER_COMMON.H"
#include <stdio.h>

#if defined(D3D11)

extern void Emulator_DoPollEvent();
extern void Emulator_WaitForTimestep(int count);
extern void Emulator_GenerateCommonTextures();
extern void Emulator_CreateGlobalShaders();
extern void Emulator_DestroyTextures();
extern void Emulator_DestroyGlobalShaders();
extern void Emulator_CreateConstantBuffers();
extern void Emulator_DestroyConstantBuffers();
extern void Emulator_CreateRasterState(int wireframe);
extern void Emulator_UpdateProjectionConstantBuffer(float* ortho);
extern void Emulator_SetConstantBuffers();
extern void Emulator_CreateVertexBuffer();
extern void Emulator_CreateIndexBuffer();

const char* renderBackendName = "D3D11";

int g_actualOverrideIndex = -1;
HWND g_overrideHWND =  NULL;
int g_overrideWidth =  -1;
int g_overrideHeight = -1;

ID3D11Texture2D* vramBaseTexture = NULL;
ID3D11Buffer* dynamic_vertex_buffer = NULL;
ID3D11Buffer* dynamic_index_buffer = NULL;
ID3D11Device* d3ddev = NULL;
ID3D11DeviceContext* d3dcontext = NULL;

#if defined(UWP)
IDXGISwapChain1* swapChain = NULL;
IDXGIDevice3* dxgiDevice = NULL;
IDXGIAdapter* dxgiAdapter = NULL;
IDXGIFactory2* dxgiFactory = NULL;
#else
IDXGISwapChain* swapChain = NULL;
IDXGIDevice* dxgiDevice = NULL;
IDXGIAdapter* dxgiAdapter = NULL;
IDXGIFactory* dxgiFactory = NULL;
#endif
ID3D11RenderTargetView* renderTargetView = NULL;
ID3D11Buffer* projectionMatrixBuffer = NULL;
ID3D11SamplerState* samplerState = NULL;
ID3D11SamplerState* rg8lutSamplerState = NULL;
ID3D11BlendState* blendState = NULL;
ID3D11RasterizerState* rasterState = NULL;

SDL_Window* g_window = NULL;

#include "shaders/D3D11/gte_shader_4_vs.h"
#include "shaders/D3D11/gte_shader_4_ps.h"
#include "shaders/D3D11/gte_shader_8_vs.h"
#include "shaders/D3D11/gte_shader_8_ps.h"
#include "shaders/D3D11/gte_shader_16_vs.h"
#include "shaders/D3D11/gte_shader_16_ps.h"
#include "shaders/D3D11/blit_shader_vs.h"
#include "shaders/D3D11/blit_shader_ps.h"


#define Shader_Compile(name) Shader_Compile_Internal((DWORD*)name##_vs, (DWORD*)name##_ps, sizeof(name##_vs), sizeof(name##_ps))

ShaderID Shader_Compile_Internal(const DWORD* vs_data, const DWORD* ps_data, const unsigned int vs_size, const unsigned int ps_size)
{
	ShaderID shader;
	HRESULT hr;

	hr = d3ddev->CreateVertexShader(vs_data, vs_size, NULL, &shader.VS);
	eassert(!FAILED(hr));
	hr = d3ddev->CreatePixelShader(ps_data, ps_size, NULL, &shader.PS);
	eassert(!FAILED(hr));
#define OFFSETOF(T, E)     ((size_t)&(((T*)0)->E))

	const D3D11_INPUT_ELEMENT_DESC INPUT_LAYOUT[] =
	{
#if defined(PGXP)
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, OFFSETOF(Vertex, x), D3D11_INPUT_PER_VERTEX_DATA, 0 },
#else	
		{ "POSITION", 0, DXGI_FORMAT_R16G16B16A16_SINT,  0, OFFSETOF(Vertex, x), D3D11_INPUT_PER_VERTEX_DATA, 0 },
#endif
		{ "TEXCOORD", 0, DXGI_FORMAT_R8G8B8A8_UINT,		 0, OFFSETOF(Vertex, u), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,	 0, OFFSETOF(Vertex, r), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = d3ddev->CreateInputLayout(INPUT_LAYOUT, sizeof(INPUT_LAYOUT) / sizeof(D3D11_INPUT_ELEMENT_DESC), vs_data, vs_size, &shader.IL);
	eassert(!FAILED(hr));

#undef OFFSETOF

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

void Emulator_DestroyRasterState()
{
	d3dcontext->RSSetState(NULL);

	if (rasterState != NULL)
	{
		rasterState->Release();
		rasterState = NULL;
	}
}

void Emulator_DestroySamplerStates()
{
	ID3D11SamplerState* samplerStates[2] = { NULL, NULL };

	d3dcontext->PSSetSamplers(0, 2, samplerStates);

	if (samplerState != NULL)
	{
		samplerState->Release();
		samplerState = NULL;
	}

	if (rg8lutSamplerState != NULL)
	{
		rg8lutSamplerState->Release();
		rg8lutSamplerState = NULL;
	}
}

void Emulator_DestroyBlendState()
{
	FLOAT blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	d3dcontext->OMSetBlendState(NULL, blendFactor, -1);
	
	if (blendState != NULL)
	{
		blendState->Release();
		blendState = NULL;
	}
}

void Emulator_DestroySwapChain()
{
	if (swapChain != NULL)
	{
		swapChain->Release();
		swapChain = NULL;
	}

	if (dxgiDevice != NULL)
	{
		dxgiDevice->Release();
		dxgiDevice = NULL;
	}

	if (dxgiAdapter != NULL)
	{
		dxgiAdapter->Release();
		dxgiAdapter = NULL;
	}

	if (dxgiFactory != NULL)
	{
		dxgiFactory->Release();
		dxgiFactory = NULL;
	}
}

void Emulator_DestroyBackBufferView()
{
	if (renderTargetView != NULL)
	{
		ID3D11RenderTargetView* nullViews[] = { NULL };
		d3dcontext->OMSetRenderTargets(_countof(nullViews), nullViews, NULL);

		renderTargetView->Release();
		renderTargetView = NULL;
	}
}

void Emulator_DestroyD3D11Context()
{
	if (d3dcontext != NULL)
	{
		d3dcontext->Flush();
		d3dcontext->ClearState();
		d3dcontext->Release();
		d3dcontext = NULL;
	}
}

void Emulator_DestroyD3D11Device()
{
	if (d3ddev != NULL)
	{
		d3ddev->Release();
		d3ddev = NULL;
	}
}

void Emulator_CreateD3D11Device()
{
#if defined(SDL2)
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);
#endif

	DXGI_MODE_DESC bd;
	ZeroMemory(&bd, sizeof(DXGI_MODE_DESC));

	bd.Width = Emulator_GetWindowWidth();
	bd.Height = Emulator_GetWindowHeight();
	bd.RefreshRate.Numerator = 60;
	bd.RefreshRate.Denominator = 1;
	bd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

#if defined(UWP)
	DXGI_SWAP_CHAIN_DESC1 sd;
#else
	DXGI_SWAP_CHAIN_DESC sd;
#endif
	memset(&sd, 0, sizeof(sd));
#if !defined(UWP)
	sd.Windowed = TRUE;
	sd.BufferDesc = bd;
#else
	sd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.Width = windowWidth;
	sd.Height = windowHeight;
#endif
#if !defined(UWP)
	sd.BufferCount = 1;
#else
	sd.BufferCount = 2;
#endif
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
#if !defined(UWP)
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
#else
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
#endif

#if defined(SDL2) && !defined(UWP_SDL2)
	sd.OutputWindow = g_overrideHWND == NULL ? wmInfo.info.win.window : g_overrideHWND;
#endif

#if defined(_DEBUG)
	unsigned int deviceCreationFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
	unsigned int deviceCreationFlags = 0;
#endif

#if defined(UWP)
	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceCreationFlags, NULL, 0, D3D11_SDK_VERSION, &d3ddev, NULL, &d3dcontext);
	assert(!FAILED(hr));

	///@FIXME Crash-UWP likely something not being free'd resulting in window not being free.
	assert(!FAILED(hr));
#else
	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceCreationFlags, NULL, 0, D3D11_SDK_VERSION, &d3ddev, NULL, &d3dcontext);
	eassert(!FAILED(hr));
#endif
}

void Emulator_CreateD3D11SwapChain()
{
#if defined(SDL2)
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);
#endif

	DXGI_MODE_DESC bd;
	ZeroMemory(&bd, sizeof(DXGI_MODE_DESC));

	bd.Width = Emulator_GetWindowWidth();
	bd.Height = Emulator_GetWindowHeight();
	bd.RefreshRate.Numerator = 60;
	bd.RefreshRate.Denominator = 1;
	bd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

#if defined(UWP)
	DXGI_SWAP_CHAIN_DESC1 sd;
#else
	DXGI_SWAP_CHAIN_DESC sd;
#endif
	memset(&sd, 0, sizeof(sd));
#if !defined(UWP)
	sd.Windowed = TRUE;
	sd.BufferDesc = bd;
#else
	sd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.Width = windowWidth;
	sd.Height = windowHeight;
#endif
#if !defined(UWP)
	sd.BufferCount = 1;
#else
	sd.BufferCount = 2;
#endif
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
#if !defined(UWP)
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
#else
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
#endif

#if defined(SDL2) && !defined(UWP_SDL2)
	sd.OutputWindow = g_overrideHWND == NULL ? wmInfo.info.win.window : g_overrideHWND;
#endif

#if defined(UWP)
	HRESULT hr = d3ddev->QueryInterface(__uuidof(IDXGIDevice3), (void**)&dxgiDevice);

	assert(!FAILED(hr));

	hr = dxgiDevice->GetAdapter(&dxgiAdapter);

	assert(!FAILED(hr));

	hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);

	assert(!FAILED(hr));

#if defined(UWP) && defined(SDL2)
	hr = dxgiFactory->CreateSwapChainForCoreWindow(d3ddev, reinterpret_cast<IUnknown*>(wmInfo.info.winrt.window), &sd, NULL, &swapChain);
#else
	hr = dxgiFactory->CreateSwapChainForComposition(d3ddev, &sd, NULL, &swapChain);
#endif

	///@FIXME Crash-UWP likely something not being free'd resulting in window not being free.
	assert(!FAILED(hr));
#else
	HRESULT hr = d3ddev->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	assert(!FAILED(hr));

	hr = dxgiDevice->GetAdapter(&dxgiAdapter);

	assert(!FAILED(hr));

	hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	assert(!FAILED(hr));

	hr = dxgiFactory->CreateSwapChain(d3ddev, &sd, &swapChain);
	eassert(!FAILED(hr));
#endif	
}

void Emulator_CreateBackBufferView()
{
	ID3D11Texture2D* backBuffer;
	HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	eassert(!FAILED(hr));

	hr = d3ddev->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	eassert(!FAILED(hr));

	backBuffer->Release();

	d3dcontext->OMSetRenderTargets(1, &renderTargetView, NULL);
}

void Emulator_ResetDevice(int recreate)
{
	if (!g_resettingDevice)
	{
		g_resettingDevice = TRUE;

		Emulator_DestroyVertexBuffer();

		Emulator_DestroyIndexBuffer();

		Emulator_DestroyTextures();

		Emulator_DestroySamplerStates();

		Emulator_DestroyGlobalShaders();

		Emulator_DestroyConstantBuffers();

		Emulator_DestroyRasterState();

		Emulator_DestroyBlendState();

		Emulator_DestroyBackBufferView();

		Emulator_DestroySwapChain();

		Emulator_DestroyD3D11Context();

#if defined(_DEBUG) && 1
		ID3D11Debug* debug;
		d3ddev->QueryInterface(IID_PPV_ARGS(&debug));
		debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		debug->Release();
#endif

		Emulator_DestroyD3D11Device();

		if (recreate)
		{
			Emulator_CreateD3D11Device();

			Emulator_CreateD3D11SwapChain();

			Emulator_CreateBackBufferView();

			Emulator_CreateGlobalShaders();

			Emulator_CreateConstantBuffers();

			Emulator_GenerateCommonTextures();

			Emulator_CreateVertexBuffer();

			Emulator_CreateIndexBuffer();
		}

		g_resettingDevice = FALSE;
	}
}

int Emulator_InitialiseD3D11Context(char* windowName)
{
#if defined(SDL2)
	SDL_SysWMinfo wmInfo;

	if (g_overrideHWND == NULL)
	{
		g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
		if (g_window == NULL)
		{
			eprinterr("Failed to initialise SDL window!\n");
			return FALSE;
		}
		
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(g_window, &wmInfo);
	}
#endif

	Emulator_CreateD3D11Device();

	Emulator_CreateD3D11SwapChain();

	Emulator_CreateBackBufferView();

	return TRUE;
}

void Emulator_CreateGlobalShaders()
{
	g_gte_shader_4 = Shader_Compile(gte_shader_4);
	g_gte_shader_8 = Shader_Compile(gte_shader_8);
	g_gte_shader_16 = Shader_Compile(gte_shader_16);
	g_blit_shader = Shader_Compile(blit_shader);
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

	if (vramBaseTexture != NULL)
	{
		vramBaseTexture->Release();
		vramBaseTexture = NULL;
	}
}

void Emulator_DestroyGlobalShaders()
{
	d3dcontext->VSSetShader(NULL, NULL, 0);
	d3dcontext->PSSetShader(NULL, NULL, 0);
	d3dcontext->IASetInputLayout(NULL);

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

	if (g_gte_shader_4.IL != NULL)
	{
		g_gte_shader_4.IL->Release();
		g_gte_shader_4.IL  = NULL;
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

	if (g_gte_shader_8.IL != NULL)
	{
		g_gte_shader_8.IL->Release();
		g_gte_shader_8.IL = NULL;
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

	if (g_gte_shader_16.IL != NULL)
	{
		g_gte_shader_16.IL->Release();
		g_gte_shader_16.IL = NULL;
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

	if (g_blit_shader.IL != NULL)
	{
		g_blit_shader.IL->Release();
		g_blit_shader.IL = NULL;
	}
}

unsigned char pixelData[64 * 64 * sizeof(unsigned int)];

void Emulator_GenerateCommonTextures()
{
	memset(pixelData, 0xFF, sizeof(pixelData));

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = 64;
	td.Height = 64;
	td.MipLevels = td.ArraySize = 1;
	td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	ID3D11Texture2D* t = NULL;

	D3D11_SUBRESOURCE_DATA srd;
	ZeroMemory(&srd, sizeof(srd));
	srd.pSysMem = (void*)&pixelData;
	srd.SysMemPitch = td.Width * sizeof(unsigned int);
	srd.SysMemSlicePitch = 0;

	HRESULT hr = d3ddev->CreateTexture2D(&td, &srd, &t);
	eassert(!FAILED(hr));
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = td.MipLevels;
	srvd.Texture2D.MostDetailedMip = 0;
	hr = d3ddev->CreateShaderResourceView(t, &srvd, &whiteTexture);
	eassert(!FAILED(hr));
	t->Release();

	ZeroMemory(&td, sizeof(td));
	td.Width = LUT_WIDTH;
	td.Height = LUT_HEIGHT;
	td.MipLevels = td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	t = NULL;

	ZeroMemory(&srd, sizeof(srd));
	srd.pSysMem = (void*)Emulator_GenerateRG8LUT();
	srd.SysMemPitch = td.Width * sizeof(unsigned int);
	srd.SysMemSlicePitch = 0;

	hr = d3ddev->CreateTexture2D(&td, &srd, &t);
	eassert(!FAILED(hr));
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = td.MipLevels;
	srvd.Texture2D.MostDetailedMip = 0;
	hr = d3ddev->CreateShaderResourceView(t, &srvd, &rg8lutTexture);
	eassert(!FAILED(hr));
	t->Release();

	ZeroMemory(&td, sizeof(td));
	td.ArraySize = 1;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	td.Format = DXGI_FORMAT_R8G8_UNORM;
	td.Width = VRAM_WIDTH;
	td.Height = VRAM_HEIGHT;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DYNAMIC;

	hr = d3ddev->CreateTexture2D(&td, NULL, &vramBaseTexture);
	eassert(!FAILED(hr));

	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;

	hr = d3ddev->CreateShaderResourceView(vramBaseTexture, &srvd, &vramTexture);
	
	vram_need_update = TRUE;

	eassert(!FAILED(hr));
}

void Emulator_CreateVertexBuffer()
{
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;

	HRESULT hr = d3ddev->CreateBuffer(&vbd, NULL, &dynamic_vertex_buffer);
	eassert(!FAILED(hr));

	UINT offset = 0;
	UINT stride = sizeof(Vertex);

	d3dcontext->IASetVertexBuffers(0, 1, &dynamic_vertex_buffer, &stride, &offset);
}

void Emulator_CreateIndexBuffer()
{
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(unsigned short) * MAX_NUM_INDEX_BUFFER_INDICES;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;

	HRESULT hr = d3ddev->CreateBuffer(&ibd, NULL, &dynamic_index_buffer);
	eassert(!FAILED(hr));

	d3dcontext->IASetIndexBuffer(dynamic_index_buffer, DXGI_FORMAT_R16_UINT, 0);

	d3dcontext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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

	Emulator_UpdateProjectionConstantBuffer(&ortho[0]);
	Emulator_SetConstantBuffers();
}

void Emulator_SetShader(const ShaderID shader)
{
	d3dcontext->VSSetShader(shader.VS, NULL, 0);
	d3dcontext->PSSetShader(shader.PS, NULL, 0);
	d3dcontext->IASetInputLayout(shader.IL);

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

	d3dcontext->PSSetShaderResources(0, 1, &texture);
	d3dcontext->PSSetShaderResources(1, 1, &rg8lutTexture);

	if (samplerState == NULL)
	{
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.MinLOD = -D3D11_FLOAT32_MAX;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		sampDesc.MaxAnisotropy = 1;
		d3ddev->CreateSamplerState(&sampDesc, &samplerState);
	}

	if (rg8lutSamplerState == NULL)
	{
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.MinLOD = -D3D11_FLOAT32_MAX;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		sampDesc.MaxAnisotropy = 1;
		d3ddev->CreateSamplerState(&sampDesc, &rg8lutSamplerState);
	}

	ID3D11SamplerState* samplerStates[2] = { samplerState, rg8lutSamplerState };

	d3dcontext->PSSetSamplers(0, 2, samplerStates);

	//g_lastBoundTexture[0] = texture;
	//g_lastBoundTexture[1] = rg8lutTexture;
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

	d3dcontext->PSSetShaderResources(0, 1, &texture);
	d3dcontext->PSSetShaderResources(1, 1, &rg8lutTexture);

	if (samplerState == NULL)
	{
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.MinLOD = -D3D11_FLOAT32_MAX;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		sampDesc.MaxAnisotropy = 1;
		d3ddev->CreateSamplerState(&sampDesc, &samplerState);
	}

	if (rg8lutSamplerState == NULL)
	{
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.MinLOD = -D3D11_FLOAT32_MAX;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		sampDesc.MaxAnisotropy = 1;
		d3ddev->CreateSamplerState(&sampDesc, &rg8lutSamplerState);
	}

	ID3D11SamplerState* samplerStates[2] = { samplerState, rg8lutSamplerState };

	d3dcontext->PSSetSamplers(0, 2, samplerStates);

	g_lastBoundTexture[0] = texture;
	g_lastBoundTexture[1] = rg8lutTexture;
}

void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
	FLOAT clearColor[4]{ r / 255.0f, g / 255.0f, b / 255.0f, 1.0f };
	d3dcontext->ClearRenderTargetView(renderTargetView, clearColor);
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

	ID3D11Texture2D* backBuffer;
	HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	eassert(!FAILED(hr));
	ID3D11Texture2D* newBackBuffer = NULL;
	D3D11_TEXTURE2D_DESC description;
	backBuffer->GetDesc(&description);
	description.BindFlags = 0;
	description.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	description.Usage = D3D11_USAGE_STAGING;
	hr = d3ddev->CreateTexture2D(&description, NULL, &newBackBuffer);
	eassert(!FAILED(hr));
	d3dcontext->CopyResource(newBackBuffer, backBuffer);
	D3D11_MAPPED_SUBRESOURCE resource;
	unsigned int subResource = D3D11CalcSubresource(0, 0, 0);
	hr = d3dcontext->Map(newBackBuffer, subResource, D3D11_MAP_READ_WRITE, 0, &resource);
	eassert(!FAILED(hr));

	int* data = (int*)resource.pData;

#define FLIP_Y (fy)
#define SWAP_RB

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

	d3dcontext->Unmap(newBackBuffer, subResource);
	newBackBuffer->Release();

#undef FLIP_Y

	free(fb);

	vram_need_update = TRUE;
}

void Emulator_CreateConstantBuffers()
{
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = sizeof(float) * 16;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = 0;
	cbd.MiscFlags = 0;
	HRESULT hr = d3ddev->CreateBuffer(&cbd, NULL, &projectionMatrixBuffer);
	eassert(SUCCEEDED(hr));
}

void Emulator_UpdateProjectionConstantBuffer(float* ortho)
{
	d3dcontext->UpdateSubresource(projectionMatrixBuffer, 0, NULL, ortho, 0, 0);
}

void Emulator_SetConstantBuffers()
{
	d3dcontext->VSSetConstantBuffers(0, 1, &projectionMatrixBuffer);
}

void Emulator_DestroyConstantBuffers()
{
	if (projectionMatrixBuffer != NULL)
	{
		projectionMatrixBuffer->Release();
		projectionMatrixBuffer = NULL;
	}
}

void Emulator_CreateRasterState(int wireframe)
{
	if (rasterState != NULL)
	{
		rasterState->Release();
		rasterState = NULL;
	}

	D3D11_RASTERIZER_DESC rsd;
	ZeroMemory(&rsd, sizeof(rsd));
	rsd.FillMode = wireframe ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
	rsd.CullMode = D3D11_CULL_NONE;
	rsd.FrontCounterClockwise = FALSE;
	rsd.DepthBias = FALSE;
	rsd.DepthBiasClamp = 0;
	rsd.SlopeScaledDepthBias = 0;
	rsd.DepthClipEnable = FALSE;
	rsd.ScissorEnable = FALSE;
	rsd.MultisampleEnable = FALSE;
	rsd.AntialiasedLineEnable = FALSE;
	HRESULT hr = d3ddev->CreateRasterizerState(&rsd, &rasterState);
	eassert(!FAILED(hr));
	d3dcontext->RSSetState(rasterState);
}

void Emulator_UpdateVRAM()
{
	if (!vram_need_update) {
		return;
	}
	vram_need_update = FALSE;

	D3D11_MAPPED_SUBRESOURCE sr;
	HRESULT hr = d3dcontext->Map(vramBaseTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &sr);
	eassert(!FAILED(hr));
	memcpy(sr.pData, vram, VRAM_WIDTH * VRAM_HEIGHT * sizeof(short));
	d3dcontext->Unmap(vramBaseTexture, 0);
}

void Emulator_SetWireframe(int enable)
{
	Emulator_CreateRasterState(enable ? TRUE : FALSE);
}

void Emulator_SetBlendMode(BlendMode blendMode)
{
	if (g_PreviousBlendMode == blendMode)
	{
		return;
	}

	if (blendState != NULL)
	{
		blendState->Release();
		blendState = NULL;
	}

	switch (blendMode)
	{
	case BM_NONE:
	{
		d3dcontext->OMSetBlendState(NULL, 0, -1);
		break;
	}
	case BM_AVERAGE:
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = TRUE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		eassert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 128.0f * (1.0f / 255.0f), 128.0f * (1.0f / 255.0f), 128.0f * (1.0f / 255.0f), 128.0f * (1.0f / 255.0f) };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
		break;
	}
	case BM_ADD:
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = TRUE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		eassert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
		break;
	}
	case BM_SUBTRACT:
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = TRUE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		eassert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
		break;
	}
	case BM_ADD_QUATER_SOURCE:
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = TRUE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		eassert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 64.0f * (1.0f / 255.0f), 64.0f * (1.0f / 255.0f), 64.0f * (1.0f / 255.0f), 64.0f * (1.0f / 255.0f) };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
		break;
	}
	}

	g_PreviousBlendMode = blendMode;
}

void Emulator_DrawTriangles(int start_vertex, int start_index, int triangles)
{
	if (triangles <= 0)
		return;

	d3dcontext->DrawIndexed(triangles * 3, start_index, 0);
}

void Emulator_UpdateVertexBuffer(const struct Vertex* vertices, int num_vertices, int vertex_start_index, int use_offset)
{
	eassert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);

	if (num_vertices <= 0)
		return;

	D3D11_MAPPED_SUBRESOURCE sr;
	d3dcontext->Map(dynamic_vertex_buffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &sr);
	
	if (use_offset)
	{
		vertices += vertex_start_index;
	}
	
	memcpy((struct Vertex*)sr.pData + vertex_start_index, vertices, num_vertices * sizeof(Vertex));
	d3dcontext->Unmap(dynamic_vertex_buffer, 0);

	vbo_was_dirty_flag = TRUE;
}

void Emulator_UpdateIndexBuffer(const unsigned short* indices, int num_indices, int face_start_index, int use_offset)
{
	eassert(num_indices <= MAX_NUM_INDEX_BUFFER_INDICES);

	if (num_indices <= 0)
		return;

	if (use_offset)
	{
		indices += face_start_index;
	}

	D3D11_MAPPED_SUBRESOURCE sr;
	d3dcontext->Map(dynamic_index_buffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &sr);
	memcpy((unsigned short*)sr.pData + face_start_index, indices, num_indices * sizeof(unsigned short));
	d3dcontext->Unmap(dynamic_index_buffer, 0);
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
	float offset_x = (float)activeDispEnv.screen.x;
	float offset_y = (float)activeDispEnv.screen.y;

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = (float)x + offset_x;
	viewport.TopLeftY = (float)y + offset_y;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	d3dcontext->RSSetViewports(1, &viewport);
}

void Emulator_SwapWindow()
{
	unsigned int timer = 1;

	Emulator_WaitForTimestep(1);

	HRESULT hr = swapChain->Present(g_swapInterval, 0);

	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
		g_resetDeviceOnNextFrame = TRUE;
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
	d3dcontext->OMSetRenderTargets(1, &frameBufferObject, NULL);
}

#endif