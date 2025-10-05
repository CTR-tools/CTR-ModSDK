#pragma once

#include <stdbool.h>
#include <stddef.h>
#ifdef INTELLISENSE_HINT
#include <stdint-gcc.h>
#else
#include <stdint.h>
#endif

typedef uint64_t u64;
typedef int64_t  s64;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint8_t  u8;
typedef int8_t   s8;

#define U32_MAX UINT32_MAX
#define S32_MAX INT32_MAX
#define U16_MAX UINT16_MAX
#define S16_MAX INT16_MAX
#define U8_MAX UINT8_MAX
#define S8_MAX INT8_MAX

#define U32_MIN UINT32_MIN
#define S32_MIN INT32_MIN
#define U16_MIN UINT16_MIN
#define S16_MIN INT16_MIN
#define U8_MIN UINT8_MIN
#define S8_MIN INT8_MIN

#define AugReview 805
#define SepReview 903
#define UsaRetail 926
#define JpnTrial 1006
#define EurRetail 1020
#define JpnRetail 1111

#if BUILD == EurRetail
#define SCREEN_HEIGHT 236
#define FPS 25
#define ELAPSED_MS 40
#else
#define SCREEN_HEIGHT 216
#define FPS 30
#define ELAPSED_MS 32
#endif
#define SCREEN_WIDTH 512
#define SECOND (FPS * ELAPSED_MS)
#define MINUTE (SECOND * 60)
#define HOUR (MINUTE * 60)

#define SECONDS(x) ((s32)(((float)(x)) * SECOND))
#define MINUTES(x) ((s32)(((float)(x)) * MINUTE))
#define HOURS(x)   ((s32)(((float)(x)) * HOUR))

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))

#define nullptr ((void *) 0)
#define force_inline static inline __attribute__((always_inline))

//#define FIX_CTR_BUGS