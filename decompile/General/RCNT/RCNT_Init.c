#include <common.h>

void DECOMP_RCNT_Init()
{
#ifndef REBUILD_PC
  EnterCriticalSection();
  StopRCnt(DescRC+1);
  SetRCnt(DescRC+1,0xffff,0x2000);
  StartRCnt(DescRC+1);
  ExitCriticalSection();
#endif
}