#include "LIBGPU.H"
#include "EMULATOR_RENDER_D3D12.H"
#include "Core/Debug/EMULATOR_LOG.H"
#include "Core/Render/EMULATOR_RENDER_COMMON.H"
#include <stdio.h>

#if defined(D3D12)

extern void Emulator_UpdateVRAM();
extern int Emulator_BeginCommandBuffer();
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
extern void Emulator_CreateIndexBuffer();

const char* renderBackendName = "D3D12";

static ID3D12Resource* tmpHeap = NULL;
ID3D12Resource* dynamic_vertex_buffer[FRAME_COUNT];
ID3D12Resource* dynamic_vertex_buffer_heap[FRAME_COUNT];
D3D12_VERTEX_BUFFER_VIEW dynamic_vertex_buffer_view;
ID3D12Device* d3ddev = NULL;
ID3D12CommandQueue* commandQueue = NULL;
IDXGISwapChain3* swapChain = NULL;
ID3D12Resource* projectionMatrixBuffer[FRAME_COUNT];
D3D12_CONSTANT_BUFFER_VIEW_DESC projectionMatrixBufferView;
ID3D12DescriptorHeap* projectionMatrixBufferHeap[FRAME_COUNT];
D3D12_RASTERIZER_DESC rasterStateDesc;
ID3D12DescriptorHeap* renderTargetDescriptorHeap;
int renderTargetDescriptorSize = 0;
int frameIndex = 0;
ID3D12Resource* renderTargets[FRAME_COUNT];
ID3D12CommandAllocator* commandAllocator;
ID3D12GraphicsCommandList* commandList;
ID3D12Fence* fence;
HANDLE fenceEvent;
UINT64 fenceValue[FRAME_COUNT];

ID3D12Resource* vramBaseTexture;

bool begin_pass_flag = FALSE;
bool begin_commands_flag = FALSE;

unsigned int dynamic_vertex_buffer_index = 0;

int g_CurrentBlendMode = BM_NONE;

SDL_Window* g_window = NULL;

int g_overrideWidth = -1;
int g_overrideHeight = -1;

void Emulator_EndCommandBuffer()
{
	commandList->Close();

	ID3D12CommandList* ppCommandLists[] = { commandList };
	commandQueue->ExecuteCommandLists(sizeof(ppCommandLists) / sizeof(commandList), ppCommandLists);

	begin_commands_flag = FALSE;
}

void Emulator_BeginPass()
{
	Emulator_BeginCommandBuffer();

	if (!begin_pass_flag)
	{
		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, renderTargetDescriptorSize);
		commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, NULL);
	}

	begin_pass_flag = TRUE;
}

void Emulator_CreateGraphicsPipelineState(ShaderID* shader, D3D12_GRAPHICS_PIPELINE_STATE_DESC* pso)
{
	for (int i = 0; i < BM_COUNT; i++)
	{
		switch (i)
		{
		case BM_NONE:
		{
			D3D12_BLEND_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.AlphaToCoverageEnable = FALSE;
			bd.IndependentBlendEnable = FALSE;
			bd.RenderTarget[0].BlendEnable = TRUE;
			bd.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
			bd.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
			bd.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			bd.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
			bd.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
			bd.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
			bd.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			pso->BlendState = bd;

			shader->BF[i][0] = 1.0f;
			shader->BF[i][1] = 1.0f;
			shader->BF[i][2] = 1.0f;
			shader->BF[i][3] = 1.0f;

			break;
		}
		case BM_AVERAGE:
		{
			D3D12_BLEND_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.AlphaToCoverageEnable = FALSE;
			bd.IndependentBlendEnable = TRUE;
			bd.RenderTarget[0].BlendEnable = TRUE;
			bd.RenderTarget[0].SrcBlend = D3D12_BLEND_BLEND_FACTOR;
			bd.RenderTarget[0].DestBlend = D3D12_BLEND_BLEND_FACTOR;
			bd.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			bd.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_BLEND_FACTOR;
			bd.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_BLEND_FACTOR;
			bd.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
			bd.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			pso->BlendState = bd;

			shader->BF[i][0] = 128.0f * (1.0f / 255.0f);
			shader->BF[i][1] = 128.0f * (1.0f / 255.0f);
			shader->BF[i][2] = 128.0f * (1.0f / 255.0f);
			shader->BF[i][3] = 128.0f * (1.0f / 255.0f);
			break;
		}
		case BM_ADD:
		{
			D3D12_BLEND_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.AlphaToCoverageEnable = FALSE;
			bd.IndependentBlendEnable = TRUE;
			bd.RenderTarget[0].BlendEnable = TRUE;
			bd.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
			bd.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;
			bd.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			bd.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
			bd.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ONE;
			bd.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
			bd.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			pso->BlendState = bd;

			shader->BF[i][0] = 1.0f;
			shader->BF[i][1] = 1.0f;
			shader->BF[i][2] = 1.0f;
			shader->BF[i][3] = 1.0f;
			break;
		}
		case BM_SUBTRACT:
		{
			D3D12_BLEND_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.AlphaToCoverageEnable = FALSE;
			bd.IndependentBlendEnable = TRUE;
			bd.RenderTarget[0].BlendEnable = TRUE;
			bd.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
			bd.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;
			bd.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
			bd.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
			bd.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ONE;
			bd.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_REV_SUBTRACT;
			bd.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			pso->BlendState = bd;

			shader->BF[i][0] = 1.0f;
			shader->BF[i][1] = 1.0f;
			shader->BF[i][2] = 1.0f;
			shader->BF[i][3] = 1.0f;
			break;
		}
		case BM_ADD_QUATER_SOURCE:
		{
			D3D12_BLEND_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.AlphaToCoverageEnable = FALSE;
			bd.IndependentBlendEnable = TRUE;
			bd.RenderTarget[0].BlendEnable = TRUE;
			bd.RenderTarget[0].SrcBlend = D3D12_BLEND_BLEND_FACTOR;
			bd.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;
			bd.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			bd.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_BLEND_FACTOR;
			bd.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ONE;
			bd.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
			bd.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			pso->BlendState = bd;

			shader->BF[i][0] = 64.0f * (1.0f / 255.0f);
			shader->BF[i][1] = 64.0f * (1.0f / 255.0f);
			shader->BF[i][2] = 64.0f * (1.0f / 255.0f);
			shader->BF[i][3] = 64.0f * (1.0f / 255.0f);
			break;
		}
		}

		assert(!FAILED(d3ddev->CreateGraphicsPipelineState(pso, IID_PPV_ARGS(&shader->GPS[i]))));
	}
}

