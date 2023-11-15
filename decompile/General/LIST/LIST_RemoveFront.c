#include <common.h>

struct Item* DECOMP_LIST_RemoveFront(struct LinkedList* L)
{
  return DECOMP_LIST_RemoveMember(L, L->first);
}

// ~0x80 bytes of free room here