#include <common.h>

void RunEntryHook()
{
	// 4P 1 pad: Set 800255c4 to 1-byte 0x04
	
	// Find each by breakpointing function,
	// then find $ra and go back 2 instructions
	
	// [JAL hook] 	[RaceFlag_DrawSelf] 	(pink start/end)
	// [unk]								(black stall start)
	// [JAL hook]	[RenderBucket_Execute]	(green start/end)
	// [JAL hook]	[CTR_ClearRenderLists_1P2P]	(blue start) -- 1p
	// [JAL hook]	[CTR_ClearRenderLists_1P2P]	(blue start) -- 2p
	// [JAL hook]	[CTR_ClearRenderLists_3P4P]	(blue start) -- 3p
	// [JAL hook]	[CTR_ClearRenderLists_3P4P]	(blue start) -- 4p
	// [JAL hook]	[DrawSky_Full]			(blue end) -- 1p
	// [JAL hook]	[227]					(blue end) -- 2p
	// [JAL hook]	[228]					(blue end) -- 3p
	// [JAL hook]	[229]					(blue end) -- 4p
	// [JAL hook]	[DrawOTag]				(black end)
	// [JAL hook]	[MainFrame_GameLogic]	(red start/end)
}