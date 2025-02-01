#include <common.h>
#include "utils.h"

uint8_t MEMCARD_Save_Hook(int slotIdx, char *name, char *param_3, char *ptrData, int fileSize, unsigned int param6)
{
    *GHOST_SIZE_ADDR = fileSize;
    memcpy(GHOST_ADDR, ptrData, fileSize);
    *g_ghostReady = 1;
    return 0;
}