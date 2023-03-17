#include <common.h>

void DECOMP_GAMEPAD_Vib_1(struct Driver* d, char param_2, char param_3)
{
  // If this is human and not AI
  if ((d->actionsFlagSet & 0x100000) == 0) {
    // Get pointer to this player's 0x50-byte gamepad buffer
    struct GamepadBuffer* pad = sdata->gGamepads->gamepad[d->driverID];
    if ((pad->unk_45 & 0xf) <= (param_2 & 0xf)) {
      pad->unk_45 = param_2;
      pad->unk_46 = param_3;
    }
    return;
  }
}

// called from 232, and in EXE near skidmark code
void DECOMP_GAMEPAD_Vib_2(struct Driver* d, char param_2, char param_3)
{
  // If this is human and not AI
  if ((d->actionsFlagSet & 0x100000) == 0) {
	// Get pointer to this player's 0x50-byte gamepad buffer
    struct GamepadBuffer* pad = sdata->gGamepads->gamepad[d->driverID];
    pad->data18[16] = param_2;
    pad->data4[0] = param_3;
  }
  return;
}

void DECOMP_GAMEPAD_Vib_3(struct Driver* d, int param_2, char param_3)
{
   // If this is human and not AI 
  if (((d->actionsFlagSet & 0x100000) == 0) && 
   // if p1 vibrate
    ((sdata->gGT->gameMode1 & 0x100 << ((uint)d->driverID & 0x1f)) == 0))
    {
        // Get pointer to this player's 0x50-byte gamepad buffer
        struct GamepadBuffer* pad = sdata->gGamepads->gamepad[d->driverID];
        if((pad->framesSinceLastInput < 0x385) && (pad->data18[4] < param_2))
        {
            pad->data18[4] = param_2;
            pad->data18[16] = param_3;
        }
    return;
    }
}

void DECOMP_GAMEPAD_Vib_4(struct Driver* d, char param_2, int param_3)
{
   // If this is human and not AI 
  if (((d->actionsFlagSet & 0x100000) == 0) && 
   // if p1 vibrate
    ((sdata->gGT->gameMode1 & 0x100 << ((uint)d->driverID & 0x1f)) == 0))
    {
        // Get pointer to this player's 0x50-byte gamepad buffer
        struct GamepadBuffer* pad = sdata->gGamepads->gamepad[d->driverID];
        if((pad->framesSinceLastInput < 0x385) && (pad->data18[20] < param_3))
        {
            pad->data18[8] = param_2;
            pad->data18[20] = (char)param_3;
        }
    return;
    }
}

void DECOMP_GAMEPAD_Vib_5(struct Driver* d, char param_2, int param_3)
{
  // If this is human and not AI 
  if (((d->actionsFlagSet & 0x100000) == 0) && 
   // if p1 vibrate
    ((sdata->gGT->gameMode1 & 0x100 << ((uint)d->driverID & 0x1f)) == 0))
    {
        // Get pointer to this player's 0x50-byte gamepad buffer
        struct GamepadBuffer* pad = sdata->gGamepads->gamepad[d->driverID];
        if((pad->framesSinceLastInput < 0x385) && (pad->data18[21] < param_3))
        {
            pad->data18[12] = param_2;
            pad->data18[21] = (char)param_3;
        }
    return;
    }
}