#include "Shaders/D3D12/gte_shader_4_vs.h"
#include "Shaders/D3D12/gte_shader_4_ps.h"
#include "Shaders/D3D12/gte_shader_8_vs.h"
#include "Shaders/D3D12/gte_shader_8_ps.h"
#include "Shaders/D3D12/gte_shader_16_vs.h"
#include "Shaders/D3D12/gte_shader_16_ps.h"
#include "Shaders/D3D12/blit_shader_vs.h"
#include "Shaders/D3D12/blit_shader_ps.h"

#define Shader_Compile(name) Shader_Compile_Internal((DWORD*)name##_vs, (DWORD*)name##_ps, sizeof(name##_vs), sizeof(name##_ps))

void Emulator_WaitForPreviousFrame()
{
	const UINT64 fenceV = fenceValue[frameIndex];
	assert(SUCCEEDED(commandQueue->Signal(fence, fenceV)));
	fenceValue[frameIndex]++;

	if (fence->GetCompletedValue() < fenceV)
	{
		assert(SUCCEEDED(fence->SetEventOnCompletion(fenceV, fenceEvent)));
		WaitForSingleObject(fenceEvent, INFINITE);
	}


	frameIndex = swapChain->GetCurrentBackBufferIndex();
}

void Emulator_EndPass()
{
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	Emulator_EndCommandBuffer();

	if (vram_need_update)
	{
		Emulator_UpdateVRAM();
	}

	begin_pass_flag = FALSE;
}

int Emulator_BeginCommandBuffer()
{
	if (begin_commands_flag)
	{
		return begin_commands_flag;
	}

	Emulator_WaitForPreviousFrame();

	int last_begin_commands_flag = begin_commands_flag;

	HRESULT hr = commandAllocator->Reset();
	assert(!FAILED(hr));
	hr = commandList->Reset(commandAllocator, NULL);
	assert(!FAILED(hr));

	begin_commands_flag = TRUE;

	return last_begin_commands_flag;
}

