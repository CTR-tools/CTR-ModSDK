#include <common.h>

void MainInit_JitPoolsNew(struct GameTracker *gGT)
{
  char numPlyr;
  u_int gameMode;
  struct JitPool *pool;
  u_int uVar5;
  u_int uVar7;
  u_int uVar9;

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
  MEMPACK_PushState();

  JitPool_Init(&gGT->JitPools.thread,uVar9 * 3 >> 7,0x48,"ThreadPool");
  // instance size changes based on numPlyrCurrGame
  JitPool_Init(&gGT->JitPools.instance, uVar9 >> 5,0x74 + (0x88 * numPlyr), "InstancePool");
  JitPool_Init(&gGT->JitPools.smallStack, uVar7 * 0x19 >> 10,0x48,"SmallStackPool");
  JitPool_Init(&gGT->JitPools.mediumStack, uVar7 >> 7,0x88,"MediumStackPool");

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

  JitPool_Init(&gGT->JitPools.largeStack, uVar5 , 0x670,"LargeStackPool");

  JitPool_Init(&gGT->JitPools.particle, uVar7 >> 5,0x7c,"ParticlePool");

  JitPool_Init(&gGT->JitPools.oscillator, uVar7 >> 5,0x18,"OscillatorPool");

  JitPool_Init(&gGT->JitPools.rain, uVar7 >> 9,0x28,"RainPool");

  // render bucket instance
  gGT->ptrRenderBucketInstance = MEMPACK_AllocMem(uVar9,"RENDER_BUCKET_INSTANCE");

// ===========================================

  // 0x1920 (smallstack)
  // increment every pointer by 8 bytes,
  // to encapsulate "next" and "prev" in objects
  pool = &gGT->JitPools.smallStack;
  while (pool != NULL) {
    pool->free.count = pool + 2;
    pool = pool->free.first;
  }
  
  // 0x1948 (medstack)
  // increment every pointer by 8 bytes,
  // to encapsulate "next" and "prev" in objects
  pool = &gGT->JitPools.mediumStack;
  while (pool != NULL) {
    *(int **)(pool + 2) = pool + 2;
    pool = (int *)*pool;
  }
  
  // 0x1970 (largestack)
  // increment every pointer by 8 bytes,
  // to encapsulate "next" and "prev" in objects
  pool = &gGT->JitPools.largeStack;
  while (pool != NULL)
  {
    *(int **)(pool + 2) = pool + 2;
    pool = (int *)*pool;
  }

  // numPlyr is not zero
  if (numPlyr)
  {

	for (char i = 0; i < numPlyr; i++)
    {			
      data.PtrClipBuffer[i] = MEMPACK_AllocMem( 
                MainDB_GetClipSize(gGT->levelID, numPlyr) << 2,
                "Clip Buffer");
    } 
  }
}

