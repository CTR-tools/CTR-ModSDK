#include <common.h>

#include "VehPhysProc_FreezeVShift_FuncPtrs.c"
#include "VehPhysProc_FreezeVShift_Init.c"
#include "VehPhysProc_PowerSlide_FuncPtrs.c"
#include "VehPhysProc_PowerSlide_Init.c"
#include "VehPhysProc_SlamWall_FuncPtrs.c"
#include "VehPhysProc_SlamWall_Init.c"
#include "VehPhysProc_SpinFirst_FuncPtrs.c"
#include "VehPhysProc_SpinFirst_Init.c"
#include "VehPhysProc_SpinLast_FuncPtrs.c"
#include "VehPhysProc_SpinLast_Init.c"
#include "VehPhysProc_SpinStop_FuncPtrs.c"
#include "VehPhysProc_SpinStop_Init.c"

#include "../AltMods/Mods5.c"

void __attribute__ ((section (".end"))) Mods5_EndOfFile()
{
	// leave empty
}