ShaderID Shader_Compile_Internal(const DWORD* vs_data, const DWORD* ps_data, const unsigned int vs_size, const unsigned int ps_size)
{
	ShaderID shader = {};
	HRESULT hr;
	static int shaderCount = 0;

	D3D12_SHADER_BYTECODE vertexShaderByteCode;
	vertexShaderByteCode.pShaderBytecode = vs_data;
	vertexShaderByteCode.BytecodeLength = vs_size;

	D3D12_SHADER_BYTECODE pixelShaderByteCode;
	pixelShaderByteCode.pShaderBytecode = ps_data;
	pixelShaderByteCode.BytecodeLength = ps_size;

#define OFFSETOF(T, E)     ((size_t)&(((T*)0)->E))

	const D3D12_INPUT_ELEMENT_DESC INPUT_LAYOUT[] =
	{
#if defined(PGXP)
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, OFFSETOF(Vertex, x), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
#else	
		{ "POSITION", 0, DXGI_FORMAT_R16G16B16A16_SINT,  0, OFFSETOF(Vertex, x), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
#endif
		{ "TEXCOORD", 0, DXGI_FORMAT_R8G8B8A8_UINT,		 0, OFFSETOF(Vertex, u), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,	 0, OFFSETOF(Vertex, r), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	//Create root signature
	D3D12_DESCRIPTOR_RANGE rangesVertex[1];
	rangesVertex[0].BaseShaderRegister = 0;
	rangesVertex[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	rangesVertex[0].NumDescriptors = 1;
	rangesVertex[0].RegisterSpace = 0;
	rangesVertex[0].OffsetInDescriptorsFromTableStart = 0;

	D3D12_DESCRIPTOR_RANGE rangesPixelVramTexture[1];
	rangesPixelVramTexture[0].BaseShaderRegister = 0;
	rangesPixelVramTexture[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	rangesPixelVramTexture[0].NumDescriptors = 1;
	rangesPixelVramTexture[0].RegisterSpace = 0;
	rangesPixelVramTexture[0].OffsetInDescriptorsFromTableStart = 0;

	D3D12_DESCRIPTOR_RANGE rangesPixelrg8lutTexture[1];
	rangesPixelrg8lutTexture[0].BaseShaderRegister = 1;
	rangesPixelrg8lutTexture[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	rangesPixelrg8lutTexture[0].NumDescriptors = 1;
	rangesPixelrg8lutTexture[0].RegisterSpace = 0;
	rangesPixelrg8lutTexture[0].OffsetInDescriptorsFromTableStart = 0;

	D3D12_ROOT_PARAMETER rootParameters[3];
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = sizeof(rangesPixelVramTexture) / sizeof(D3D12_DESCRIPTOR_RANGE);
	rootParameters[0].DescriptorTable.pDescriptorRanges = rangesPixelVramTexture;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = sizeof(rangesPixelrg8lutTexture) / sizeof(D3D12_DESCRIPTOR_RANGE);
	rootParameters[1].DescriptorTable.pDescriptorRanges = rangesPixelrg8lutTexture;

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].DescriptorTable.NumDescriptorRanges = sizeof(rangesVertex) / sizeof(D3D12_DESCRIPTOR_RANGE);
	rootParameters[2].DescriptorTable.pDescriptorRanges = rangesVertex;

	D3D12_ROOT_PARAMETER rootParametersBlit[3];
	rootParametersBlit[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParametersBlit[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParametersBlit[0].DescriptorTable.NumDescriptorRanges = sizeof(rangesPixelVramTexture) / sizeof(D3D12_DESCRIPTOR_RANGE);
	rootParametersBlit[0].DescriptorTable.pDescriptorRanges = rangesPixelVramTexture;

	rootParametersBlit[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParametersBlit[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParametersBlit[1].DescriptorTable.NumDescriptorRanges = sizeof(rangesPixelrg8lutTexture) / sizeof(D3D12_DESCRIPTOR_RANGE);
	rootParametersBlit[1].DescriptorTable.pDescriptorRanges = rangesPixelrg8lutTexture;

	rootParametersBlit[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParametersBlit[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParametersBlit[2].DescriptorTable.NumDescriptorRanges = sizeof(rangesVertex) / sizeof(D3D12_DESCRIPTOR_RANGE);
	rootParametersBlit[2].DescriptorTable.pDescriptorRanges = rangesVertex;

	D3D12_STATIC_SAMPLER_DESC staticSamplerDesc[2];
	ZeroMemory(&staticSamplerDesc[0], sizeof(staticSamplerDesc));
	staticSamplerDesc[0].Filter = D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	staticSamplerDesc[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplerDesc[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplerDesc[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplerDesc[0].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	staticSamplerDesc[0].MinLOD = -D3D12_FLOAT32_MAX;
	staticSamplerDesc[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplerDesc[0].MaxAnisotropy = 1;

	staticSamplerDesc[0].ShaderRegister = 0;
	staticSamplerDesc[0].RegisterSpace = 0;
	staticSamplerDesc[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	staticSamplerDesc[1].Filter = D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	staticSamplerDesc[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	staticSamplerDesc[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	staticSamplerDesc[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplerDesc[1].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	staticSamplerDesc[1].MinLOD = -D3D12_FLOAT32_MAX;
	staticSamplerDesc[1].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplerDesc[1].MaxAnisotropy = 1;
	staticSamplerDesc[1].ShaderRegister = 1;
	staticSamplerDesc[1].RegisterSpace = 0;
	staticSamplerDesc[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.NumParameters = shaderCount == 3 ? 3 : 3;
	rootSignatureDesc.pParameters = shaderCount == 3 ? rootParametersBlit : rootParameters;
	rootSignatureDesc.NumStaticSamplers = 2;
	rootSignatureDesc.pStaticSamplers = &staticSamplerDesc[0];

	ID3DBlob* errorBlob;
	ID3DBlob* signature;
	hr = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &errorBlob);
	//printf("%s\n", errorBlob->GetBufferPointer());
	assert(!FAILED(hr));

	hr = d3ddev->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&shader.RS));
	assert(!FAILED(hr));

	Emulator_BeginCommandBuffer();
	commandList->SetGraphicsRootSignature(shader.RS);

	DXGI_SAMPLE_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(sampleDesc));
	sampleDesc.Count = 1;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pso;
	ZeroMemory(&pso, sizeof(pso));
	pso.InputLayout = { INPUT_LAYOUT, sizeof(INPUT_LAYOUT) / sizeof(D3D12_INPUT_ELEMENT_DESC) };
	pso.pRootSignature = shader.RS;
	pso.VS = vertexShaderByteCode;
	pso.PS = pixelShaderByteCode;
	pso.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	pso.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pso.SampleDesc = sampleDesc;
	pso.SampleMask = 0xFFFFFFFF;
	pso.RasterizerState = rasterStateDesc;
	pso.NumRenderTargets = 1;
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	depthStencilDesc.DepthEnable = FALSE;
	pso.DepthStencilState = depthStencilDesc;

	Emulator_CreateGraphicsPipelineState(&shader, &pso);

	Emulator_EndCommandBuffer();
	Emulator_WaitForPreviousFrame();

#undef OFFSETOF

	shaderCount++;//Hack

	return shader;
}

void Emulator_ResetDevice(int recreate)
{
	//for (int i = frameIndex ^ 1; i < frameCount; ++i)
	{
		//Emulator_WaitForPreviousFrame();
	}

	if (d3ddev != NULL)
	{
		d3ddev->Release();
		d3ddev = NULL;
	}

	if (swapChain != NULL)
	{
		swapChain->Release();
		swapChain = NULL;
	}

	if (commandQueue != NULL)
	{
		commandQueue->Release();
		commandQueue = NULL;
	}

	if (renderTargetDescriptorHeap != NULL)
	{
		renderTargetDescriptorHeap->Release();
		renderTargetDescriptorHeap = NULL;
	}

	if (commandList != NULL)
	{
		commandList->Release();
		commandList = NULL;
	}

	fence->Release();
	commandAllocator->Release();

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		renderTargets[i]->Release();
		projectionMatrixBufferHeap[i]->Release();
		projectionMatrixBuffer[i]->Release();
		fenceValue[i] = 0;
	}

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		if (dynamic_vertex_buffer[i] = NULL)
		{
			dynamic_vertex_buffer[i]->Release();
			dynamic_vertex_buffer[i] = NULL;
		}

		if (dynamic_vertex_buffer_heap[i] = NULL)
		{
			dynamic_vertex_buffer_heap[i]->Release();
			dynamic_vertex_buffer_heap[i] = NULL;
		}
		}

	Emulator_DestroyGlobalShaders();

	if (vramBaseTexture != NULL)
	{
		vramBaseTexture->Release();
		vramBaseTexture = NULL;
	}

	if (rg8lutTexture.m_textureResource != NULL)
	{
		rg8lutTexture.m_textureResource->Release();
		rg8lutTexture.m_textureResource = NULL;
	}

	if (rg8lutTexture.m_srvHeap != NULL)
	{
		rg8lutTexture.m_srvHeap->Release();
		rg8lutTexture.m_srvHeap = NULL;
	}

	if (rg8lutTexture.m_uploadHeap != NULL)
	{
		rg8lutTexture.m_uploadHeap->Release();
		rg8lutTexture.m_uploadHeap = NULL;
	}

	if (whiteTexture.m_textureResource != NULL)
	{
		whiteTexture.m_textureResource->Release();
		whiteTexture.m_textureResource = NULL;
	}

	if (whiteTexture.m_srvHeap != NULL)
	{
		whiteTexture.m_srvHeap->Release();
		whiteTexture.m_srvHeap = NULL;
	}

	if (whiteTexture.m_uploadHeap != NULL)
	{
		whiteTexture.m_uploadHeap->Release();
		whiteTexture.m_uploadHeap = NULL;
	}

	if (vramTexture.m_textureResource != NULL)
	{
		vramTexture.m_textureResource->Release();
		vramTexture.m_textureResource = NULL;
	}

	if (vramTexture.m_srvHeap != NULL)
	{
		vramTexture.m_srvHeap->Release();
		vramTexture.m_srvHeap = NULL;
	}

	if (vramTexture.m_uploadHeap != NULL)
	{
		vramTexture.m_uploadHeap->Release();
		vramTexture.m_uploadHeap = NULL;
	}

	CloseHandle(fenceEvent);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);

	IDXGIFactory2* factory = NULL;
	HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory));

	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create DXGI factory2!\n");
		return;
	}

	int adapterIndex = 0;
	int adapterFound = FALSE;
	IDXGIAdapter1* adapter = NULL;
	while (factory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC1 adapterDesc;
		adapter->GetDesc1(&adapterDesc);

		if (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			continue;
		}

		hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device), NULL);

		if (SUCCEEDED(hr))
		{
			adapterFound = TRUE;
			break;
		}

		adapterIndex++;
	}

	if (!adapterFound) {
		eprinterr("Failed to locate D3D12 compatible adapter!\n");
		return;
	}

	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}

	hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&d3ddev));
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create D3D12 device!\n");
		return;
	}

	hr = d3ddev->GetDeviceRemovedReason();

	D3D12_COMMAND_QUEUE_DESC commandQDesc;
	ZeroMemory(&commandQDesc, sizeof(D3D12_COMMAND_QUEUE_DESC));
	commandQDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	commandQDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = d3ddev->CreateCommandQueue(&commandQDesc, IID_PPV_ARGS(&commandQueue));
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create D3D12 command queue!\n");
		return;
	}

	DXGI_SAMPLE_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(DXGI_SAMPLE_DESC));
	sampleDesc.Count = 1;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC1));
	swapChainDesc.BufferCount = FRAME_COUNT;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc = sampleDesc;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Width = windowWidth;
	swapChainDesc.Height = windowHeight;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFSDesc;
	ZeroMemory(&swapChainFSDesc, sizeof(swapChainFSDesc));
	swapChainFSDesc.Windowed = TRUE;

	IDXGISwapChain1* tempSwapChain;

	hr = factory->CreateSwapChainForHwnd(commandQueue, wmInfo.info.win.window, &swapChainDesc, &swapChainFSDesc, NULL, &tempSwapChain);

	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create swap chain!\n");
		return;
	}

	swapChain = (IDXGISwapChain3*)tempSwapChain;
	frameIndex = swapChain->GetCurrentBackBufferIndex();

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
	ZeroMemory(&heapDesc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
	heapDesc.NumDescriptors = FRAME_COUNT;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	hr = d3ddev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&renderTargetDescriptorHeap));
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create RTV Descripter heap!\n");
		return;
	}

	renderTargetDescriptorSize = d3ddev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargets[i]));
		if (FAILED(hr))
		{
			return;
	}

		d3ddev->CreateRenderTargetView(renderTargets[i], NULL, rtvHandle);

		rtvHandle.Offset(1, renderTargetDescriptorSize);
	}

	hr = d3ddev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	if (FAILED(hr))
	{
		return;
	}

	hr = d3ddev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, IID_PPV_ARGS(&commandList));
	if (FAILED(hr))
	{
		return;
	}

	commandList->Close();

	hr = d3ddev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (FAILED(hr))
	{
		return;
	}

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		fenceValue[i] = 0;
	}

	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (fenceEvent == NULL)
	{
		eprinterr("Failed to create fence event!\n");
		return;
	}

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex)), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&dynamic_vertex_buffer[i]));
		assert(SUCCEEDED(hr));

		hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex)), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&dynamic_vertex_buffer_heap[i]));
		assert(SUCCEEDED(hr));
	}

	D3D12_RESOURCE_DESC td;

	ZeroMemory(&td, sizeof(td));
	td.Width = VRAM_WIDTH;
	td.Height = VRAM_HEIGHT;
	td.MipLevels = td.DepthOrArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8_UNORM;
	td.SampleDesc.Count = 1;
	td.Flags = D3D12_RESOURCE_FLAG_NONE;
	td.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

	hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &td, D3D12_RESOURCE_STATE_COPY_DEST, NULL, IID_PPV_ARGS(&vramTexture.m_textureResource));
	assert(!FAILED(hr));

	hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &td, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&vramTexture.m_uploadHeap));
	assert(!FAILED(hr));

	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc;
	ZeroMemory(&srvHeapDesc, sizeof(srvHeapDesc));
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	hr = d3ddev->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&vramTexture.m_srvHeap));
	assert(SUCCEEDED(hr));

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = td.Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	d3ddev->CreateShaderResourceView(vramTexture.m_textureResource, &srvDesc, vramTexture.m_srvHeap->GetCPUDescriptorHandleForHeapStart());


	Emulator_CreateConstantBuffers();
	Emulator_CreateGlobalShaders();
	Emulator_GenerateCommonTextures();

	D3D12_RESOURCE_DESC textureResourceDesc;
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	textureResourceDesc.Alignment = 0;
	textureResourceDesc.Width = VRAM_WIDTH * VRAM_HEIGHT * sizeof(short);
	textureResourceDesc.Height = 1;
	textureResourceDesc.DepthOrArraySize = 1;
	textureResourceDesc.MipLevels = 1;
	textureResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	textureResourceDesc.SampleDesc.Count = 1;
	textureResourceDesc.SampleDesc.Quality = 0;
	textureResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	textureResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &textureResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&vramBaseTexture));
	assert(!FAILED(hr));

	ZeroMemory(&textureResourceDesc, sizeof(textureResourceDesc));
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	textureResourceDesc.Alignment = 0;
	textureResourceDesc.Width = MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex);
	textureResourceDesc.Height = 1;
	textureResourceDesc.DepthOrArraySize = 1;
	textureResourceDesc.MipLevels = 1;
	textureResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	textureResourceDesc.SampleDesc.Count = 1;
	textureResourceDesc.SampleDesc.Quality = 0;
	textureResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	textureResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex)), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&dynamic_vertex_buffer[i]));
		assert(SUCCEEDED(hr));

		hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex)), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&dynamic_vertex_buffer_heap[i]));
		assert(SUCCEEDED(hr));
	}

	if (begin_pass_flag)
	{
		begin_commands_flag = FALSE;
		begin_pass_flag = FALSE;
		Emulator_BeginPass();
	}
	else if (begin_commands_flag)
	{
		begin_commands_flag = FALSE;
		Emulator_BeginCommandBuffer();
	}
}

