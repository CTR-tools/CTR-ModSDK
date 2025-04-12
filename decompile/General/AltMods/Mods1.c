// OnlineCTR (part 1)
// This is 10,000 bytes of code,
// Safe to store here because OnlineCTR
// Uses RAMEX, which disables the below
// optimizations of ThreadPool and XNF
#ifdef USE_ONLINE
#include "OnlineCTR/hooks.c"
#include "OnlineCTR/menu.c"
#include "OnlineCTR/states.c"
#include "OnlineCTR/thread.c"
#include "OnlineCTR/endOfRaceUI.c"
#include "OnlineCTR/meterGrade.c"
#endif

// original ps1 with fragmented memory,
// but also only if NOT using RAMEX, because
// with RAMEX, we dont need to save 0x1b00 bytes
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX)

#include "ByteFiller.h"

void RelocMemory_DefragUI_Mods1_XNF()
{
	// ...
}

void RelocMemory_DefragUI_Mods1()
{
	// 0x2320
	FILLER(1,B,0,0);
}

#endif