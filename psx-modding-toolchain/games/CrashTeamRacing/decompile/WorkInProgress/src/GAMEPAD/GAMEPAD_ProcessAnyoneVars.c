#include <common.h>

void DECOMP_GAMEPAD_ProcessAnyoneVars(struct GamepadSystem* gGamepads)
{
  uint uVar1;
  uint uVar2;
  struct GamepadBuffer* pad;

  // determine which buttons are held this frame,
  // store a backup of "currFrame" into "lastFrame"
  uVar1 = GAMEPAD_ProcessHold();

  // handle mapping of D-Pad and
  // analog stick values onto each other
  GAMEPAD_ProcessSticks(gGamepads);

  // Writes all gamepad variables
  // for Tap and Release, based on Hold
  uVar2 = GAMEPAD_ProcessTapRelease(gGamepads);

  GAMEPAD_ProcessForceFeedback(gGamepads);

  // These are used to see if any button is pressed by anyone
  // during this frame. Reset them all to zero
  gGamepads->anyoneHeldCurr = 0;
  gGamepads->anyoneTapped 	= 0;
  gGamepads->anyoneReleased = 0;
  gGamepads->anyoneHeldPrev = 0;

  // if gamepads are connected
  if (gGamepads->numGamepadsConnected)
  {
	// for iVar4 = 0; iVar4 < numGamepads; iVar4++
    for (int i = 0; i < gGamepads->numGamepadsConnected; i++)
	{
		pad = gGamepads->gamepad[i];
		gGamepads->anyoneHeldCurr |= pad->buttonsHeldCurrFrame;
		gGamepads->anyoneTapped   |= pad->buttonsTapped;
		gGamepads->anyoneReleased |= pad->buttonsReleased;
		gGamepads->anyoneHeldPrev |= pad->buttonsHeldPrevFrame;
    } 
  }
}