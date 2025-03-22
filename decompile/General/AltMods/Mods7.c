#ifdef USE_ONLINE
#include "OnlineCTR/global.h"
unsigned int checkpointTimes[(MAX_LAPS * CPS_PER_LAP) + 1];
#endif

#ifdef USE_BOOSTBAR
#include "BoostBar/mods7.c"
#endif

#ifdef USE_60FPS
#include "60fps/mods7.c"
#endif
