#include <ctr/rng.h>
#include <ctr/math.h>
#include <ctr/test.h>

#define RNG_MULT_FACTOR 0x6255
#define RNG_INC_FACTOR 0x3619

/* Address: 0x8003ea28 */
u32 RNG_Rand()
{
    BACKUP_RNG_Rand();
    e_seed = (e_seed * RNG_MULT_FACTOR + RNG_INC_FACTOR) & 0xFFFF;
    TEST_RNG_Rand();
    return e_seed;
}

/* Address: 0x8003ea6c */
s32 RNG_RandInt(u32 n)
{
    BACKUP_RNG_RandInt();
    const u32 rand = RNG_Random(&e_gameTrackerSeed);
    const s32 ret = ((s32) ((rand & 0xFFFF) * n)) >> 16;
    TEST_RNG_RandInt(n, ret);
    return ret;
}

/* Address: 0x8003eaac */
u16 RNG_PseudoRand(u16 n)
{
    const u16 ret = n * RNG_MULT_FACTOR + RNG_INC_FACTOR;
    TEST_RNG_PseudoRand(n, ret);
    return ret;
}

/* Address: 0x8006c684 */
u32 RNG_Random(RNGSeed* seed)
{
#ifdef TEST_RNG_IMPL
    RNGSeed inputSeed = *seed;
#endif
    const u32 x = seed->b >> 8;
    const u32 nextA = (seed->a >> 8) | (seed->b << 24);
    seed->b = (x | ((seed->a + x + (nextA >> 8)) << 24)) ^ 0xDEADC0ED;
    seed->a = nextA;
    TEST_RNG_Random(&inputSeed, seed);
    return seed->b;
}