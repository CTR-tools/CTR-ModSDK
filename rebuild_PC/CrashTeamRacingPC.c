#define _CRT_SECURE_NO_WARNINSG
#define REBUILD_PC

#include "../rebuild_PS1/main.c"
#include "../decompile/General/zGlobal_DATA.c"
#include "../decompile/General/zGlobal_SDATA.c"

int main()
{
	PsyX_Initialise("CTRPC", 640, 480, 0);
	PsyX_CDFS_Init("ctr-u.bin", 0, 0);

	void PsyX_SetSwapInterval(int);
	void PsyX_EnableSwapInterval(int);

	// set to 30 FPS VSync
	PsyX_SetSwapInterval(2);
	PsyX_EnableSwapInterval(1);

	return DECOMP_main();
}