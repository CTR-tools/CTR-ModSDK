#include <common.h>

/// @brief Main gamepad processing function. Polls every connected gamepad and generates global state flags.
/// @param gGamepads - gamepad input system
void DECOMP_GAMEPAD_ProcessAnyoneVars(struct GamepadSystem* gGamepads)
{
  struct GamepadBuffer* pad;

  //process gamepads
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

  //foreach connected gamepad
  for (int i = 0; i < gGamepads->numGamepadsConnected; i++)
  {
    //get gamepad
    pad = &gGamepads->gamepad[i];

    //update global system flag
    gGamepads->anyoneHeldCurr |= pad->buttonsHeldCurrFrame;
    gGamepads->anyoneTapped   |= pad->buttonsTapped;
    gGamepads->anyoneReleased |= pad->buttonsReleased;
    gGamepads->anyoneHeldPrev |= pad->buttonsHeldPrevFrame;
  }
}