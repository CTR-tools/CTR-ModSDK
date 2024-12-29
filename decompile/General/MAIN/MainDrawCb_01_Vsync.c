#include <common.h>

void DECOMP_MainDrawCb_Vsync()
{
	struct GameTracker* gGT;
	
	sdata->vsyncTillFlip--;
	
	gGT = sdata->gGT;
	gGT->frameTimer_VsyncCallback++;
	gGT->vSync_between_drawSync++;
	if ((gGT->gameMode1 & PAUSE_ALL) == 0) gGT->frameTimer_Confetti++;

	// 1 unit = 1/16th millisecond
	// 1 second = ~16,000 units
	// increment timer, and reset system clock
	sdata->rcntTotalUnits += GetRCnt(0xf2000001);
	ResetRCnt(0xf2000001);

	DECOMP_howl_PlayAudio_Update();

	#ifdef REBUILD_PC
	PsyX_UpdateInput();
	#endif
	
	DECOMP_GAMEPAD_PollVsync(sdata->gGamepads);	
	return;
}