#ifndef EMULATOR_RENDER_D3D9_H
#define EMULATOR_RENDER_D3D9_H

#include "Core/Setup/Platform/EMULATOR_PLATFORM_SETUP.H"
#include "Core/Setup/Platform/EMULATOR_PLATFORM_INCLUDES.H"

#include <string.h>

#if defined(D3D9)

extern int Emulator_InitialiseD3D9Context(char* windowName);

typedef IDirect3DTexture9* TextureID;

struct ShaderID {
	IDirect3DVertexShader9* VS;
	IDirect3DPixelShader9* PS;
};

typedef IDirect3DSurface9* RenderTargetID;
extern IDirect3DVertexBuffer9* dynamic_vertex_buffer;
extern IDirect3D9* d3d;
extern IDirect3DDevice9* d3ddev;
extern D3DPRESENT_PARAMETERS  d3dpp;
extern LPDIRECT3DVERTEXDECLARATION9 vertexDecl;
extern ShaderID Shader_Compile_Internal(const DWORD* vs_data, const DWORD* ps_data);
#define Shader_Compile(name) Shader_Compile_Internal((DWORD*)name##_vs, (DWORD*)name##_ps)
#endif

#endif