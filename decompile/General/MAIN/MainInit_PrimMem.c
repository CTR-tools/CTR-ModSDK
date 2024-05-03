#include <common.h>

// force parameter is a personal optimization
void DECOMP_MainInit_PrimMem(struct GameTracker* gGT, int force)
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

#ifdef USE_HIGHMP

	if(force != 0)
		size = force/2;
	else
		size = 0x200000;

#else

	// optimization,
	// use all remaining heap for primMem,
	// LOAD_TenStages:Stage8
	#if 1
	if(force == 0)
	{
		// only for race tracks, menu/cutscenes
		// dont need PrimMem expansion, and also
		// menu/cutscene needs HighMem sometimes
		
		// gGT->levelID is set cause Stage8
		// is past all the level load+callback
		if(gGT->levelID <= CITADEL_CITY)
		{
			int newSize = (DECOMP_MEMPACK_GetFreeBytes()/2);
			
			// adjust for alignment
			// that can inflate size later
			newSize &= 0xffffffE0;
			
			// make room for ghost recording and two tapes
			if((gGT->gameMode1 & TIME_TRIAL) != 0)
				newSize -= (0x3E00+(0x268*2))/2;
				
			// if remaining size is less than OG requirement,
			// allocate way too much memory and crash the game
			if(newSize < size) 
			{
				printf("Missed by: %08x\n", (size-newSize)*2);
				DECOMP_MEMPACK_AllocMem(0x900000);
			}
			
			printf("BonusPrim: %08x\n", newSize-size);
			size = newSize;
		}
	}
	#endif
	
	// optimization,
	// steal OT mem during loading screen,
	// LOAD_TenStages:Stage0
	#if 1
		if(force != 0)
			size = force/2;
	#endif

#endif

#ifdef REBUILD_PC
	// only allocate early-stage
	if(force == 0) return;
	
	// allocate rest of 24-bit range
	size = 0x1000000 - (int)sdata->mempack[0].firstFreeByte;
	size /= 2;
	size -= 0x100;
#endif
	
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

#ifdef USE_HIGHMP
	size = 0x20000;
#endif

	DECOMP_MainDB_OTMem(&gGT->db[0].otMem, size);
	DECOMP_MainDB_OTMem(&gGT->db[1].otMem, size);
	
	// 0x1000 per player, plus 0x18 for linking
	size = ((gGT->numPlyrCurrGame) << 0xC) | 0x18;
	gGT->otSwapchainDB[0] = DECOMP_MEMPACK_AllocMem(size); // "ot1"
	gGT->otSwapchainDB[1] = DECOMP_MEMPACK_AllocMem(size); // "ot2"
}