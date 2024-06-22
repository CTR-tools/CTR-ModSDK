#include <common.h>

#include "GAMEPAD_Init.c"
#include "GAMEPAD_SetMainMode.c"
#include "GAMEPAD_ProcessState.c"
#include "GAMEPAD_PollVsync.c"
#include "GAMEPAD_GetNumConnected.c"
#include "GAMEPAD_ProcessHold.c"
#include "GAMEPAD_ProcessSticks.c"
#include "GAMEPAD_ProcessTapRelease.c"
#include "GAMEPAD_ProcessMotors.c"
#include "GAMEPAD_ProcessAnyoneVars.c"

#include "../AltMods/Mods2.c"

void __attribute__ ((section (".end"))) Mods2_EndOfFile()
{
	// leave empty
}