int Emulator_InitialiseD3D12Context(char* windowName)
{
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window!\n");
		return FALSE;
	}
	
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);

	IDXGIFactory2* factory = NULL;
	HRESULT hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory));

	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create DXGI factory2!\n");
		return FALSE;
	}

	int adapterIndex = 0;
	int adapterFound = FALSE;
	IDXGIAdapter1* adapter = NULL;
	while (factory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC1 adapterDesc;
		adapter->GetDesc1(&adapterDesc);

		if (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			continue;
		}

		hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), NULL);

		if (SUCCEEDED(hr))
		{
			adapterFound = TRUE;
			break;
		}

		adapterIndex++;
	}

	if (!adapterFound) {
		eprinterr("Failed to locate D3D12 compatible adapter!\n");
		return FALSE;
	}

	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}

	hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&d3ddev));
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create D3D12 device!\n");
		return FALSE;
	}

	hr = d3ddev->GetDeviceRemovedReason();

	D3D12_COMMAND_QUEUE_DESC commandQDesc;
	ZeroMemory(&commandQDesc, sizeof(D3D12_COMMAND_QUEUE_DESC));
	commandQDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	commandQDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = d3ddev->CreateCommandQueue(&commandQDesc, IID_PPV_ARGS(&commandQueue));
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create D3D12 command queue!\n");
		return FALSE;
	}

	DXGI_SAMPLE_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(DXGI_SAMPLE_DESC));
	sampleDesc.Count = 1;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC1));
	swapChainDesc.BufferCount = FRAME_COUNT;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc = sampleDesc;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Width = windowWidth;
	swapChainDesc.Height = windowHeight;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFSDesc;
	ZeroMemory(&swapChainFSDesc, sizeof(swapChainFSDesc));
	swapChainFSDesc.Windowed = TRUE;

	IDXGISwapChain1* tempSwapChain;

	hr = factory->CreateSwapChainForHwnd(commandQueue, wmInfo.info.win.window, &swapChainDesc, &swapChainFSDesc, NULL, &tempSwapChain);

	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create swap chain!\n");
		return FALSE;
	}

	swapChain = (IDXGISwapChain3*)tempSwapChain;
	frameIndex = swapChain->GetCurrentBackBufferIndex();

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
	ZeroMemory(&heapDesc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
	heapDesc.NumDescriptors = FRAME_COUNT;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	hr = d3ddev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&renderTargetDescriptorHeap));
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create RTV Descripter heap!\n");
		return FALSE;
	}

	renderTargetDescriptorSize = d3ddev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargets[i]));
		if (FAILED(hr))
		{
			return FALSE;
		}

		d3ddev->CreateRenderTargetView(renderTargets[i], NULL, rtvHandle);

		rtvHandle.Offset(1, renderTargetDescriptorSize);
	}

	hr = d3ddev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = d3ddev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, IID_PPV_ARGS(&commandList));
	if (FAILED(hr))
	{
		return FALSE;
	}

	commandList->Close();

	hr = d3ddev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (FAILED(hr))
	{
		return FALSE;
	}

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		fenceValue[i] = 0;
	}

	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (fenceEvent == NULL)
	{
		eprinterr("Failed to create fence event!\n");
		return FALSE;
	}

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex)), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&dynamic_vertex_buffer[i]));
		assert(SUCCEEDED(hr));

		hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex)), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&dynamic_vertex_buffer_heap[i]));
		assert(SUCCEEDED(hr));
	}

	return TRUE;
}

