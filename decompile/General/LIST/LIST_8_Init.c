#include <common.h>

void DECOMP_LIST_Init(struct LinkedList* L, struct Item* item, int itemSize, int numItems)
{
  while(numItems > 0)
  {
      // add to freeItems
      DECOMP_LIST_AddBack(L,item);

	  numItems--;

	  // increment pointer to next member
	  item = (struct Item*)((int)item + itemSize);
  }
}