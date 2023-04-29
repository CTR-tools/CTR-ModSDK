#include <common.h>

struct Item* DECOMP_LIST_RemoveMember(struct LinkedList* L, struct Item* I)
{
  // probably waste of time, but leave it for now
  if(L->first == 0) return 0;

  // can't remove this check, or it'll crash
  // in 232, bottom of Door_ThTick, erasing keys
  if(I == 0) return 0;

  // if this is not the first item
  if (I->prev != 0)
  {
    I->prev->next = I->next;
  }

  else
  {
    L->first = I->next;
  }

  // if this is not the last item
  if (I->next != 0)
  {
    I->next->prev = I->prev;
  }

  else
  {
	L->last = I->prev;
  }

  // decrease item count
  L->count = L->count - 1;

  // erase links
  I->next = 0;
  I->prev = 0;

  return I;
}