void Emulator_CreateGlobalShaders()
{
	Emulator_CreateRasterState(FALSE);

	g_gte_shader_4 = Shader_Compile(gte_shader_4);
	g_gte_shader_8 = Shader_Compile(gte_shader_8);
	g_gte_shader_16 = Shader_Compile(gte_shader_16);
	g_blit_shader = Shader_Compile(blit_shader);
}

void Emulator_DestroyGlobalShaders()
{
	for (int i = 0; i < BM_COUNT; i++)
	{
		if (g_gte_shader_4.GPS[i] != NULL)
		{
			g_gte_shader_4.GPS[i]->Release();
			g_gte_shader_4.GPS[i] = NULL;
		}

		if (g_gte_shader_8.GPS[i] != NULL)
		{
			g_gte_shader_8.GPS[i]->Release();
			g_gte_shader_8.GPS[i] = NULL;
		}

		if (g_gte_shader_16.GPS[i] != NULL)
		{
			g_gte_shader_16.GPS[i]->Release();
			g_gte_shader_16.GPS[i] = NULL;
		}

		if (g_blit_shader.GPS[i] != NULL)
		{
			g_blit_shader.GPS[i]->Release();
			g_blit_shader.GPS[i] = NULL;
		}
	}

	if (g_gte_shader_4.RS != NULL)
	{
		g_gte_shader_4.RS->Release();
		g_gte_shader_4.RS = NULL;
	}

	if (g_gte_shader_8.RS != NULL)
	{
		g_gte_shader_8.RS->Release();
		g_gte_shader_8.RS = NULL;
	}

	if (g_gte_shader_16.RS != NULL)
	{
		g_gte_shader_16.RS->Release();
		g_gte_shader_16.RS = NULL;
	}

	if (g_blit_shader.RS != NULL)
	{
		g_blit_shader.RS->Release();
		g_blit_shader.RS = NULL;
	}
}

