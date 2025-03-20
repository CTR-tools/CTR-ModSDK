#include <common.h>

#include "MainInit_02_PrimMem.c"
#include "MainInit_03_JitPoolsReset.c"
#include "MainInit_04_OTMem.c"
#include "MainInit_05_JitPoolsNew.c"
#include "MainInit_06_Drivers.c"
#include "MainInit_07_FinalizeInit.c"
#include "MainInit_09_VRAMClear.c"
#include "MainInit_10_VRAMDisplay.c"
#include "MainKillGame_00_StopCTR.c"
#include "MainKillGame_01_LaunchSpyro2.c"
#include "MainLoadVLC_00_Callback.c"
#include "MainLoadVLC.c"
#include "MainMain.c"

// byte budget requirement
#include "../MATH/MATH_0_Sin.c"
#include "../LibraryOfModels/LibraryOfModels_0_Store.c"

#if defined (USE_ALTMODS)
// for modding
#include "../AltMods/ModsMain.c"
#endif