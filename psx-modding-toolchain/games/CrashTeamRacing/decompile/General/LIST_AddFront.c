#include <common.h>

void DECOMP_LIST_AddFront(struct LinkedList* L, struct Item* I)
{
  struct Item* oldFirst;

  // can't remove this check, or it'll crash
  // after beating Roo, spawning at key door
  if(I == 0) return 0;

  I->prev = 0;

  // link new item to the first on the list
  oldFirst = L->first;
  I->next = oldFirst;

  // if the list already has items
  if (oldFirst != 0)
  {
    // link current first to new item
    L->first->prev = I;
  }

  // if list is empty
  else
  {
    // first = last = new item
    L->last = I;
  }

  // new item is now the new first item
  L->first = I;

  L->count = L->count + 1;
}