void Emulator_GenerateCommonTextures()
{
	unsigned int pixelData = 0xFFFFFFFF;

	D3D12_RESOURCE_DESC td;

	ZeroMemory(&td, sizeof(td));
	td.Width = 1;
	td.Height = 1;
	td.MipLevels = td.DepthOrArraySize = 1;
	td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.Flags = D3D12_RESOURCE_FLAG_NONE;
	td.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

	HRESULT hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &td, D3D12_RESOURCE_STATE_COPY_DEST, NULL, IID_PPV_ARGS(&whiteTexture.m_textureResource));
	assert(!FAILED(hr));

	unsigned int uploadBufferSize = td.Width * td.Height * sizeof(unsigned int);

	hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&whiteTexture.m_uploadHeap));
	assert(!FAILED(hr));

	D3D12_SUBRESOURCE_DATA srd;
	ZeroMemory(&srd, sizeof(srd));
	srd.pData = (void*)&pixelData;
	srd.RowPitch = td.Width * sizeof(unsigned int);
	srd.SlicePitch = 0;

	Emulator_BeginCommandBuffer();
	UpdateSubresources(commandList, whiteTexture.m_textureResource, whiteTexture.m_uploadHeap, 0, 0, 1, &srd);
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(whiteTexture.m_textureResource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
	Emulator_EndCommandBuffer();

	Emulator_WaitForPreviousFrame();

	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	hr = d3ddev->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&whiteTexture.m_srvHeap));
	assert(SUCCEEDED(hr));

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = td.Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	d3ddev->CreateShaderResourceView(whiteTexture.m_textureResource, &srvDesc, whiteTexture.m_srvHeap->GetCPUDescriptorHandleForHeapStart());

	ZeroMemory(&td, sizeof(td));
	td.Width = LUT_WIDTH;
	td.Height = LUT_HEIGHT;
	td.MipLevels = td.DepthOrArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

	hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &td, D3D12_RESOURCE_STATE_COPY_DEST, NULL, IID_PPV_ARGS(&rg8lutTexture.m_textureResource));
	assert(!FAILED(hr));

	uploadBufferSize = td.Width * td.Height * sizeof(unsigned int);

	hr = d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&rg8lutTexture.m_uploadHeap));
	assert(!FAILED(hr));

	ZeroMemory(&srd, sizeof(srd));
	srd.pData = (void*)Emulator_GenerateRG8LUT();
	srd.RowPitch = td.Width * sizeof(unsigned int);
	srd.SlicePitch = 0;

	Emulator_BeginCommandBuffer();
	UpdateSubresources(commandList, rg8lutTexture.m_textureResource, rg8lutTexture.m_uploadHeap, 0, 0, 1, &srd);
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(rg8lutTexture.m_textureResource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
	Emulator_EndCommandBuffer();
	Emulator_WaitForPreviousFrame();

	ZeroMemory(&srvHeapDesc, sizeof(srvHeapDesc));
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	hr = d3ddev->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&rg8lutTexture.m_srvHeap));
	assert(SUCCEEDED(hr));

	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = td.Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	d3ddev->CreateShaderResourceView(rg8lutTexture.m_textureResource, &srvDesc, rg8lutTexture.m_srvHeap->GetCPUDescriptorHandleForHeapStart());
}

int Emulator_CreateCommonResources()
{
	memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

	Emulator_GenerateCommonTextures();

	Emulator_CreateConstantBuffers();

	D3D12_RESOURCE_DESC td;

	ZeroMemory(&td, sizeof(td));
	td.Width = VRAM_WIDTH;
	td.Height = VRAM_HEIGHT;
	td.MipLevels = td.DepthOrArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8_UNORM;
	td.SampleDesc.Count = 1;
	td.Flags = D3D12_RESOURCE_FLAG_NONE;
	td.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

	D3D12_HEAP_PROPERTIES heapProperties;
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperties.CreationNodeMask = 1;
	heapProperties.VisibleNodeMask = 1;

	HRESULT hr = d3ddev->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &td, D3D12_RESOURCE_STATE_COPY_DEST, NULL, IID_PPV_ARGS(&vramTexture.m_textureResource));
	assert(!FAILED(hr));

	hr = d3ddev->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &td, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&vramTexture.m_uploadHeap));
	assert(!FAILED(hr));

	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	hr = d3ddev->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&vramTexture.m_srvHeap));
	assert(SUCCEEDED(hr));

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = td.Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	d3ddev->CreateShaderResourceView(vramTexture.m_textureResource, &srvDesc, vramTexture.m_srvHeap->GetCPUDescriptorHandleForHeapStart());

	ZeroMemory(&td, sizeof(td));
	td.Width = LUT_WIDTH;
	td.Height = LUT_HEIGHT;
	td.MipLevels = td.DepthOrArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8_UNORM;
	td.SampleDesc.Count = 1;
	td.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

	D3D12_RESOURCE_DESC textureResourceDesc;
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	textureResourceDesc.Alignment = 0;
	textureResourceDesc.Width = VRAM_WIDTH * VRAM_HEIGHT * sizeof(short);
	textureResourceDesc.Height = 1;
	textureResourceDesc.DepthOrArraySize = 1;
	textureResourceDesc.MipLevels = 1;
	textureResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	textureResourceDesc.SampleDesc.Count = 1;
	textureResourceDesc.SampleDesc.Quality = 0;
	textureResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	textureResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	ZeroMemory(&heapProperties, sizeof(heapProperties));
	heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperties.CreationNodeMask = 1;
	heapProperties.VisibleNodeMask = 1;

	hr = d3ddev->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &textureResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&vramBaseTexture));
	assert(!FAILED(hr));

	Emulator_CreateGlobalShaders();

	//Emulator_ResetDevice();

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
	if (begin_commands_flag && begin_pass_flag && !g_resetDeviceOnNextFrame)
	{
		commandList->SetGraphicsRootSignature(shader.RS);
		commandList->SetPipelineState(shader.GPS[g_CurrentBlendMode]);
		commandList->OMSetBlendFactor(shader.BF[g_CurrentBlendMode]);

		Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0.0f, 0.0f, 1.0f);
	}
}

