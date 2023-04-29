#include <common.h>

void DECOMP_GAMEPAD_Vib_1(struct Driver* d, char param_2, char param_3)
{
  // If this is human and not AI
  if ((d->actionsFlagSet & 0x100000) == 0) {
    // Get pointer to this player's 0x50-byte gamepad buffer
    struct GamepadBuffer* pad = &sdata->gGamepads->gamepad[d->driverID];
    if ((pad->unk_45 & 0xf) <= (param_2 & 0xf)) {
      pad->unk_45 = param_2;
      pad->unk_46 = param_3;
    }
    return;
  }
}