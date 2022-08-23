#include <common.h>

struct Item* LIST_RemoveMember(struct LinkedList* L, struct Item* I);
void LIST_AddFront(struct LinkedList* L, struct Item* I);

void DECOMP_AllocPool_Remove(struct AllocPool* AP, struct Item* item)
{
  LIST_RemoveMember(&AP->taken,item);
  LIST_AddFront(&AP->free,item);
}