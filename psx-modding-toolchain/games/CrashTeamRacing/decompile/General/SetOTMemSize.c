#include <common.h>

void SetOTMemSize(struct GameTracker* gGT)
{
	int size;
	int levelID = gGT->levelID;
	
	// cutscenes, main menu, garage, ND Box, 
	// any% end, 101% end, credits
	if(levelID >= 30)
	{
		size = 0x2000;
		goto EndFunc;
	}
	
	// Adv Hub
	if(levelID >= 25)
	{
		size = 0x2c00;
		goto EndFunc;
	}
	
	// battle maps
	if(levelID >= 18)
	{
		size = 0x8000;
		goto EndFunc;
	}
	
	// 1P/2P mode
	if(gGT->numPlyrCurrGame < 3)
	{
		size = 0x2000;
		goto EndFunc;
	}
	
	// 3P/4P mode
	size = 0x3000;
	goto EndFunc;
	
EndFunc:
	Alloc_OTMem(&gGT->db[0].otMem, size);
	Alloc_OTMem(&gGT->db[1].otMem, size);
	
	// 0x1000 per player, plus 0x18 for linking
	size = ((gGT->numPlyrCurrGame) << 0xC) | 0x18;
	gGT->ot_camera110_UI[0] = MEMPACK_AllocMem(size, 0);
	gGT->ot_camera110_UI[1] = MEMPACK_AllocMem(size, 0);
}

