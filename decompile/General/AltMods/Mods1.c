// OnlineCTR (part 1)
#ifndef REBUILD_PC
#ifdef USE_ONLINE
#include "OnlineCTR/hooks.c"
#include "OnlineCTR/menu.c"
#include "OnlineCTR/states.c"
#include "OnlineCTR/thread.c"
#include "OnlineCTR/endOfRaceUI.c"
#include "OnlineCTR/meterGrade.c"
#endif
#endif

#ifdef USE_PROFILER
#include "DebugMenu/Font.c"
#endif

// original ps1 with fragmented memory,
// but also only if NOT using RAMEX, because
// with RAMEX, we dont need to save 0x1b00 bytes
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX)

#include "ByteFiller.h"

void RelocMemory_DefragUI_Mods1()
{
	// 0x2320
	FILLER(1,B,0,0);
}

#endif