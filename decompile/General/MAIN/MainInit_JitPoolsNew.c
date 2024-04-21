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

  // This happens if you're in Adventure Arena
  uVar7 = 0x800;

  if (
		// If you're not in Adventure Arena
		((gameMode & ADVENTURE_ARENA) == 0) &&

		(
			// This value sets if you're not in adventure
			// arena, and not in the main menu
			uVar7 = 0x1000,

			// If you're in main menu
			(gameMode & MAIN_MENU) != 0
		)
	  )
  {
	// This is set if not in Adventure Arena,
	// and if you're in main menu
    uVar7 = 0x400;
  }

  // This happens if you're in Adventure Arena
  uVar9 = 0x800;

  // If you're not in Adventure Arena
  if ((gameMode & ADVENTURE_ARENA) == 0)
  {
	// If you're not in main menu
    if ((gameMode & MAIN_MENU) == 0) {
      uVar9 = 0x1000;
    }

	// If you're in main menu
    else {
      uVar9 = 0x400;

      if (gGT->levelID == ADVENTURE_CHARACTER_SELECT) {
        uVar9 = 0x800;
      }
    }
  }

  // add a bookmark
  DECOMP_MEMPACK_PushState();

  int numThread = 0;
  int numInstance = 0;
  int numDriver = 0;
  
  int numInstLev = gGT->level1->numInstances;
  
  // if not set yet,
  // eliminate main menu
  if(numThread == 0)
  {
	switch(gGT->overlayIndex_Threads)
	{
		// 230: main menu
		// OG game uses: 32,24,4
		case 0:
			// 4 drivers, 4 camera threads,
			// Crash + Trophy + Animations,
			// plus 8 instances for Adv->Load
			numInstance = 24;
			numThread = 16;
			numDriver = 4;
			break;
		
		//// 231: race or battle
		//case 1:
		//	break;

		// 232: adv hub
		// OG game uses: 64,48,8
		case 2:
			numInstance = 64;
			numThread = 32;
			numDriver = 4;
			break;
		

		// 233: cutscene (and advhub podium->drive)
		// OG game uses: 64,48,8
		case 3:
			numInstance = 64;
			numThread = 32;
			numDriver = 4;
			break;
	}
  }
  
  // if not set yet,
  // eliminate the following:
  //	Crystal Challenge
  //	Time Trial
  //	Relic Race
  //	VS/Battle
  if(numThread == 0)
  {
	// Level: +66 inst (dingo canyon) +20 threads (mystery caves)
	//		4p is only +42 inst
	
	// MinePool +10 inst +10 thread
	// warpball +1 inst +1 thread
	
	// missile explosion +x*3 inst +x thread
	//		max missiles in flight (4p=8, 2p=6, 1p=3)
	
	// drivers/turbo + x*3 inst +x*2 thread
	//		1p=8, 2p=6, 4p=4, TimeTrial=3
	
	// camera +0 inst +numPlayer thread
	
	// tnt explosion +numPlayer*3 inst +0 thread
	//		assume 1 player hits one TNT,
	//		no added thread cause missile thread dies
	  
	// all of these use 231 overlayIndex_Threads
	switch(gGT->overlayIndex_EndOfRace)
	{
		// 221: Crystal Challenge
		// OG game uses: 128,96,8
		case 0:
			// hub4 challenge is 77 numInstLev
			// add 16 for explosion threads
			numInstance = numInstLev+16;
			numThread = numInstLev+16;
			numDriver = 1;
			break;
		
		// 222: adv/arcade
		// OG game uses: 128,96,8
		case 1:
			// dingo canyon is 66 numInstLev,
			// 2P Polar Pass Oxide+FakeCrash
			// is the max we can push in 2mb RAM
			numInstance = numInstLev+46; // risky, not enough
			numThread = 50;
			numDriver = 8;
			if(gGT->numPlyrCurrGame==2)
				numDriver = 6;
			break;
			
		// 223: relic race
		// OG game uses: 128,96,8
		case 2:
			// +16 instance for driver, hud, etc
			// +32 threads for track hazards + crate explosion + driver + camera
			numInstance = numInstLev+16;
			numThread = 32;
			numDriver = 1;
			break;

		// 224: time trial
		// OG game uses: 128,96,8
		case 3:
			// +16 instance for driver, hud, etc
			// +32 threads for track hazards + 
			//		3 drivers + 3 turbo threads + camera
			numInstance = numInstLev+16;
			numThread = 32;
			numDriver = 3;
			break;
			
		// 225: vs/battle
		// OG game uses: 128,96,8
		case 4:
			// highest numInstLev is 42 (mystery caves)
			numInstance = numInstLev+64;
			numThread = 64;
			numDriver = 4;
			break;
	}
  }

  // ThreadPool
  DECOMP_JitPool_Init(
	&gGT->JitPools.thread, 
	numThread, 
	sizeof(struct Thread),
	/*"ThreadPool"*/0);
  
  // InstancePool
  DECOMP_JitPool_Init(
	&gGT->JitPools.instance, 
	numInstance,
	sizeof(struct Instance) + (sizeof(struct InstDrawPerPlayer) * numPlyr), 
	/*"InstancePool"*/0);

  // SmallStackPool
  // OG game was 0x40+8,
  // changed now to 0x38+8 (UI_Element3d)
  DECOMP_JitPool_Init(
	&gGT->JitPools.smallStack, 
	numThread-numDriver,
	0x38 + sizeof(void*)*2,
	/*"SmallStackPool"*/0);
  
  int numMedium = uVar7 >> 7;
  if(numMedium > 20) numMedium = 20;
  
  // MediumStackPool
  // OG game was 0x80+8,
  // now changed to 0x60+8 (optimized Warppad)
  DECOMP_JitPool_Init(
	&gGT->JitPools.mediumStack, 
	numMedium,
	0x60 + sizeof(void*)*2,
	/*"MediumStackPool"*/0);

  // OG game used 0x670 for driver, should be 0x640,
  // maybe intended to mix RainPool into Driver struct?
  DECOMP_JitPool_Init(&gGT->JitPools.largeStack,numDriver, 	0x640,	/*"LargeStackPool"*/0);
  DECOMP_JitPool_Init(&gGT->JitPools.particle, 	uVar7 >> 5,	0x7c,	/*"ParticlePool"*/0);
  DECOMP_JitPool_Init(&gGT->JitPools.oscillator,uVar7 >> 5,	0x18,	/*"OscillatorPool"*/0);
  DECOMP_JitPool_Init(&gGT->JitPools.rain, 		numDriver,	0x28,	/*"RainPool"*/0);

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
  gGT->ptrRenderBucketInstance = (int)148 + (int)&rdata.s_STATIC_GNORMALZ[0];
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

