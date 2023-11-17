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
#define u_char unsigned char
#define u_short unsigned short
#define u_int unsigned int
#define u_long unsigned int
#define _Static_assert(x) ;
#define __attribute__(x) ;
#define BUILD 926
#define RECT RECT16

#include "../rebuild_PS1/main.c"
#include "../decompile/General/zGlobal_DATA.c"
#include "../decompile/General/zGlobal_SDATA.c"

int main()
{
	void PsyX_Initialise(char* appName, int width, int height, int fullscreen);
	PsyX_Initialise("CTRPC", 800, 600, 0);

	void PsyX_CDFS_Init(const char* imageFileName, int track /*= 0*/, int sectorSize /*= 0*/);
	PsyX_CDFS_Init("ctr-u.bin", 0, 0);

	void PsyX_SetSwapInterval(int);
	void PsyX_EnableSwapInterval(int);

	// set to 30 FPS VSync
	PsyX_SetSwapInterval(2);
	PsyX_EnableSwapInterval(1);

	return DECOMP_main();
}