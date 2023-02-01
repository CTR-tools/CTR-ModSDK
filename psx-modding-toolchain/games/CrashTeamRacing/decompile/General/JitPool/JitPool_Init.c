#include <common.h>

void DECOMP_JitPool_Init(struct JitPool* AP,int maxItems,int itemSize,char* name)
{
  // dont call memset, we overwrite the whole thing anyway

  AP->maxItems = maxItems;
  AP->itemSize = itemSize;

  // dont write AP->poolSize, waste of time

  // all items in a pool, dont give "name" as parameter, waste of time
  AP->ptrPoolData = MEMPACK_AllocMem(maxItems * itemSize, name);

  JitPool_Clear(AP);

  return;
}