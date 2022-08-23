#include <common.h>

void LIST_AddBack(struct LinkedList* L, struct Item* I);

void DECOMP_LIST_Init(struct LinkedList* L, struct Item* item, int itemSize, int numItems)
{
  while(numItems > 0)
  {
      // add to freeItems
      LIST_AddBack(L,item);

	  numItems--;

	  // increment pointer to next member
	  item = (struct Item*)((int)item + itemSize);
  }
}