void Emulator_SetTextureAndShader(TextureID texture, ShaderID shader)
{
	Emulator_SetShader(shader);

	if (g_texturelessMode) {
		texture = whiteTexture;
	}

	///@FIXME broken!
	if (g_lastBoundTexture[0].m_textureResource == texture.m_textureResource && g_lastBoundTexture[1].m_textureResource == rg8lutTexture.m_textureResource) {
		//return;
	}

	ID3D12DescriptorHeap* ppHeapsSRV[] = { texture.m_srvHeap };
	commandList->SetDescriptorHeaps(_countof(ppHeapsSRV), ppHeapsSRV);
	commandList->SetGraphicsRootDescriptorTable(0, texture.m_srvHeap->GetGPUDescriptorHandleForHeapStart());
	ID3D12DescriptorHeap* ppHeapsSRV2[] = { rg8lutTexture.m_srvHeap };
	commandList->SetDescriptorHeaps(_countof(ppHeapsSRV2), ppHeapsSRV2);
	commandList->SetGraphicsRootDescriptorTable(1, rg8lutTexture.m_srvHeap->GetGPUDescriptorHandleForHeapStart());

	g_lastBoundTexture[0] = texture;
	g_lastBoundTexture[1] = rg8lutTexture;
}

void Emulator_SetTexture(TextureID texture, enum TexFormat texFormat)
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

	///@FIXME broken!
	if (g_lastBoundTexture[0].m_textureResource == texture.m_textureResource && g_lastBoundTexture[1].m_textureResource == rg8lutTexture.m_textureResource) {
		//return;
	}

	ID3D12DescriptorHeap* ppHeapsSRV[] = { texture.m_srvHeap };
	commandList->SetDescriptorHeaps(_countof(ppHeapsSRV), ppHeapsSRV);
	commandList->SetGraphicsRootDescriptorTable(0, texture.m_srvHeap->GetGPUDescriptorHandleForHeapStart());
	ID3D12DescriptorHeap* ppHeapsSRV2[] = { rg8lutTexture.m_srvHeap };
	commandList->SetDescriptorHeaps(_countof(ppHeapsSRV2), ppHeapsSRV2);
	commandList->SetGraphicsRootDescriptorTable(1, rg8lutTexture.m_srvHeap->GetGPUDescriptorHandleForHeapStart());

	g_lastBoundTexture[0] = texture;
	g_lastBoundTexture[1] = rg8lutTexture;
}

void Emulator_DestroyTexture(TextureID texture)
{
	UNIMPLEMENTED();
}

void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
	FLOAT clearColor[4]{ r / 255.0f, g / 255.0f, b / 255.0f, 1.0f };
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, d3ddev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, NULL);
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

#define FLIP_Y (fy)
	int* data = NULL;
	assert(FALSE);//Needs implementing for framebuffer write backs!
	return;

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

#if 0
	unsigned short* src = (unsigned short*)fb;
	unsigned short* dst = vram + x + y * VRAM_WIDTH;

	for (int i = 0; i < h; i++) {
		memcpy(dst, src, w * sizeof(unsigned short));
		src += w;
		dst += VRAM_WIDTH;
	}
#elif 1

	short* ptr = (short*)vram + VRAM_WIDTH * y + x;

	for (int fy = 0; fy < h; fy++) {
		short* fb_ptr = fb + (h * FLIP_Y / h) * w;

		for (int fx = 0; fx < w; fx++) {
			ptr[fx] = fb_ptr[w * fx / w];
		}

		ptr += VRAM_WIDTH;
	}
#endif

#undef FLIP_Y

	free(fb);

	vram_need_update = TRUE;
}

void Emulator_CreateConstantBuffers()
{
	unsigned int projectionMatrixBufferSize = ((sizeof(float) * 16) + 255) & ~255;

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.NumDescriptors = 1;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		HRESULT hr = d3ddev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&projectionMatrixBufferHeap[i]));
		assert(SUCCEEDED(hr));
}

	for (int i = 0; i < FRAME_COUNT; i++)
	{
		d3ddev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(projectionMatrixBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&projectionMatrixBuffer[i]));

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
		ZeroMemory(&cbvDesc, sizeof(cbvDesc));
		cbvDesc.BufferLocation = projectionMatrixBuffer[i]->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = projectionMatrixBufferSize;
		d3ddev->CreateConstantBufferView(&cbvDesc, projectionMatrixBufferHeap[i]->GetCPUDescriptorHandleForHeapStart());

		void** pMap = NULL;
		CD3DX12_RANGE readRange(0, 0);
		HRESULT hr = projectionMatrixBuffer[i]->Map(0, &readRange, (void**)(&pMap));
		ZeroMemory(pMap, projectionMatrixBufferSize);
		projectionMatrixBuffer[i]->Unmap(0, NULL);
	}
}

void Emulator_UpdateProjectionConstantBuffer(float* ortho)
{
	void** pMap = NULL;
	CD3DX12_RANGE readRange(0, 0);
	HRESULT hr = projectionMatrixBuffer[frameIndex]->Map(0, &readRange, (void**)(&pMap));
	memcpy(pMap, ortho, (sizeof(float) * 16));
	projectionMatrixBuffer[frameIndex]->Unmap(0, &readRange);
}

void Emulator_SetConstantBuffers()
{
	ID3D12DescriptorHeap* ppHeapsCBV[] = { projectionMatrixBufferHeap[frameIndex] };
	commandList->SetDescriptorHeaps(_countof(ppHeapsCBV), ppHeapsCBV);
	commandList->SetGraphicsRootDescriptorTable(2, projectionMatrixBufferHeap[frameIndex]->GetGPUDescriptorHandleForHeapStart());
}

void Emulator_DestroyConstantBuffers()
{
	UNIMPLEMENTED();
}

void Emulator_UpdatePipelineStateObject()
{

}

void Emulator_CreateRasterState(int wireframe)
{
	ZeroMemory(&rasterStateDesc, sizeof(rasterStateDesc));
	rasterStateDesc.FillMode = wireframe ? D3D12_FILL_MODE_WIREFRAME : D3D12_FILL_MODE_SOLID;
	rasterStateDesc.CullMode = D3D12_CULL_MODE_NONE;
	rasterStateDesc.FrontCounterClockwise = FALSE;
	rasterStateDesc.DepthBias = FALSE;
	rasterStateDesc.DepthBiasClamp = 0;
	rasterStateDesc.SlopeScaledDepthBias = 0;
	rasterStateDesc.DepthClipEnable = FALSE;
	rasterStateDesc.MultisampleEnable = FALSE;
	rasterStateDesc.AntialiasedLineEnable = FALSE;

	Emulator_UpdatePipelineStateObject();
}

