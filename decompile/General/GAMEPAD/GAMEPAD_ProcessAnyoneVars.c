#include <common.h>

void DECOMP_GAMEPAD_ProcessAnyoneVars(struct GamepadSystem* gGamepads)
{
  int i;
  unsigned int uVar1;
  unsigned int uVar2;
  struct GamepadBuffer* pad;

  DECOMP_GAMEPAD_ProcessHold(gGamepads);
  DECOMP_GAMEPAD_ProcessSticks(gGamepads);
  DECOMP_GAMEPAD_ProcessTapRelease(gGamepads);
  DECOMP_GAMEPAD_ProcessMotors(gGamepads);

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