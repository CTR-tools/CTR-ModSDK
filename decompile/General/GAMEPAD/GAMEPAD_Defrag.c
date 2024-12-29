#include <common.h>

#include "GAMEPAD_00_Init.c"
#include "GAMEPAD_01_SetMainMode.c"
#include "GAMEPAD_02_ProcessState.c"
#include "GAMEPAD_03_PollVsync.c"
#include "GAMEPAD_04_GetNumConnected.c"
#include "GAMEPAD_05_ProcessHold.c"
#include "GAMEPAD_06_ProcessSticks.c"
#include "GAMEPAD_07_ProcessTapRelease.c"
#include "GAMEPAD_08_ProcessMotors.c"
#include "GAMEPAD_09_ProcessAnyoneVars.c"
#include "GAMEPAD_10_JogCon1.c"
#include "GAMEPAD_11_JogCon2.c"
#include "GAMEPAD_12_ShockFreq.c"
#include "GAMEPAD_13_ShockForce1.c"
#include "GAMEPAD_14_ShockForce2.c"

#if defined (USE_DEFRAG)
#include "../AltMods/Mods2.c"

void __attribute__ ((section (".end"))) Mods2_EndOfFile()
{
	// leave empty
}
#endif