#ifndef EMULATOR_PLATFORM_INCLUDES_H
#define EMULATOR_PLATFORM_INCLUDES_H

/*
 * Assert inclusion
 */

#include "Core/Debug/EMULATOR_ASSERT.H"

/*
 * SDL2.H inclusion.
 */

#if defined(__EMSCRIPTEN__)
#include <SDL2/SDL.h>
#elif (defined(_WINDOWS) || defined(__MINGW32__) || defined(__linux__) || defined(__APPLE__)) && !defined(__ANDROID__) && !defined(SN_TARGET_PSP2) && !defined(PLATFORM_NX) && !defined(PLATFORM_NX_ARM) || defined(UWP_SDL2)
#define _U_LONG
#include <SDL.h>
#if defined(SDL2_MIXER)
#include <SDL_mixer.h>
#endif
#if defined(VULKAN)
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <shaderc/shaderc.hpp>
#include <vector>
#include <set>
#include <array>
#include "Core/Render/Vulkan/EMULATOR_RENDER_VULKAN.H"
#endif
#elif defined (__ANDROID__)
#define DEBUG_PRINTS
#include <SDL.h>
#include <SDL_syswm.h>
#if (OGLES_VERSION == 3)
#include <GLES3/gl3.h>
#endif
#endif

#if defined (OGL)
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#include "Core/Render/OGL/EMULATOR_RENDER_OGL.H"
#elif defined (OGLES)
#if OGLES_VERSION == 2
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif OGLES_VERSION == 3
#include <GLES3/gl3.h>
#endif
#include <EGL/egl.h>
#include "Core/Render/OGLES/EMULATOR_RENDER_OGLES.H"
#if defined(__EMSCRIPTEN__)
#include <SDL2/SDL_egl.h>
#include <SDL2/SDL_syswm.h>
#else
#include <SDL_egl.h>
#endif
#elif defined(D3D9)
#include <Windows.h>
#include <d3d9.h>
#include <SDL_syswm.h>
#include "Core/Render/D3D9/EMULATOR_RENDER_D3D9.H"
#elif defined(D3D11)
#if defined(UWP)
#include <d3d11_3.h>
#else
#include <d3d11.h>
#endif
#if defined(SDL2)
#include <SDL_syswm.h>
#endif
#include "Core/Render/D3D11/EMULATOR_RENDER_D3D11.H"
#elif defined(D3D12)
#include <d3dx12.h>
#include <SDL_syswm.h>
#include <dxgi1_4.h>
#include "Core/Render/D3D12/EMULATOR_RENDER_D3D12.H"
#elif defined(XED3D)
#include <xtl.h>
#include <xgraphics.h>
#if _XDK_VER != 21256
#error "Invalid XDK version"
#endif
#include "Core/Render/XED3D/EMULATOR_RENDER_XED3D.H"
#endif

#include "Core/FileSystem/EMULATOR_FILESYSTEM_COMMON.H"

#endif
