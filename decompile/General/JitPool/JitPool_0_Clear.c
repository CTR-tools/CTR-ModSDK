#include <common.h>

void DECOMP_JitPool_Clear(struct JitPool* AP)
{
  int loopIndex;
  unsigned int currSlot;

  currSlot = (int)AP->ptrPoolData;

  // clear list of free and taken
  DECOMP_LIST_Clear(&AP->free);
  DECOMP_LIST_Clear(&AP->taken);

  for(loopIndex = 0; loopIndex < AP->maxItems; loopIndex++)
  {
	  // add all pool items to the free list
      DECOMP_LIST_AddFront(&AP->free,(struct Item*)currSlot);

	  // same as & 0xfffffffc, but more optimal,
	  // this is aligning down, not up
      currSlot += ((AP->itemSize)>>2)<<2;
  }
}