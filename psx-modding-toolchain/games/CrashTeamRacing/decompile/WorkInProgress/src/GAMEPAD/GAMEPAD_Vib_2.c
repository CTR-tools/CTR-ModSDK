#include <common.h>

// called from 232, and in EXE near skidmark code
void DECOMP_GAMEPAD_Vib_2(struct Driver* d, char param_2, char param_3)
{
  // If this is human and not AI
  if ((d->actionsFlagSet & 0x100000) == 0) {
	// Get pointer to this player's 0x50-byte gamepad buffer
    struct GamepadBuffer* pad = &sdata->gGamepads->gamepad[d->driverID];
    pad->data18[16] = param_2;
    pad->data4[0] = param_3;
  }
  return;
}