#include <common.h>

void DECOMP_MainInit_JitPoolsNew(struct GameTracker *gGT)
{
  char numPlyr;
  u_int gameMode;
  struct JitPool *pool;
  u_int uVar5;
  u_int uVar7;
  u_int uVar9;
  int* pointer;

  // game mode
  gameMode = gGT->gameMode1;
  numPlyr = gGT->numPlyrCurrGame;

  // Adventure Arena, 1P No Weapons
  uVar7 = 0x800;

  if (
		// If you're not in Adventure Arena
		((gameMode & ADVENTURE_ARENA) == 0) &&
		(
			// All racing gameplay
			uVar7 = 0x1000,

			// If you're in main menu
			(gameMode & MAIN_MENU) != 0
		)
	  )
  {
	// Main Menu, bare minimum
    uVar7 = 0x400;
  }

  // Adventure Arena, 1P No Weapons
  uVar9 = 0x800;

  // If you're not in Adventure Arena
  if ((gameMode & ADVENTURE_ARENA) == 0)
  {
	// All racing gameplay
    if ((gameMode & MAIN_MENU) == 0) {
      uVar9 = 0x1000;
    }

    else
	{
	  // Main Menu, bare minimum
      uVar9 = 0x400;

      if (gGT->levelID == ADVENTURE_GARAGE)
	  {
        uVar9 = 0x800;
      }
    }
  }


  // assume RAMEX,
  // always have 8 drivers
  #ifdef USE_ONLINE
  uVar7 = 0x1000;
  uVar9 = 0x1000;
  #endif


  // add a bookmark
  DECOMP_MEMPACK_PushState();


// 2mb RAM, decomp/General, ram holes
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX) && defined(USE_ALTMODS)
  // saves 0x1B00 bytes
  void RelocMemory_DefragUI_Mods1_ThreadPool();
  int backup = (int)sdata->mempack[0].firstFreeByte;
  sdata->mempack[0].firstFreeByte = (void*)RelocMemory_DefragUI_Mods1_ThreadPool;
#endif


  // normally maxed at 96
  int numThread = uVar9 * 3 >> 7;

  // ThreadPool
  DECOMP_JitPool_Init(
	&gGT->JitPools.thread, numThread,
	sizeof(struct Thread), /*"ThreadPool"*/0);


// 2mb RAM, decomp/General, ram holes
// 8000F000 - 8000F820 to MediumStackPool
// 8000F820 - 8000FFF0 to $sp stack memory
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX) && defined(USE_ALTMODS)
  sdata->mempack[0].firstFreeByte = (void*)0x8000F000;
#endif


  // normally maxed at 32
  int numMedium = uVar7 >> 7;
  if(numMedium > 20) numMedium = 20;

  // MediumStackPool
  // OG game was 0x80+8,
  // now changed to 0x60+8 (optimized WarpPad)
  // WarpPad is the largest struct that uses MedStackPool
  DECOMP_JitPool_Init(
	&gGT->JitPools.mediumStack, numMedium,
	sizeof(struct Item) + sizeof(struct WarpPad), 
	/*"MediumStackPool"*/0);


// 2mb RAM, decomp/General, ram holes
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX) && defined(USE_ALTMODS)
  sdata->mempack[0].firstFreeByte = (void*)backup;
  
  if(
		// override, only if 3P4P VS
		(gGT->numPlyrCurrGame > 2) &&
		
		// main menu is "4p" dont corruput 1p overlay
		(gGT->levelID != MAIN_MENU_LEVEL)
	)
  {
	  void OVR_Region3();
	  unsigned int addrSmallPool = (unsigned int)OVR_Region3;
	  addrSmallPool -= 6500;
	  sdata->mempack[0].firstFreeByte = (void*)addrSmallPool;
  }
#endif


  // normally maxed at 100
  int numSmall = uVar7 * 0x19 >> 10;

  // SmallStackPool
  // OG game was 0x40+8,
  // changed now to 0x38+8 (og UiElement3D)
  // UiElement3D is the largest struct that uses SmallStackPool
  DECOMP_JitPool_Init(
	&gGT->JitPools.smallStack, numSmall,
	sizeof(struct Item) + sizeof(struct UiElement3D),  
	/*"SmallStackPool"*/0);


// 2mb RAM, decomp/General, ram holes
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX) && defined(USE_ALTMODS)
  if(
		// override, only if 3P4P VS
		(gGT->numPlyrCurrGame > 2) &&
		
		// main menu is "4p" dont corruput 1p overlay
		(gGT->levelID != MAIN_MENU_LEVEL)
	)
	{
	  sdata->mempack[0].firstFreeByte = (void*)backup;
	}
