// ======= Headers =============
#if __GNUC__
#include <SDL2/SDL.h>
#define _EnterCriticalSection(x)
#define EnterCriticalSection(x)
#define ExitCriticalSection()
#endif

#define _CRT_SECURE_NO_WARNINGS
#define REBUILD_PC
#define USE_EXTENDED_PRIM_POINTERS 0
#include "psx/types.h"
#include "psx/libetc.h"
#include "psx/libgte.h"
#include "psx/libgpu.h"
#include "psx/libspu.h"
#include "psx/libcd.h"
#include "psx/libapi.h"
#include "psx/strings.h"
#include "psx/inline_c.h"
#include "PsyX/PsyX_public.h"
#include "PsyX/PsyX_globals.h"
#include "PsyX/PsyX_render.h"

// ======= Syntax Correction =============

#define BUILD 926
#define u_char unsigned char
#define u_short unsigned short
#define u_int unsigned int
#define u_long unsigned int

// these two should do nothing
#define _Static_assert(x) 
#define __attribute__(x)

// ======= Replace Psn00bsdk Data =============

#define RECT RECT16
typedef enum {
	PAD_ID_MOUSE = 0x1, // Sony PS1 mouse
	PAD_ID_NEGCON = 0x2, // Namco neGcon
	PAD_ID_IRQ10_GUN = 0x3, // "Konami" lightgun without composite video passthrough
	PAD_ID_DIGITAL = 0x4, // Digital pad or Dual Analog/DualShock in digital mode
	PAD_ID_ANALOG_STICK = 0x5, // Flight stick or Dual Analog in green LED mode
	PAD_ID_GUNCON = 0x6, // Namco Guncon (lightgun with composite video passthrough)
	PAD_ID_ANALOG = 0x7, // Dual Analog/DualShock in analog (red LED) mode
	PAD_ID_MULTITAP = 0x8, // Multitap adapter (when tap_mode == 1)
	PAD_ID_JOGCON = 0xe, // Namco Jogcon
	PAD_ID_CONFIG_MODE = 0xf, // Dual Analog/DualShock in config mode (if len == 0x3)
	PAD_ID_NONE = 0xf  // No pad connected (if len == 0xf)
} PadTypeID;

// ======= RebuildPS1 -> PC =============

#include "../rebuild_PS1/main.c"
#include "../decompile/General/zGlobal_DATA.c"
#include "../decompile/General/zGlobal_SDATA.c"

// ======= PC-Specific Code =============

// PsyCross bug, the Enter key does not
// work in PsyXKeyboardHandler, workaround:
int NikoGetEnterKey()
{
#if __GNUC__
	return 0;
#else
	// dont use Windows.h
	__declspec(dllimport) short __stdcall 
		GetAsyncKeyState(int vKey);
	
	return GetAsyncKeyState(0xd);
#endif
}

void PsyXKeyboardHandler(int key, char down)
{
	if (down == 0)
		key = 0;

	void SubmitName_UseKeyboard(int key);
	SubmitName_UseKeyboard(key);
}

// printf once every X frames
int frameGap = 2000;
int frameCount = 0;
int oldTicks = 0;

int NikoCalcFPS()
{
	if (frameCount++ != frameGap) return;
	
	frameCount = 0;
	int newTicks = SDL_GetTicks();
	int delta = newTicks - oldTicks;
	oldTicks = newTicks;

	printf("NikoCalcFPS: %d fps\n", (1000 * frameGap) / delta);
}

#ifndef CC
	#if __GNUC__
		#if _WIN32
			#ifndef __clang__
				#define CC "MINGW-GCC"
			#else
				#define CC "MINGW-CLANG"
			#endif
		#else
			#ifndef __clang__
				#define CC "GCC"
			#else
				#define CC "CLANG"
			#endif
		#endif
	#elif defined(_MSC_VER)
		#define CC "MSVC"
	#else
		#define CC "Unknown"
	#endif
#endif

int main(int argc, char* argv[])
{
	printf("[CTR] Built with: " CC "\n");
#ifdef USE_16BY9
	printf("[CTR] USE_16BY9=1\n");
	PsyX_Initialise("CTRPC", 1280, 720, 0);
#else
	printf("[CTR] USE_16BY9=0\n");
	PsyX_Initialise("CTRPC", 800, 600, 0);
#endif

	PsyX_CDFS_Init("ctr-u.bin", 0, 0);

	// set to 30 FPS VSync
	PsyX_SetSwapInterval(2);
	PsyX_EnableSwapInterval(1);

	// P1 = Controller 1
	g_cfg_controllerToSlotMapping[0] = 0;

	// for typing in SubmitName
	g_dbg_gameDebugKeys = PsyXKeyboardHandler;
	
	// override PsyX_Sys_InitialiseInput,
	// so typing in SubmitName doesn't break
	memset(&g_cfg_keyboardMapping, 0, sizeof(g_cfg_keyboardMapping));

	return DECOMP_main();
}