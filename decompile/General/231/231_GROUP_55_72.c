
// NOT ready to defrag full region until globals are in
#if 0

#include "231_055_RB_GetThread_ClosestTracker.c"

// This came between 055 and 056, 
// even in OG game

// 800b295c (OG addr)
short tntSitArr[] =
{
	
}

// 800b2ac4 (OG addr)
short tntThrowArr[] =
{
	
}

// 800b2ae4 (OG addr)
struct ParticleEmitter emSet_Missile[] =
{
	
}

// 800b2c88 (OG addr)
short warpballScaleArr[] =
{
	
}

// 800b2cac (OG addr)
short warpballPosArr[] =
{
	
}

// 800b2cc4 (OG addr)
short maskPosArr[] =
{
	
}

// 800b2d14 (OG addr)
short bubbleScaleArr1[] =
{
	
}

// 800b2cf4 (OG addr)
short bubbleScaleArr2[] =
{
	
}

// 800b2d40 (OG addr)
short bubbleScaleArr3[] =
{
	
}
#endif



// === WARNING ===
// All the MinePool stuff is now double-allocated
// because the block compiles to Baron instead of
// RB_GetThread_ClosestTracker




// OG game allocated 50 of these,
// but only allowed up to 40 items,
// causing Nitro Court Crystal Challenge bug.
// Here, only allocate 40, save some RAM
#include <common.h>
struct WeaponSlot231 minePoolItem[40];
struct LinkedList minePoolTaken;
struct LinkedList minePoolFree;

#include "231_056_057_RB_Baron.c"
#include "231_058_059_RB_Blade.c"

#ifndef REBUILD_PC
#include "231_060_RB_Bubbles_RoosTubes.c"
#include "231_061_068_RB_Crate.c"
#include "231_069_072_RB_Crystal.c"
#endif