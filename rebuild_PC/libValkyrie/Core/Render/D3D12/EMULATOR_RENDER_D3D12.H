#ifndef EMULATOR_RENDER_D3D12_H
#define EMULATOR_RENDER_D3D12_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

#include <string.h>

#if defined(D3D12)

#define FRAME_COUNT 2

struct D3D12TextureWrapper
{
	ID3D12Resource* m_textureResource;
	ID3D12DescriptorHeap* m_srvHeap;
	ID3D12Resource* m_uploadHeap;
};

typedef D3D12TextureWrapper TextureID;

#define MAX_NUM_BLEND_MODES (5)

struct ShaderID {
	D3D12_SHADER_BYTECODE VS;
	D3D12_SHADER_BYTECODE PS;
	D3D12_INPUT_LAYOUT_DESC IL;
	ID3D12RootSignature* RS;
	ID3D12PipelineState* GPS[MAX_NUM_BLEND_MODES];
	FLOAT BF[MAX_NUM_BLEND_MODES][4];
};

typedef D3D12_RENDER_TARGET_VIEW_DESC* RenderTargetID;

extern bool begin_pass_flag;
extern bool begin_commands_flag;

extern ID3D12Device* d3ddev;
extern D3D12_VERTEX_BUFFER_VIEW dynamic_vertex_buffer_view;
extern ID3D12Resource* dynamic_vertex_buffer[FRAME_COUNT];
extern int frameIndex;
extern ID3D12GraphicsCommandList* commandList;
extern unsigned int dynamic_vertex_buffer_index;

extern int Emulator_InitialiseD3D12Context(char* windowName);

#endif

#endif