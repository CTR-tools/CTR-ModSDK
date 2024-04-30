#include "231_055_RB_GetThread_ClosestTracker.c"

// This came between 055 and 056, 
// even in OG game

// OG game allocated 50 of these,
// but only allowed up to 40 items,
// causing Nitro Court Crystal Challenge bug.
// Here, only allocate 40, save some RAM
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