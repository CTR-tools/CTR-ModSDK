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
	// For Arcade/Battle
	// worst case thread in race: 48
	// +10 for mine pool
	// +8 drivers
	// +4 camera
	// +1 warpball
	// 1p	+3*3 for missile explosions 3*3
	// 1p	+10 for mystery caves turtles
	// 4p	+8*3 for missile explosions (3+3+1+1)*3
	  
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
			// dingo canyon is 66 numInstLev
			numInstance = numInstLev+40;
			numThread = 48;
			numDriver = 8;
			if(gGT->numPlyrCurrGame==2)
				numDriver = 6;
			break;
			
		// 223: relic race
		// OG game uses: 128,96,8
		case 2:
			// +16 instance for driver, hud, etc
			// +32 threads for track hazards + crate explosion + driver + camera
			numInstance = numInstLev + 16;
			numThread = 32;
			numDriver = 1;
			break;

		// 224: time trial
		// OG game uses: 128,96,8
		case 3:
			// +16 instance for driver, hud, etc
			// +24 threads for track hazards + ghosts + driver + camera
			numInstance = numInstLev + 16;
			numThread = 24;
			numDriver = 3;
			break;
			
		// 225: vs/battle
		// OG game uses: 128,96,8
		case 4:
			// highest numInstLev is 42 (mystery caves)
			numInstance = numInstLev+48;
			numThread = 48;
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
  DECOMP_JitPool_Init(
	&gGT->JitPools.smallStack, 
	numThread,
	0x40 + sizeof(void*)*2,
	/*"SmallStackPool"*/0);
  
  // MediumStackPool
  DECOMP_JitPool_Init(
	&gGT->JitPools.mediumStack, 
	uVar7 >> 7,
	0x80 + sizeof(void*)*2,
	/*"MediumStackPool"*/0);

  DECOMP_JitPool_Init(&gGT->JitPools.largeStack,numDriver, 	0x670,	/*"LargeStackPool"*/0);
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

