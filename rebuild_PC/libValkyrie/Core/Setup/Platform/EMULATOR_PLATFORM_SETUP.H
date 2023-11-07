#ifndef EMULATOR_PLATFORM_SETUP_H
#define EMULATOR_PLATFORM_SETUP_H

#include "EMULATOR_ARCHITECTURE_SETUP.H"

#if defined(SN_TARGET_PSP2)
		typedef unsigned int uintptr_t;
		#define EXIT_SUCCESS (0)
#endif

#define MAX_NUM_GAME_INSTANCES (6)

//#define NO_AUDIO
//#define DEBUG_PRINTS
#define TOUCH_UI

#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif
#ifndef NULL
#define NULL		0
#endif

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#define UWP
#define UWP_SDL2
//#define DEBUG_PRINTS
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif

/*
 * Platform specific emulator setup
 */
#if (defined(_WINDOWS) || defined(__APPLE__) || defined(__linux__) || defined(__MINGW32__)) && !defined(__ANDROID__) && !defined(SN_TARGET_PSP2) && !defined(PLATFORM_NX) && !defined(PLATFORM_NX_ARM) || (defined(UWP_SDL2))

#if defined(_DEBUG) && !defined(UWP_SDL2)
#define DEBUG_PRINTS
#endif

//Open Graphics Library (Embedded Systems)
//#define OGLES
//#define OGLES_VERSION 3

//Open Graphics Library
#define OGL

//Vulkan
//#define VULKAN
		
//Direct3D9
//#define D3D9

//Direct3D11
//#define D3D11

//Direct3D12
//#define D3D12
//Needs new IBO implementing

#if !defined(_DEBUG)
#define NO_FILESYSTEM
#endif

#if defined(OGL) || defined(D3D9) || defined(D3D11) || defined(D3D12) || defined(VULKAN) || defined(UWP_SDL2) && !defined(SN_TARGET_PSP2)
#define SDL2
//#define SDL2_MIXER
//#define OPENAL
#endif

#if defined(OGL)
#define GLEW
#endif

#elif defined(__EMSCRIPTEN__)
#define OGLES
#define OGLES_VERSION (3)
#define SDL2
//Crashing / locking up in browser so disabled for now //#define OPENAL
#define TOUCH_UI
#elif defined(__ANDROID__)
#define OGLES
#define OGLES_VERSION (3)
#define SDL2
#define NO_FILESYSTEM
#define NO_BOUNTY_LIST_EXPORT
#define TOUCH_UI
#elif defined(_XBOX)
#define XED3D
#endif
#if defined(OGLES)
#if OGLES_VERSION == 2
#define ES2_SHADERS
#elif OGLES_VERSION == 3
#define ES3_SHADERS
#endif
#endif
#if defined(UWP)//UWP
#define D3D11
#define XAUDIO2
#endif
#if defined(SN_TARGET_PSP2)
#define GXM
#define NO_BOUNTY_LIST_EXPORT
#define NO_FILESYSTEM
#endif
#if defined(PLATFORM_NX) || defined(PLATFORM_NX_ARM)
#define NO_BOUNTY_LIST_EXPORT
#define NO_FILESYSTEM
#endif

 /*
  * Emulator render options.
  */
#define RO_DOUBLE_BUFFERED

#endif
