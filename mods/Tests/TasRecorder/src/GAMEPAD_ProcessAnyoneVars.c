#include <common.h>

void DECOMP_GAMEPAD_ProcessAnyoneVars(struct GamepadSystem* gGamepads)
{
  struct GamepadBuffer* pad;

  //process gamepads
  GAMEPAD_ProcessHold(gGamepads);
  GAMEPAD_ProcessSticks(gGamepads);
  GAMEPAD_ProcessTapRelease(gGamepads);
  
  // Disabled for TAS Software
  // GAMEPAD_ProcessMotors(gGamepads);

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