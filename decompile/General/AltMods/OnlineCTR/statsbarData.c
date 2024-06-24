#include <common.h>

#define NUM_STATS 3
#define NUM_CLASS 4

#define STATBAR_BLUE 0xC80000
#define STATBAR_BLUEGREEN 0xA8700
#define STATBAR_GREENYELLOW 0xB428
#define STATBAR_YELLOW 0xB4B4
#define STATBAR_ORANGE 0x64DC
#define STATBAR_DARKORANGE 0x28DC
#define STATBAR_RED 0xEB

u_int barColors[7] =
{
    STATBAR_BLUE,STATBAR_BLUEGREEN,
    STATBAR_YELLOW,STATBAR_YELLOW,
    STATBAR_ORANGE, STATBAR_DARKORANGE,
    STATBAR_RED
};

// 3 lengths for 3 bars
short barLen[NUM_STATS];

short barStat[NUM_STATS * NUM_CLASS] =
{
    // balanced
    40, 64, 72,
    // accel
    48, 80, 32,
    // speed
    80, 32, 10,
    // turn
    28, 48, 80,
};

