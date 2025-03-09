#include <common.h> 

void DECOMP_Smart_ExitCriticalSection(void)
{
  // Optimization, use Software-CriticalSection
  // that does not actually block callbacks,
  // just prevent use of audio during callbacks
  sdata->criticalSectionCount--;
}
