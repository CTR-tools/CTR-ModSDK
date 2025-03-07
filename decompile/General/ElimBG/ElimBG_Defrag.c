#include <common.h>

#include "ElimBG_0_SaveScreenshot_Chunk.c"
#include "ElimBG_1_SaveScreenshot_Full.c"
#include "ElimBG_2_Activate.c"
#include "ElimBG_3_ToggleInstance.c"
#include "ElimBG_4_ToggleAllInstances.c"
#include "ElimBG_5_HandleState.c"
#include "ElimBG_6_Deactivate.c"

#if defined(USE_ALTMODS)
#include "../AltMods/Mods6.c"

void __attribute__ ((section (".end"))) Mods6_EndOfFile()
{
	// leave empty
}
#endif