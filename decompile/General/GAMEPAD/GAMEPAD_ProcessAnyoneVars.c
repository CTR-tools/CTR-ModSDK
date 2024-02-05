#include <common.h>

void DECOMP_GAMEPAD_ProcessAnyoneVars(struct GamepadSystem* gGamepads)
{
  int i;
  unsigned int uVar1;
  unsigned int uVar2;
  struct GamepadBuffer* pad;

  // determine which buttons are held this frame,
  // store a backup of "currFrame" into "lastFrame"
  DECOMP_GAMEPAD_ProcessHold(gGamepads);

#ifndef REBUILD_PS1
  // handle mapping of D-Pad and
  // analog stick values onto each other
  GAMEPAD_ProcessSticks(gGamepads);
#endif

  // Writes all gamepad variables
  // for Tap and Release, based on Hold
  DECOMP_GAMEPAD_ProcessTapRelease(gGamepads);

#ifndef REBUILD_PS1
  GAMEPAD_ProcessMotors(gGamepads);
#endif

  // These are used to see if any button is pressed by anyone
  // during this frame. Reset them all to zero
  gGamepads->anyoneHeldCurr = 0;
  gGamepads->anyoneTapped 	= 0;
  gGamepads->anyoneReleased = 0;
  gGamepads->anyoneHeldPrev = 0;

  for (i = 0; i < gGamepads->numGamepadsConnected; i++)
  {
	pad = &gGamepads->gamepad[i];
	gGamepads->anyoneHeldCurr |= pad->buttonsHeldCurrFrame;
	gGamepads->anyoneTapped   |= pad->buttonsTapped;
	gGamepads->anyoneReleased |= pad->buttonsReleased;
	gGamepads->anyoneHeldPrev |= pad->buttonsHeldPrevFrame;
  }
}