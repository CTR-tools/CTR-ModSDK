#define _CRT_SECURE_NO_WARNINGS
#define REBUILD_PC
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

#define BUILD 926
#define u_char unsigned char
#define u_short unsigned short
#define u_int unsigned int
#define u_long unsigned int

// these two should do nothing
#define _Static_assert(x) 
#define __attribute__(x)

// Since we dont have psn00b in PC
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

#include "../rebuild_PS1/main.c"
#include "../decompile/General/zGlobal_DATA.c"
#include "../decompile/General/zGlobal_SDATA.c"

enum SdlKeys
{
	SDL_SCANCODE_RIGHT = 79,
	SDL_SCANCODE_LEFT = 80,
	SDL_SCANCODE_DOWN = 81,
	SDL_SCANCODE_UP = 82,
	SDL_SCANCODE_C = 6,
	SDL_SCANCODE_X = 27,
};
static int btnFlags = 0;

int WIN_GetPressUp()
{
	return btnFlags & 0x1;
}

int WIN_GetPressDown()
{
	return btnFlags & 0x2;
}

int WIN_GetPressLeft()
{
	return btnFlags & 0x4;
}

int WIN_GetPressRight()
{
	return btnFlags & 0x8;
}

int WIN_GetPressCross()
{
	return btnFlags & 0x10;
}

int WIN_GetPressTriangle()
{
	return btnFlags & 0x20;
}

void PsyXKeyboardHandler(int key, char down)
{
	// here goes your SDL_SCANCODE_* debug keys
	if (key == SDL_SCANCODE_UP)
		btnFlags = down ? (btnFlags | 0x1) : (btnFlags & ~0x1);
	if (key == SDL_SCANCODE_DOWN)
		btnFlags = down ? (btnFlags | 0x2) : (btnFlags & ~0x2);
	if (key == SDL_SCANCODE_LEFT)
		btnFlags = down ? (btnFlags | 0x4) : (btnFlags & ~0x4);
	if (key == SDL_SCANCODE_RIGHT)
		btnFlags = down ? (btnFlags | 0x8) : (btnFlags & ~0x8);
	if (key == SDL_SCANCODE_X)
		btnFlags = down ? (btnFlags | 0x10) : (btnFlags & ~0x10);
	if (key == SDL_SCANCODE_C)
		btnFlags = down ? (btnFlags | 0x20) : (btnFlags & ~0x20);
}

int frameCount = 0;
int oldTicks = 0;

// printf once every X frames
int frameGap = 200;

int NikoCalcFPS()
{
	if (frameCount++ != frameGap) return;
	
	frameCount = 0;
	int newTicks = SDL_GetTicks();
	int delta = newTicks - oldTicks;
	oldTicks = newTicks;

	printf("NikoCalcFPS: %d fps\n", (1000 * frameGap) / delta);
}

int main()
{
	PsyX_Initialise("CTRPC", 800, 600, 0);
	PsyX_CDFS_Init("ctr-u.bin", 0, 0);

	// set to 30 FPS VSync
	PsyX_SetSwapInterval(2);
	PsyX_EnableSwapInterval(1);
	g_dbg_gameDebugKeys = PsyXKeyboardHandler;

	return DECOMP_main();
}