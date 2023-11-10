#ifndef EMULATOR_RENDER_D3D11_H
#define EMULATOR_RENDER_D3D11_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

#include <string.h>

#if defined(D3D11)

typedef ID3D11ShaderResourceView* TextureID;

struct ShaderID {
	ID3D11VertexShader* VS;
	ID3D11PixelShader* PS;
	ID3D11InputLayout* IL;
};

typedef ID3D11RenderTargetView* RenderTargetID;

extern ID3D11Device* d3ddev;
extern ID3D11DeviceContext* d3dcontext;
extern ID3D11Texture2D* vramBaseTexture;
extern ID3D11Buffer* dynamic_vertex_buffer;


extern int Emulator_InitialiseD3D11Context(char* windowName);
extern ShaderID Shader_Compile(const char* source);

#endif

#endif