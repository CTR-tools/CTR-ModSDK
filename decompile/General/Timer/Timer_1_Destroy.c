#include <common.h>

void DECOMP_Timer_Destroy()
{
  EnterCriticalSection();
  StopRCnt(DescRC+1);
  ExitCriticalSection();
}