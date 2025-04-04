#include <common.h>

void DECOMP_MainInit_PrimMem(
	struct GameTracker* gGT

	#ifdef USE_MOREPRIM
	, int force
	#endif
)

{
	int GetOriginalSize(struct GameTracker* gGT);
	int size = GetOriginalSize(gGT);

	int backup = 0;

#ifdef USE_MOREPRIM

  // On PS1
  // Stage 0 allocates PrimMem to HighMem,
  // Stage 7 allocates PrimMem to fill rest of RAM
  #ifndef REBUILD_PC
	
	// optimization,
	// LOAD_TenStages: Stage 0,
	// allocate HighMem for checkered flag
	if(force != 0)
	{
		size = force/2;
		
		backup = (int)sdata->mempack[0].firstFreeByte;
		
		sdata->mempack[0].firstFreeByte = 
			(void*)((int)sdata->mempack[0].lastFreeByte
			- 0xA000 // primMem needed
			- (0x2200*2)); // ghost HighMem
	}

	// optimization,
	// LOAD_TenStages: Stage 7,
	// allocate all remaining RAM
	else
	{
		// gGT->levelID is set cause Stage 7
		// is past all the level load+callback
		if (gGT->levelID <= CITADEL_CITY)
		{
			#ifdef USE_NEWLEV
			// store the memory here, past the level
			sdata->PtrMempack->firstFreeByte = 0x80400000;
			#endif
				
			int newSize = (DECOMP_MEMPACK_GetFreeBytes()/2);
			
			// adjust for alignment
			// that can inflate size later
			newSize &= 0xffffffE0;
			
			// make room for ghost recording and two tapes
			if((gGT->gameMode1 & TIME_TRIAL) != 0)
			{
				//newSize -= (0x3E00+(0x268*2))/2;
				newSize -= 0x2200;
			}
				
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

  // On PC
  // Stage 0 allocates all 24-bit RAM to primitives,
  // Stage 7 does nothing,
  // The rest of LOAD_TenStages can use 
  // 		32-bit addresses above 24-bit max
  #else
	
	// optimization,
	// LOAD_TenStages: Stage 0
	if(force != 0)
	{
		// allocate rest of 24-bit range
		size = 0x1000000 - (int)sdata->mempack[0].firstFreeByte;
		size /= 2;
		size -= 0x100;
	}
	
	// optimization,
	// LOAD_TenStages: Stage 7,
	else
	{
		return;
	}

  #endif // PS1 or PC
  
#endif // USE_MOREPRIM
	
	DECOMP_MainDB_PrimMem(&gGT->db[0].primMem, size);
	DECOMP_MainDB_PrimMem(&gGT->db[1].primMem, size);
	
#ifdef USE_MOREPRIM
	
  #ifndef REBUILD_PC
	// Stage 0:
	// restore firstFreeByte for the rest
	// of the LOAD_TenStages loading system
	if(backup != 0)
	{
		sdata->mempack[0].firstFreeByte = (void*)backup;
	}
  #endif

#endif

}

int GetOriginalSize(struct GameTracker* gGT)
{
	int levelID = gGT->levelID;
	
	// adv garage
	if(levelID == ADVENTURE_GARAGE)
		return 0x1b800;
	
	// main menu
	if(levelID == MAIN_MENU_LEVEL)
		return 0x17c00;
	
	if(gGT->numPlyrCurrGame == 1)
	{
		// any% end, 101% end, credits
		if(levelID >= OXIDE_ENDING)
			return 0x17c00;
		
		// intro cutscene
		if(levelID >= INTRO_RACE_TODAY)
			return 0x1e000;
		
		// adv hub
		if(levelID >= GEM_STONE_VALLEY)
			return 0x1c000;
		
		// ordinary tracks

		// all are 0x67 or 0x5F, adv hub was 0x5F too
		return data.primMem_SizePerLEV_1P[levelID] << 10;
	}
	
	if(gGT->numPlyrCurrGame == 2)
	{
		// assume only levID 0-24
		return data.primMem_SizePerLEV_2P[levelID] << 10;
	}
	
	// 3P 4P
	// assume only levID 0-24
	return data.primMem_SizePerLEV_4P[levelID] << 10;
}