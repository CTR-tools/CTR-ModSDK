#include <common.h>

void DECOMP_RCNT_Destroy()
{
  EnterCriticalSection();
  StopRCnt(DescRC+1);
  ExitCriticalSection();
}