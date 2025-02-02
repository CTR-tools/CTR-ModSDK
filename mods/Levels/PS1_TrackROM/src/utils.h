#ifndef UTILS_H_TRACKROM
#define UTILS_H_TRACKROM

#include <common.h>

#define CUSTOM_LEVEL_ID 0

enum HotReloadSteps
{
    HOT_RELOAD_DONE = 0,
    HOT_RELOAD_START = 1,
    HOT_RELOAD_LOAD = 2,
    HOT_RELOAD_READY = 3,
    HOT_RELOAD_EXEC = 4,
};

#define TRIGGER_HOT_RELOAD (volatile int*) 0x8000C000
#define TRIGGER_VRM_RELOAD (volatile int*) 0x8000C004
#define GHOST_READY (volatile int*) 0x8000C008
#define CHAR_MODEL_PTRS (struct Model**) 0x8000C010

#define CUSTOM_VRAM_ADDR (char*) 0x80200000
#define GHOST_SIZE_ADDR (int*) 0x80280000
#define DRIVER_ADDR (char*) 0x80290000
#define GHOST_ADDR (char*) 0x80280004
#define CUSTOM_MAP_PTR_ADDR (int*) 0x80300000
#define CUSTOM_LEV_ADDR (char*) 0x80300004

void HotReload();
void HotReloadVRAM();

#endif