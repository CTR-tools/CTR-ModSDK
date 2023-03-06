#include <common.h>

void MainDrawCallback_Vsync()
{
	struct GameTracker* gGT;
	int iVar2;
	
	gGT = sdata->gGT;
	sdata->gGT->frameTimer_VsyncCallback++;

	// If game is not paused
	if ((sdata->gGT->gameMode1 & 0xfU) == 0) gGT->frameTimer_Confetti++;

	// frame duplicator
	sdata->vsyncTillFlip--;

	// count vsync calls between drawsync
	sdata->gGT->vSync_between_drawSync++;

	// elapsed units since previous vsync
	// 1 unit = 1/16th millisecond
	iVar2 = GetRCnt(0xf2000001);

	// increment system
	// 1 second = ~16,000 units
	sdata->rcnt_elapsedUnits_betweenVsyncs += iVar2;

	// reset timer
	ResetRCnt(0xf2000001);

	howl_PlayAudio_Update();
	GAMEPAD_CheckUnplugged(sdata->gGamepads);
	return;
}