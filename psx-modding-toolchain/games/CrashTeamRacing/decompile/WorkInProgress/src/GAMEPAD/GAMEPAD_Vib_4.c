#include <common.h>

void DECOMP_GAMEPAD_Vib_4(struct Driver* d, char param_2, int param_3)
{
   // If this is human and not AI 
  if (((d->actionsFlagSet & 0x100000) == 0) && 
   // if p1 vibrate
    ((sdata->gGT->gameMode1 & P1_VIBRATE << d->driverID) == 0))
    {
        // Get pointer to this player's 0x50-byte gamepad buffer
        struct GamepadBuffer* pad = &sdata->gGamepads->gamepad[d->driverID];
        if((pad->framesSinceLastInput < 0x385) && (pad->data18[20] < param_3))
        {
            pad->data18[8] = param_2;
            pad->data18[20] = (char)param_3;
        }
    return;
    }
}