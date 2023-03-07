#include <common.h>

void MainDrawCb_Vsync()
{
	struct GameTracker* gGT;
	
	sdata->vsyncTillFlip--;
	
	gGT = sdata->gGT;
	gGT->frameTimer_VsyncCallback++;
	gGT->vSync_between_drawSync++;
	if ((gGT->gameMode1 & 0xfU) == 0) gGT->frameTimer_Confetti++;

	// 1 unit = 1/16th millisecond
	// 1 second = ~16,000 units
	// increment timer, and reset system clock
	sdata->rcnt_elapsedUnits_betweenVsyncs += GetRCnt(0xf2000001);
	ResetRCnt(0xf2000001);

	howl_PlayAudio_Update();
	GAMEPAD_CheckUnplugged(sdata->gGamepads);
	return;
}