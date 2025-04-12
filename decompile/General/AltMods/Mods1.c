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
// REBUILD_PS1 does not have fragmenting,
// RAMEX does not need memory-saving hacks
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX)

#include "ByteFiller.h"

void RelocMemory_DefragUI_Mods1_XNF()
{
	// 0x730 = 1840 bytes
	FILLER(0,7,3,0);
}

void RelocMemory_DefragUI_Mods1_ThreadPool()
{
	// 0x1b00 = 6912 bytes
	FILLER(1,B,0,0);
}

#endif