#include <common.h>

struct Item* DECOMP_LIST_RemoveBack(struct LinkedList* L)
{
  return DECOMP_LIST_RemoveMember(L, L->last);
}

// ~0x80 bytes of free room here
