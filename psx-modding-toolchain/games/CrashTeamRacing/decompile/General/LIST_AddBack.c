#include <common.h>

void DECOMP_LIST_AddBack(struct LinkedList* L, struct Item* I)
{
  struct Item* oldLast;

  // can't remove this check, or it'll crash
  // after beating Roo, spawning at key door
  if(I == 0) return 0;

  I->next = 0;

  // link new item to the last on the list
  oldLast = L->last;
  I->prev = oldLast;

  // if the list already has items
  if (oldLast != 0)
  {
    // link current last to new item
    L->last->next = I;
  }

  // if list is empty
  else
  {
    // last = first = new item
    L->first = I;
  }

  // new item is now the new first item
  L->last = I;

  L->count = L->count + 1;
}