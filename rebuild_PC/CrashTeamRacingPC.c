
// ======= Headers =============
#define _CRT_SECURE_NO_WARNINGS
#define REBUILD_PC
#include <string.h>

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
#if defined(__GNUC__) || defined(__clang__)
	return 0;
#endif
	// dont use Windows.h
	__declspec(dllimport) short __stdcall
		GetAsyncKeyState(_In_ int vKey);

	return GetAsyncKeyState(0xd);
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

struct StartSettings {
	int width;
	int heigth;
	char* fileName;
};
struct StartSettings startSettings = {
#ifdef WIDE_SCREEN	//HD 720p
	.width = 1280,
	.heigth = 720,
#elif defined(ULTRAWIDE_SCREEN)	//half of UWHD
	.width = 1280,
	.heigth = 540,
#else	//SVGA
	.width = 800,
	.heigth = 600,
#endif
};

int main(int argc, char* argv[])
{
	switch (argc){
		case 1: {
			startSettings.fileName = (char*)malloc(sizeof(char) * strlen("ctr-u.bin"));
			strcpy(startSettings.fileName, "ctr-u.bin");
			break;
		}
		case 2: {
			startSettings.fileName = (char*)malloc(sizeof(char) * strlen(argv[1]));
			strcpy(startSettings.fileName, argv[1]);
			break;
		}
		default: {
			for (int i = 1; i != argc; i++) {
				switch (argv[i][0]) {
				case '/':
				case '+':
				case '-': {
					if (strlen(argv[i]) > 1 && argc > i + 1) switch (argv[i][1]) {
					case 'w':
						startSettings.width = atoi(argv[i + 1]);
						break;
					case 'h':
						startSettings.heigth = atoi(argv[i + 1]);
						break;
					}
					break;
				}
				}
				if (i == argc - 1) {
					int _strlen = strlen(argv[i]);
					if (argv[i][_strlen - 4] == '.' && argv[i][_strlen - 3] == 'b' && argv[i][_strlen - 2] == 'i' && argv[i][_strlen - 1] == 'n') {
						startSettings.fileName = (char*)malloc(sizeof(char) * strlen(argv[i]));
						strcpy(startSettings.fileName, argv[i]);
					}
				}
			}
			break;
		}
	}
	if (!fopen(startSettings.fileName, "r")) return -1; //no file
	printf("Filename is: ");
	printf(startSettings.fileName);
	printf("\n");
	PsyX_Initialise("CTRPC", startSettings.width, startSettings.heigth, 0);
	PsyX_CDFS_Init(startSettings.fileName, 0, 0);

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
