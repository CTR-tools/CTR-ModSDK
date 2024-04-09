#ifndef PSYX_CONFIG_H
#define PSYX_CONFIG_H

// Uses 32 bit pointers on P_TAG and other primitives
// When turned off also disables PGXP

#ifndef USE_EXTENDED_PRIM_POINTERS
#define USE_EXTENDED_PRIM_POINTERS 0
#endif

// PGXP-Z: Precise GTE transform pipeline with Z-depth and widescreen fixes. Recommended for game mode
#ifndef USE_PGXP
#define USE_PGXP USE_EXTENDED_PRIM_POINTERS
#endif

#endif // PSYX_CONFIG_H