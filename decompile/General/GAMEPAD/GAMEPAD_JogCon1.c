#include <common.h>

void DECOMP_GAMEPAD_JogCon1(struct Driver* d, int val, int timeMS)
{
	// if AI
	if((d->actionsFlagSet & 0x100000) != 0)
		return;
	
	struct GamepadBuffer* gb = 
		&sdata->gGamepads->gamepad[d->driverID];
	
	if((gb->unk45 & 0xf) > (val & 0xf))
		return;
	
	gb->unk45 = val;
	gb->unk46 = timeMS;
}