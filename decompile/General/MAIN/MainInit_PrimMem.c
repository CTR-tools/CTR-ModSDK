#include <common.h>

void DECOMP_MainInit_PrimMem(struct GameTracker* gGT)
{
	int size;
	int levelID = gGT->levelID;
	
	// adv garage
	if(levelID == ADVENTURE_CHARACTER_SELECT)
	{
		size = 0x1b800;
		goto EndFunc;
	}
	
	// main menu
	if(levelID == MAIN_MENU_LEVEL)
	{
		size = 0x17c00;
		goto EndFunc;
	}
	
	if(gGT->numPlyrCurrGame == 1)
	{
		// any% end, 101% end, credits
		if(levelID >= OXIDE_ENDING)
		{
			size = 0x17c00;
			goto EndFunc;
		}
		
		// intro cutscene
		if(levelID >= INTRO_RACE_TODAY)
		{
			size = 0x1e000;
			goto EndFunc;
		}
		
		// adv hub
		if(levelID >= GEM_STONE_VALLEY)
		{
			size = 0x1c000;
			goto EndFunc;
		}
		
		// ordinary tracks

		// all are 0x67 or 0x5F, adv hub was 0x5F too
		size = data.primMem_SizePerLEV_1P[levelID] << 10;
		goto EndFunc;
	}
	
	if(gGT->numPlyrCurrGame == 2)
	{
		// assume only levID 0-24
		size = data.primMem_SizePerLEV_2P[levelID] << 10;
		goto EndFunc;
	}
	
	// 3P 4P
	// assume only levID 0-24
	size = data.primMem_SizePerLEV_4P[levelID] << 10;
	
EndFunc:
	DECOMP_MainDB_PrimMem(&gGT->db[0].primMem, size);
	DECOMP_MainDB_PrimMem(&gGT->db[1].primMem, size);
}

void DECOMP_MainInit_OTMem(struct GameTracker* gGT)
{
	int size;
	int levelID = gGT->levelID;
	
	// cutscenes, main menu, garage, ND Box, 
	// any% end, 101% end, credits
	if(levelID >= INTRO_RACE_TODAY)
	{
		size = 0x2000;
		goto EndFunc;
	}
	
	// Adv Hub
	if(levelID >= GEM_STONE_VALLEY)
	{
		size = 0x2c00;
		goto EndFunc;
	}
	
	// battle maps
	if(levelID >= NITRO_COURT)
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
	
EndFunc:
	DECOMP_MainDB_OTMem(&gGT->db[0].otMem, size * P_LEN);
	DECOMP_MainDB_OTMem(&gGT->db[1].otMem, size * P_LEN);
	
	// 0x1000 per player, plus 0x18 for linking
	size = (gGT->numPlyrCurrGame * 1024 + 6) * sizeof(OTTYPE);
	gGT->ot_tileView_UI[0] = DECOMP_MEMPACK_AllocMem(size); // "ot1"
	gGT->ot_tileView_UI[1] = DECOMP_MEMPACK_AllocMem(size); // "ot2"
}