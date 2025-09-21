#pragma once

#include <ctr/macros.h>
#include <ctr/rng.h>

typedef struct GameTracker
{
    u8 fill[0x252c];
    RNGSeed seed;
} GameTracker;

extern GameTracker* e_gameTracker;