void Emulator_UpdateVRAM()
{
	if (!vram_need_update) {
		return;
	}
	vram_need_update = FALSE;

	if (begin_commands_flag)
	{
		CD3DX12_RANGE readRange(0, 0);

		void* pTextureData = NULL;

		HRESULT hr = vramBaseTexture->Map(0, &readRange, (void**)&pTextureData);
		assert(!FAILED(hr));
		memcpy(pTextureData, vram, (VRAM_WIDTH * VRAM_HEIGHT) * sizeof(short));
		vramBaseTexture->Unmap(0, NULL);

		D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
		footprint.Footprint.Width = VRAM_WIDTH;
		footprint.Footprint.Height = VRAM_HEIGHT;
		footprint.Footprint.Depth = 1;
		footprint.Footprint.RowPitch = VRAM_WIDTH * sizeof(short);
		footprint.Footprint.Format = DXGI_FORMAT_R8G8_UNORM;

		CD3DX12_TEXTURE_COPY_LOCATION src(vramBaseTexture, footprint);
		CD3DX12_TEXTURE_COPY_LOCATION dest(vramTexture.m_textureResource, 0);

		commandList->CopyTextureRegion(&dest, 0, 0, 0, &src, NULL);
	}
}

void Emulator_SetWireframe(int enable)
{
	Emulator_CreateRasterState(enable ? TRUE : FALSE);
}

void Emulator_SetBlendMode(enum BlendMode blendMode)
{
	if (g_PreviousBlendMode == blendMode)
	{
		return;
	}

	g_CurrentBlendMode = blendMode;
	g_PreviousBlendMode = blendMode;
}

void Emulator_DrawTriangles(int start_vertex, int start_index, int triangles)
{
	if (triangles <= 0)
		return;

	if (!g_resetDeviceOnNextFrame)
	{
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		commandList->DrawInstanced(triangles * 3, 1, dynamic_vertex_buffer_index, 0);
		dynamic_vertex_buffer_index += triangles * 3;
	}
}

void Emulator_UpdateVertexBuffer(const Vertex* vertices, int num_vertices)
{
	assert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);

	if (num_vertices <= 0)
		return;

	if (begin_commands_flag)
	{
		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(dynamic_vertex_buffer[frameIndex], D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST));

		void* pMap = NULL;
		CD3DX12_RANGE readRange(0, 0);
		HRESULT hr = dynamic_vertex_buffer_heap[frameIndex]->Map(0, &readRange, &pMap);
		assert(SUCCEEDED(hr));

		memcpy((char*)pMap + dynamic_vertex_buffer_index * sizeof(Vertex), vertices, num_vertices * sizeof(Vertex));
		dynamic_vertex_buffer_heap[frameIndex]->Unmap(0, NULL);

		commandList->CopyBufferRegion(dynamic_vertex_buffer[frameIndex], dynamic_vertex_buffer_index * sizeof(Vertex), dynamic_vertex_buffer_heap[frameIndex], dynamic_vertex_buffer_index * sizeof(Vertex), num_vertices * sizeof(Vertex));
		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(dynamic_vertex_buffer[frameIndex], D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
	}

	vbo_was_dirty_flag = TRUE;
}

void Emulator_UpdateIndexBuffer(const unsigned short* indices, int num_indices)
{
#if 1
	eassert(num_indices <= MAX_NUM_INDEX_BUFFER_INDICES);

	if (num_indices <= 0)
		return;

#if 0
	if (begin_commands_flag)
	{
		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(dynamic_vertex_buffer[frameIndex], D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST));

		void* pMap = NULL;
		CD3DX12_RANGE readRange(0, 0);
		HRESULT hr = dynamic_vertex_buffer_heap[frameIndex]->Map(0, &readRange, &pMap);
		assert(SUCCEEDED(hr));

		memcpy((char*)pMap + dynamic_vertex_buffer_index * sizeof(Vertex), vertices, num_vertices * sizeof(Vertex));
		dynamic_vertex_buffer_heap[frameIndex]->Unmap(0, NULL);

		commandList->CopyBufferRegion(dynamic_vertex_buffer[frameIndex], dynamic_vertex_buffer_index * sizeof(Vertex), dynamic_vertex_buffer_heap[frameIndex], dynamic_vertex_buffer_index * sizeof(Vertex), num_vertices * sizeof(Vertex));
		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(dynamic_vertex_buffer[frameIndex], D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
	}
#endif

	vbo_was_dirty_flag = TRUE;
#else
	eassert(num_indices <= MAX_NUM_INDEX_BUFFER_INDICES);

	if (num_indices <= 0)
		return;

	D3D11_MAPPED_SUBRESOURCE sr;
	d3dcontext->Map(dynamic_index_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sr);
	memcpy(sr.pData, indices, num_indices * sizeof(unsigned short));
	d3dcontext->Unmap(dynamic_index_buffer, 0);
#endif
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
	float offset_x = (float)activeDispEnv.screen.x;
	float offset_y = (float)activeDispEnv.screen.y;

	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = (float)x + offset_x;
	viewport.TopLeftY = (float)y + offset_y;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	commandList->RSSetViewports(1, &viewport);

	D3D12_RECT rect;
	rect.left = 0;
	rect.right = width;
	rect.top = 0;
	rect.bottom = height;
	commandList->RSSetScissorRects(1, &rect);
}

void Emulator_SwapWindow()
{
	unsigned int timer = 1;

#if defined(SINGLE_THREADED_AUDIO)
	Emulator_CounterWrapper(0, &timer);
#endif

	Emulator_WaitForTimestep(1);

	HRESULT hr = swapChain->Present(g_swapInterval, 0);

	Emulator_WaitForPreviousFrame();

	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
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
	
}

#endif