#endif


  // normally maxed at 128
  int numInstance = uVar9 >> 5;

  // Optimization tech
  if (numInstance == 128)
  {
	#if defined(USE_LEVELDEV) || defined(USE_LEVELDISC)
	
	// custom tracks have no level instances,
	// no weapons, nothing on the track
	numInstance = 32;
	
	// Extend bit range of quadblockID,
	// upper bits are never used, but still
	// need AND for alignment with LW instruction
	*(unsigned short*)0x800a0f18 = 0xFFFC;
	*(unsigned short*)0x800a1e80 = 0xFFFC;
	*(unsigned short*)0x800a36d8 = 0xFFFC;
	*(unsigned short*)0x800a4fd0 = 0xFFFC;
	*(unsigned short*)0x800a6f70 = 0xFFFC;
	*(unsigned short*)0x800a8b90 = 0xFFFC;
	
	#else
		
	if(gGT->numPlyrCurrGame == 1)
	{
		// Do NOT touch Crystal Challenge, AdvHub, Cutscene,
		// only apply to race tracks: TimeTrial/Relic/Arcade
		if(gGT->levelID <= TURBO_TRACK)
		{
			// Except Dingo Canyon,
			// This track is why we need 128 in the first place,
			// Rest of tracks are MORE than 16 behind Dingo Canyon
			if(gGT->levelID != DINGO_CANYON)
			{
				numInstance -= 16;
			}
		}
	}
	
	else
	{
		// Apply to VS and Battle
		if(gGT->levelID <= LAB_BASEMENT)
		{
			numInstance -= 16;
		}
	}
	
	#endif
  }

  // InstancePool
  DECOMP_JitPool_Init(
	&gGT->JitPools.instance, numInstance,
	sizeof(struct Instance) + (sizeof(struct InstDrawPerPlayer) * numPlyr),
	/*"InstancePool"*/0);
	
	
  int numDriver = uVar7 >> 9;
  if (gGT->numPlyrCurrGame == 2) numDriver = 6;
  if (gGT->numPlyrCurrGame > 2) numDriver = 4;
  if ((gameMode & TIME_TRIAL) != 0) numDriver = 3;
  if ((gameMode & MAIN_MENU) != 0) numDriver = 4;

  #ifdef USE_ONLINE
  numDriver = 8;
  #endif

  // OG game used 0x670 for driver, should be 0x640,
  // maybe intended to mix RainPool into Driver struct?
  DECOMP_JitPool_Init(&gGT->JitPools.largeStack,numDriver, 	sizeof(struct Item) + sizeof(struct Driver),	/*"LargeStackPool"*/0);
  DECOMP_JitPool_Init(&gGT->JitPools.rain, 		numDriver,	sizeof(struct RainLocal),	/*"RainPool"*/0);



  // Must be 64 in adventure arena,
  // normally maxed at 128
  int numParticle = uVar7 >> 5;
  if(numParticle > 120) numParticle = 120;

  #ifdef USE_ONLINE
  // fix mystery caves with 8 players,
  // cause all drivers use P1 exhaust
  numParticle = 120*10;
  #endif

  DECOMP_JitPool_Init(&gGT->JitPools.particle, 	numParticle,sizeof(struct Particle),	/*"ParticlePool"*/0);
  DECOMP_JitPool_Init(&gGT->JitPools.oscillator,numParticle,0x18,	/*"OscillatorPool"*/0);



#ifdef REBUILD_PS1
  // original CTR code, still used for
  // REBUILD_PS1 and REBUILD_PC cause those
  // builds dont have OG game's bloatful RDATA
  gGT->ptrRenderBucketInstance = DECOMP_MEMPACK_AllocMem(uVar9/*,"RENDER_BUCKET_INSTANCE"*/);
#else
  // save 0x400 - 0x1000 bytes
  // when compiling with OG game's RDATA
  // then expand PrimMem in 60fps,
  // add 148 bytes cause of MATH_Sin relocated
  gGT->ptrRenderBucketInstance = (void*)((int)148 + (int)&rdata.s_STATIC_GNORMALZ[0]);
#endif



// ===========================================



  // small, medium, large
  for(int i = 0; i < 3; i++)
  {
	// this goes to JitPool[SMALL+i].free.first
	pointer = (int *)(
						(char*)&gGT->JitPools.smallStack +
						(sizeof(struct JitPool) * i)
					);

    // loop through all objects, increment 8 bytes,
	// encapsulate the pointers to "next" and "prev"
	while (pointer != (int *)0x0) {
		*(int **)(pointer + 2) = pointer + 2;
		pointer = (int *)*pointer;
	}
  }

  for (int i = 0; i < numPlyr; i++)
  {
    data.PtrClipBuffer[i] =
		DECOMP_MEMPACK_AllocMem(
			DECOMP_MainDB_GetClipSize(gGT->levelID, numPlyr) << 2
			/*,"Clip Buffer"*/);
  }
}

