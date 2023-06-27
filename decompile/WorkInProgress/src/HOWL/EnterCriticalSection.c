#include <common.h> 

void DECOMP_Smart_EnterCriticalSection(void)
{
  char alreadyEntered;
  int iVar2;
  // Add 1 to the number of times you've
  // tried to enter a critical section
  iVar2 = sdata->criticalSectionCount + 1;

  // Check if you're already in a critical section
  alreadyEntered = (sdata->criticalSectionCount == 0);

  // Set the number of times you've
  // tried to enter a critical section
  sdata->criticalSectionCount = iVar2;

  // if you are not already in critical section
  if (alreadyEntered)
  {
	// enter the critical section
    Smart_EnterCriticalSection();
  }
  return;
}