#include <common.h>

void DECOMP_GAMEPAD_ShockForce1(struct Driver* d, int frame, int val)
{
	// if AI
	if((d->actionsFlagSet & 0x100000) != 0)
		return;
	
	// 0 for enabled,
	// 1 for disabled
	if((sdata->gGT->gameMode1 & (0x100 << d->driverID)) != 0)
		return;
	
	struct GamepadBuffer* gb = 
		&sdata->gGamepads->gamepad[d->driverID];
		
	if(gb->framesSinceLastInput >= 0x385)
		return;
	
	if(gb->shockValForce1 >= val)
		return;
	
	gb->shockFrameForce1 = frame;
	gb->shockValForce1 = val;
}