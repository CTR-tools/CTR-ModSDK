#include "global.h"

// LOAD_AppendQueue
// param1 is always the Pointer to "cd position of bigfile"
// param2 is type, 1 for readfile, 2 for dram, 3 for vram
// param3 is the index of the subfile within BIGFILE
// param4 is ptrDestination. If null, destination is Mempack_AllocMem
// param5 is callbackFuncPtr
void FUN_80032d30(unsigned int bigfile,short type,int index,unsigned int ptrDest, unsigned int callback)
{
  int len;
  struct LoadQueueSlot* lqs;
  register struct sData* gp asm("gp");

  len = (int)gp->queueLength;
  lqs = &gp->queueSlots[len];

  // Normally 8, boosted to 9 for OnlineCTR
  if (len >= 9) return; 

  lqs->ptrBigfileCdPos = bigfile;
  lqs->flags = 0;
  lqs->type = type;
  lqs->subfileIndex = index;
  lqs->ptrDestination = ptrDest;
  lqs->size = 0;
  lqs->callback.funcPtr = callback;
  
  gp->queueLength = len+1;
  
  return;
}