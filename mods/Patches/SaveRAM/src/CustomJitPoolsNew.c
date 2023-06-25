#include <common.h>

// to do: add headers for project
void LOAD_Callback_DriverModels();
void ClearThreadPool(struct JitPool* ap);
void ClearDriverPool(struct JitPool* ap);

#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
void ANTICHIP_CheckFraud_Entry();
#endif

// MainInit_JitPoolsNew
void MainInit_JitPoolsNew_New(struct GameTracker* gGT)
{
  int clipSize;
  int *piVar4;
  int loop;
  int uVar3;
  int uVar7;
  int uVar9;
  int numDrivers;
  int i_0x1000;
  int medStackCount;

  // relocation
  {
	// add 2nd bookmark, which we'll use to restore
	// the mempack pointer when we're done with this
	MEMPACK_PushState();

	// 0x800091c0 - 0x80009f00
	// 0xc00 for oscillator
	// 0x140 for rain
	// 0x1000>>5 = 128, 0x1000>>9 = 8,
	sdata->mempack[0].firstFreeByte = (void*)0x800091C0;
	JitPool_Init(&gGT->JitPools.oscillator,128,0x18,0);
	JitPool_Init(&gGT->JitPools.rain,8,0x28,0);

	// 0x8000E3E0 - 0x80010000
	// 0x1c20 for small stack
	// 0x1000 * 0x19 >> 10 = 100 (dec 100 = 0x64 hex)
	sdata->mempack[0].firstFreeByte = (void*)0x8000E3E0;
	JitPool_Init(&gGT->JitPools.smallStack, 100, 0x48,0);

	// 0x1B00 shaved off heap
	// Original game wanted 96 threads, but the game
	// uses 48 max, simple mistake while scaling with instance pool
	ClearThreadPool(&gGT->JitPools.thread);

	// 0x3380 bytes,
	// half in 0x8000A000 region,
	// half in 0x8000C400 region
	// "Clear" is same as "Init" for this specific case
	ClearDriverPool(&gGT->JitPools.largeStack);

	// fix mempack, so it doesn't point
	// to kernel memory anymore
	MEMPACK_PopState();
  }

  uVar3 = gGT->gameMode1;

  // This happens if you're in Adventure Arena
  uVar7 = 0x800;

  if (
		// If you're not in Adventure Arena
		((uVar3 & 0x100000) == 0) &&

		(
			// This value sets if you're not in adventure
			// arena, and not in the main menu
			uVar7 = 0x1000,

			// If you're in main menu
			(uVar3 & 0x2000) != 0
		)
	  )
  {
	// This is set if not in Adventure Arena,
	// and if you're in main menu
    uVar7 = 0x400;
  }

  // =============
  // uVar9 only impacts InstancePool
  // =============

  // This happens if you're in Adventure Arena
  uVar9 = 64;

  // If you're not in Adventure Arena
  if ((uVar3 & 0x100000) == 0)
  {
	// If you're not in main menu
    if ((uVar3 & 0x2000) == 0) 
	{  
	  // 90 is too few for Dingo Canyon Arcade near start-line.
	  // Must have 90, plus 10 missiles, plus 7 mines, plus extra.
	  // Settled with 120, which is better than 128
	  uVar9 = 120;
    }

	// If you're in main menu
    else
	{
      uVar9 = 32;
    }
  }
  
  // add a bookmark (default for the game)
  MEMPACK_PushState();

  // do not store on RDATA, like previous versions did,
  // because thread optimization saves enough RAM, and
  // most other mods use RDATA when combined with oxide fix
  gGT->ptrRenderBucketInstance = (void*)MEMPACK_AllocMem(0x1000);

  JitPool_Init(&gGT->JitPools.instance, uVar9, 0x74 + (0x88 * gGT->numPlyrCurrGame),0);

  // everywhere else (main menu, race, adv hub, podiums)
  medStackCount = 12;

  // ND Box, oxide intro
  if((sdata->gGT->gameMode1 & GAME_CUTSCENE) != 0)
  {
	  medStackCount = 24;
  }

  // 0x660
  JitPool_Init(&gGT->JitPools.mediumStack,medStackCount,0x88,0);

  // 0x3e00
  JitPool_Init(&gGT->JitPools.particle,
	uVar7 >> 5,

	#if BUILD == SepReview
	0x84,0
	#elif BUILD >= UsaRetail
	0x7c,0
	#endif

	);

  // small, medium, large
  for(loop = 0; loop < 3; loop++)
  {
	// this goes to JitPool[SMALL+loop].free.first
	piVar4 = (int *)(
						(char*)&gGT->JitPools.smallStack +
						(sizeof(struct JitPool) * loop)
					);

    // loop through all objects, increment 8 bytes,
	// encapsulate the pointers to "next" and "prev"
	while (piVar4 != (int *)0x0) {
		*(int **)(piVar4 + 2) = piVar4 + 2;
		piVar4 = (int *)*piVar4;
	}
  }

  // MainDB_GetClipSize didn't exist in Sep3
  // build, instead it was just this:
  #if BUILD == SepReview

      if (gGT->levelID == NAUGHTY_DOG_CRATE) {
        clipSize = 96000>>2;
      }
      else {
        clipSize = 12000>>2;
        if (gGT->levelID == ADVENTURE_CHARACTER_SELECT) {
          clipSize = 0x1000>>2;
        }
      }

  #elif BUILD >= UsaRetail

  // get size
  clipSize = MainDB_GetClipSize(gGT->levelID,gGT->numPlyrCurrGame);

  #endif

  // clip buffer for each player
  for(loop = 0; loop < gGT->numPlyrCurrGame; loop++)
  {
	data.PtrClipBuffer[loop] = MEMPACK_AllocMem(clipSize << 2);
  }
}