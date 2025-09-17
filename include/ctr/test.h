#ifndef TEST_H
#define TEST_H

#include <ctr/macros.h>

void LoadTestPatches();

#define TEST_MATH_IMPL

#ifdef TEST_MATH_IMPL
    void TEST_MATH_Sin(u32 angle, s32 res);
#else
    #define TEST_MATH_Sin(angle, res)
#endif

#endif