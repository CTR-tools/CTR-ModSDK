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

  // OG game uses either 24, 48, or 96
  int numThreads = uVar9 * 3 >> 7;

  // Niko optimization, 
  // game never uses more than 64
  if(numThreads > 64)
	  numThreads = 64;

  // ThreadPool
  DECOMP_JitPool_Init(
	&gGT->JitPools.thread,
	numThreads,
	0x48,/*"ThreadPool"*/0);
  
  // InstancePool
  DECOMP_JitPool_Init(
	&gGT->JitPools.instance, 
	uVar9 >> 5,
	sizeof(struct Instance) + (sizeof(struct InstDrawPerPlayer) * numPlyr), /*"InstancePool"*/0);

  // SmallStackPool
  DECOMP_JitPool_Init(
	&gGT->JitPools.smallStack, 
	uVar7 * 0x19 >> 10,
	0x40 + sizeof(void*)*2,/*"SmallStackPool"*/0);
  
  // MediumStackPool
  DECOMP_JitPool_Init(
	&gGT->JitPools.mediumStack, 
	uVar7 >> 7,
	0x80 + sizeof(void*)*2,/*"MediumStackPool"*/0);

  // if you're not in main menu
  if ((gameMode & MAIN_MENU) == 0)
  {
	// allocate 8 driver structs
    uVar5 = uVar7 >> 9;
  }
  // if you are in main menu
  else
  {
	// allocate 4 driver structs
    uVar5 = 4;
  }

  DECOMP_JitPool_Init(&gGT->JitPools.largeStack,uVar5, 		0x670,	/*"LargeStackPool"*/0);
  DECOMP_JitPool_Init(&gGT->JitPools.particle, 	uVar7 >> 5,	0x7c,	/*"ParticlePool"*/0);
  DECOMP_JitPool_Init(&gGT->JitPools.oscillator,uVar7 >> 5,	0x18,	/*"OscillatorPool"*/0);
  DECOMP_JitPool_Init(&gGT->JitPools.rain, 		uVar7 >> 9,	0x28,	/*"RainPool"*/0);

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

