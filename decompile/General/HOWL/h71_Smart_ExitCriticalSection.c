#include <common.h> 

void DECOMP_Smart_ExitCriticalSection(void)
{
  if (
		// if you're already in a critical section
		(sdata->criticalSectionCount != 0) &&

		// reduce the number of times you've tried to exit, by 1
		(sdata->criticalSectionCount += -1,

		// if you have no more active needs to be in a critical section
		sdata->criticalSectionCount == 0))
  {
	// Use the real PsyQ version
    ExitCriticalSection();
  }
  return;
}
