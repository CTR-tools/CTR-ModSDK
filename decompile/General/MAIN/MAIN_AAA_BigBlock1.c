#include <common.h>

#include "MainInit_PrimMem.c"
#include "MainInit_JitPoolsReset.c"
#include "MainInit_OTMem.c"
#include "MainInit_JitPoolsNew.c"
#include "MainInit_Drivers.c"
#include "MainInit_FinalizeInit.c"
#include "MainInit_VRAMClear.c"
#include "MainInit_VRAMDisplay.c"
#include "MainKillGame_StopCTR.c"
#include "MainKillGame_LaunchSpyro2.c"
#include "MainLoadVLC_Callback.c"
#include "MainLoadVLC.c"
#include "MainMain.c"

// for modding
#include "../AltMods/ModsMain.c"