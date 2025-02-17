#ifdef USE_ONLINE
#include "OnlineCTR/lap.c"
#endif

// Online and Profiler should
// never happen at the same time
#ifdef USE_PROFILER
#include "Debug/Debug1.c"
#endif