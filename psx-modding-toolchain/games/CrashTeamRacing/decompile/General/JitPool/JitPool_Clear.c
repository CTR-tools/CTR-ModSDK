#include <common.h>

void LIST_Clear(struct LinkedList* L);
void LIST_AddFront(struct LinkedList* L, struct Item* I);

void DECOMP_JitPool_Clear(struct JitPool* AP)
{
  int loopIndex;
  unsigned int currSlot;

  currSlot = (int)AP->ptrPoolData;

  // clear list of free and taken
  LIST_Clear(&AP->free);
  LIST_Clear(&AP->taken);

  for(loopIndex = 0; loopIndex < AP->maxItems; loopIndex++)
  {
	  // add all pool items to the free list
      LIST_AddFront(&AP->free,(struct Item*)currSlot);

	  // same as & 0xfffffffc, but more optimal,
	  // this is aligning down, not up
      currSlot += ((AP->itemSize)>>2)<<2;
  }
}