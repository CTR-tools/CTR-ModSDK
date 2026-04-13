#include <common.h>

#include "VehPhysProc_06_FreezeVShift_Update.c"
#include "VehPhysProc_07_FreezeVShift_ReverseOneFrame.c"
#include "VehPhysProc_08_FreezeVShift_Init.c"
#include "VehPhysProc_09_PowerSlide_PhysAngular.c"
#include "VehPhysProc_10_PowerSlide_Finalize.c"
#include "VehPhysProc_11_PowerSlide_Update.c"
#include "VehPhysProc_12_PowerSlide_PhysLinear.c"
#include "VehPhysProc_13_PowerSlide_InitSetUpdate.c"
#include "VehPhysProc_14_PowerSlide_Init.c"
#include "VehPhysProc_15_SlamWall_PhysAngular.c"
#include "VehPhysProc_16_SlamWall_Update.c"
#include "VehPhysProc_17_SlamWall_PhysLinear.c"
#include "VehPhysProc_18_SlamWall_Animate.c"
#include "VehPhysProc_19_SlamWall_Init.c"
#include "VehPhysProc_20_SpinFirst_Update.c"
#include "VehPhysProc_21_SpinFirst_PhysLinear.c"
#include "VehPhysProc_22_SpinFirst_PhysAngular.c"
#include "VehPhysProc_23_SpinFirst_InitSetUpdate.c"
#include "VehPhysProc_24_SpinFirst_Init.c"
#include "VehPhysProc_25_SpinLast_Update.c"
#include "VehPhysProc_26_SpinLast_PhysLinear.c"
#include "VehPhysProc_27_SpinLast_PhysAngular.c"
#include "VehPhysProc_28_SpinLast_Init.c"
//#include "VehPhysProc_29_SpinStop_Update.c" //TODO (not needed?)
//#include "VehPhysProc_30_SpinStop_PhysLinear.c" //TODO (not needed?)
//#include "VehPhysProc_31_SpinStop_PhysAngular.c" //TODO (not needed?)
#include "VehPhysProc_32_SpinStop_Animate.c"
#include "VehPhysProc_33_SpinStop_Init.c"

#if defined (USE_ALTMODS)
#include "../AltMods/Mods5.c"

void __attribute__ ((section (".end"))) Mods5_EndOfFile()
{
	// leave empty
}
#endif