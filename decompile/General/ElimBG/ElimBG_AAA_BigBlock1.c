#include <common.h>

#include "ElimBG_SaveScreenshot_Chunk.c"
#include "ElimBG_SaveScreenshot_Full.c"
#include "ElimBG_Activate.c"
#include "ElimBG_ToggleInstance.c"
#include "ElimBG_ToggleAllInstances.c"
#include "ElimBG_HandleState.c"
#include "ElimBG_Deactivate.c"

#include "../AltMods/Mods6.c"

void __attribute__ ((section (".end"))) Mods6_EndOfFile()
{
	// leave empty
}