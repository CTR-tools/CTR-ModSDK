#include <common.h>

void DECOMP_GAMEPAD_Init(struct GamepadSystem* gGamepads)
{
  PadInitMtap(gGamepads->padbuff[0][0],gGamepads->padbuff[2][34]);
  PadStartCom();

  for (int i = 0; i < 8; i++)
  {
    struct GamepadBuffer* pad = gGamepads->gamepad[i];
	// no analog sticks detected
    pad->gamepadType = 0;
    pad->unk_44_countdown = 0;
  }
  gGamepads->gamepadsConnectedByFlag = 0xffffffff;
  return;
}