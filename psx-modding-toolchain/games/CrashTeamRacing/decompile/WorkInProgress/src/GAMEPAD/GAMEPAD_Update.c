#include <common.h>

uint DECOMP_GAMEPAD_Update(struct GamepadSystem* gGamepads)
{
  uint uVar1;
  uint uVar2;

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
  *(undefined4 *)(gGamepads + 0x290) = 0;
  *(undefined4 *)(gGamepads + 0x294) = 0;
  *(undefined4 *)(gGamepads + 0x298) = 0;
  *(undefined4 *)(gGamepads + 0x29c) = 0;

  // if gamepads are connected
  if (gGamepads->numGamepadsConnected)
  {

	// for iVar4 = 0; iVar4 < numGamepads; iVar4++
    for (int i = 0; i < gGamepads->numGamepadsConnected; i++)
	{
    struct GamepadBuffer* pad = gGamepads->gamepad[i];
      *(uint *)(gGamepads + 0x290) = *(uint *)(gGamepads + 0x290) | pad->buttonsHeldCurrFrame;
      *(uint *)(gGamepads + 0x294) = *(uint *)(gGamepads + 0x294) | pad->buttonsTapped;
      *(uint *)(gGamepads + 0x298) = *(uint *)(gGamepads + 0x298) | pad->buttonsReleased;
      *(uint *)(gGamepads + 0x29c) = *(uint *)(gGamepads + 0x29c) | pad->buttonsHeldPrevFrame;
    } 
  }
  return uVar1 | uVar2;
}