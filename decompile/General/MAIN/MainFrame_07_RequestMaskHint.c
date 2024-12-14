#include <common.h>

// Request Aku Hint, doesn't start till FUN_800b3dd8
// hintId:
//	0x00 - Welcome to Adventure Arena
//	0x01 - using a warp pad (part of welcome)
// 	0x02 - Need more trophies
//	0x03 - Need 4 trophies for Boss
//	0x04 - Need 4 keys for oxide
//	0x05 - Must have 1 Boss Key
//	0x06 - This is the load/save screen
// 	0x07 - Congrats on opening new area
//	0x12 - Must have 2 Boss Key
//	0x19 - Collect every crystal in arena
//	0x1a - CTR Token
//	0x1b - Gem Cups
//	0x1c - Must get 10 relics
//	0x1d - Relic
// param2:
//	0x00 - not interrupting a warppad load screen
// 	0x01 - interrupting (CTR, Relic, or Crystal hints)
void DECOMP_MainFrame_RequestMaskHint(short hintId, char interruptWarpPad)
{
  struct GameTracker* gGT = sdata->gGT;
	
  if (((gGT->gameMode1 & PAUSE_ALL) == 0) &&
		(sdata->AkuHint_RequestedHint == -1))
  {
    sdata->AkuAkuHintState = 1;

    gGT->drivers[0]->funcPtrs[0] = DECOMP_VehPhysProc_FreezeEndEvent_Init;

	sdata->AkuHint_RequestedHint = hintId;
	sdata->AkuHint_boolInterruptWarppad = interruptWarpPad;
  }
  return;
}