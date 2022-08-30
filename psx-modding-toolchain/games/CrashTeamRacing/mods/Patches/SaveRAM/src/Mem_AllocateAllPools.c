#include <common.h>

// to do: add headers for project
void DrawHeat_Main();
void LOAD_Callback_DriverModels();
void ClearThreadPool(struct AllocPool* ap);
void ClearDriverPool(struct AllocPool* ap);

#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
void ANTICHIP_CheckFraud_Entry();
#endif

// only in builds 926+
int GetClipBufferSize(int levID, int numPlayers);

// To do: add header for CTR funcs
void AllocPool_Init(struct AllocPool* ap, int numItems, int itemSize);
void AllocPool_Clear(struct AllocPool* ap);
void* MEMPACK_AllocMem(int size); // no char* name needed
int MEMPACK_PushState();
void MEMPACK_PopState();
void LIST_Clear(struct LinkedList* L);
void LIST_AddFront(struct LinkedList* L, void* item);

// AllocateAllPools
void AllocateAllPools_New(struct GameTracker* gGT)
{
  int clipSize;
  int *piVar4;
  int loop;
  int uVar3;
  int uVar7;
  int uVar9;
  int numDrivers;
  int i_0x1000;

  // relocation
  {
	// add 2nd bookmark, which we'll use to restore
	// the mempack pointer when we're done with this
	MEMPACK_PushState();

	// 0x800091c0 - 0x80009f00
	// 0xc00 for oscillator
	// 0x140 for rain
	// 0x1000>>5 = 128, 0x1000>>9 = 8,
	sdata.mempack[0].firstFreeByte = (void*)0x800091C0;
	AllocPool_Init(&gGT->AllocPools.oscillator,128,0x18);
	AllocPool_Init(&gGT->AllocPools.rain,8,0x28);

	// 0x8000E3E0 - 0x80010000
	// 0x1c20 for small stack
	// 0x1000 * 0x19 >> 10 = 100 (dec 100 = 0x64 hex)
	sdata.mempack[0].firstFreeByte = (void*)0x8000E3E0;
	AllocPool_Init(&gGT->AllocPools.smallStack, 100, 0x48);

	// 0x1B00 shaved off heap
	// Original game wanted 96 threads, but the game
	// uses 48 max, simple mistake while scaling with instance pool
	ClearThreadPool(&gGT->AllocPools.thread);

	// 0x3380 bytes,
	// half in 0x8000A000 region,
	// half in 0x8000C400 region
	// "Clear" is same as "Init" for this specific case
	ClearDriverPool(&gGT->AllocPools.largeStack);

	// Japan builds relocate medium stack pool
	#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
	// overwrite anti-modchip functions, +8 to skip JR RA
	// 0x1100 for medium stack
	// 0x1000>>7 = 32
	sdata.mempack[0].firstFreeByte = (ANTICHIP_CheckFraud_Entry + 0x10);
	AllocPool_Init(&gGT->AllocPools.mediumStack, 32,0x88); // 0x1000>>7 = 32
	#endif

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
    if ((uVar3 & 0x2000) == 0) {
      uVar9 = 128;
    }

	// If you're in main menu
    else
	{
	  // only in japan builds
	  #if (BUILD == JpnTrial) || (BUILD == JpnRetail)

 	  // only do this during initialization of main menu,
	  // so this doesn't interfere with end-side allocation.
	  // Still needed even if every pool were relocated off heap

	  // save another 0x300 bytes to save Hot Air Skyway in 1P Arcade,
	  // increase sp min-addr from 801ff800 to 801ffb00
	  sdata.mempack[0].lastFreeByte = (void*)0x801ffb00;

	  #endif


      uVar9 = 32;

	  // 0x28(40) (AdvGarage)
      if (gGT->levelID == 0x28) {
        uVar9 = 64;
      }
    }
  }
  
  // add a bookmark (default for the game)
  MEMPACK_PushState();

  // do not store on RDATA, like previous versions did,
  // because thread optimization saves enough RAM, and
  // most other mods use RDATA when combined with oxide fix
  gGT->ptrRenderBucketInstance = (void*)MEMPACK_AllocMem(0x1000);

  AllocPool_Init(&gGT->AllocPools.instance, uVar9, 0x74 + (0x88 * gGT->numPlayers));

  // USA and PAL dont need to relocate
  #if (BUILD == UsaRetail) || (BUILD == EurRetail)
  // 0x1100
  AllocPool_Init(&gGT->AllocPools.mediumStack,
  	uVar7 >> 7,0x88);
  #endif

  // 0x3e00
  AllocPool_Init(&gGT->AllocPools.particle,
	uVar7 >> 5,

	#if BUILD == SepReview
	0x84
	#elif BUILD >= UsaRetail
	0x7c
	#endif

	);

  // small, medium, large
  for(loop = 0; loop < 3; loop++)
  {
	// this goes to AllocPool[SMALL+loop].free.first
	piVar4 = (int *)(
						(char*)&gGT->AllocPools.smallStack +
						(sizeof(struct AllocPool) * loop)
					);

    // loop through all objects, increment 8 bytes,
	// encapsulate the pointers to "next" and "prev"
	while (piVar4 != (int *)0x0) {
		*(int **)(piVar4 + 2) = piVar4 + 2;
		piVar4 = (int *)*piVar4;
	}
  }

  // GetClipBufferSize didn't exist in Sep3
  // build, instead it was just this:
  #if BUILD == SepReview

      if (gGT->levelID == 0x29) {
        clipSize = 96000>>2;
      }
      else {
        clipSize = 12000>>2;
        if (gGT->levelID == 0x28) {
          clipSize = 0x1000>>2;
        }
      }

  #elif BUILD >= UsaRetail

  // get size
  clipSize = GetClipBufferSize(gGT->levelID,gGT->numPlayers);

  #endif

  // clip buffer for each player
  for(loop = 0; loop < gGT->numPlayers; loop++)
  {
	data.PtrClipBuffer[loop] = MEMPACK_AllocMem(clipSize << 2);
  }
}