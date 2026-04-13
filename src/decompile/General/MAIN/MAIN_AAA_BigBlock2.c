#include <common.h>

#include "MainDB_00_GetClipSize.c"
#include "MainDB_01_PrimMem.c"
#include "MainDB_02_OTMem.c"
#include "MainDrawCb_00_DrawSync.c"
#include "MainDrawCb_01_Vsync.c"
#include "MainFrame_00_TogglePauseAudio.c"
#include "MainFrame_01_ResetDB.c"
#include "MainFrame_02_GameLogic.c"

#if defined (USE_ALTMODS)
#include "../AltMods/ModsA.c"

void __attribute__ ((section (".end"))) ModsA_EndOfFile()
{
	// leave empty
}
#endif