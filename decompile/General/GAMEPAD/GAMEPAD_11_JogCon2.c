#include <common.h>

void DECOMP_GAMEPAD_JogCon2(struct Driver* d, int val, int timeMS)
{
	// if AI
	if((d->actionsFlagSet & 0x100000) != 0)
		return;
	
	struct GamepadBuffer* gb = 
		&sdata->gGamepads->gamepad[d->driverID];
	
	gb->unk42 = val;
	gb->unk48 = timeMS;
}