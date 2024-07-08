#ifndef MACROS_H
#define MACROS_H

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

#define SECONDS(x) ((s32)(((float)x) * SECOND))
#define MINUTES(x) ((s32)(((float)x) * MINUTE))
#define HOURS(x)   ((s32)(((float)x) * HOUR))

#define nullptr ((void *) 0)

#ifndef REBUILD_PC
#define force_inline static inline __attribute__((always_inline))
#else
#define force_inline static inline
#endif

#define len(arr) (sizeof(arr) / sizeof(arr[0]))
#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))

#define RGBtoBGR(color) \
	((color & 0xFF0000) >> 16) | (color & 0xFF00) | ((color & 0xFF) << 16)

#define GetRed(color) \
	(color & 0xFF)

#define GetGreen(color) \
	(color & 0xFF00)>>8

#define GetBlue(color) \
	(color & 0xFF0000)>>16

#define aspectratioupsample(int) \
	(int*7)/4

#define aspectratiodownsample(int) \
	(int*4)/7

#endif