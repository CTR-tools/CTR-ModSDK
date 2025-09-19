#ifndef RAND_H
#define RAND_H

#include <ctr/macros.h>

typedef struct RNGSeed
{
    u32 a;
    u32 b;
} RNGSeed;

u32 RNG_Rand();
s32 RNG_RandInt(u32 n);
u16 RNG_PseudoRand(u16 n);
u32 RNG_Random(RNGSeed* seed);

extern u32 e_seed; // 0x8008d424
extern RNGSeed e_gameTrackerSeed; // 0x8009904c

#endif