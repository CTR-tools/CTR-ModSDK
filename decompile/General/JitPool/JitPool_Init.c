#include <common.h>

void DECOMP_JitPool_Init(struct JitPool* AP, 
	int maxItems, int itemSize, char* name)
{
  // dont call memset, overwrite the whole thing anyway
  // dont write AP->poolSize, waste of time
  // dont pass "name" to MEMPACK

  AP->maxItems = maxItems;
  AP->itemSize = itemSize;
  AP->ptrPoolData = MEMPACK_AllocMem(maxItems * itemSize);
  JitPool_Clear(AP);
  return;
}