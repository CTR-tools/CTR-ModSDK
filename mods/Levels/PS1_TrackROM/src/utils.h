#ifndef UTILS_H_TRACKROM
#define UTILS_H_TRACKROM

#define CUSTOM_LEVEL_ID 20

enum HotReloadSteps
{
    HOT_RELOAD_DONE = 0,
    HOT_RELOAD_START = 1,
    HOT_RELOAD_LOAD = 2,
    HOT_RELOAD_READY = 3,
    HOT_RELOAD_EXEC = 4,
};

static volatile int* g_triggerHotReload = (volatile int*) 0x8000C000;
static volatile int* g_triggerVRMReload = (volatile int*) 0x8000C004;
static const char* CUSTOM_VRAM_ADDR = (char*) 0x80200000;
static const int* CUSTOM_MAP_PTR_ADDR = (int *) 0x80300000;
static const char* CUSTOM_LEV_ADDR = (char*) 0x80300004;

void HotReload();
void HotReloadVRAM();

#endif