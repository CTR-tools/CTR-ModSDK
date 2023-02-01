#include <common.h>

struct Item* LIST_RemoveMember(struct LinkedList* L, struct Item* I);
void LIST_AddFront(struct LinkedList* L, struct Item* I);

int DECOMP_JitPool_Add(struct JitPool* AP)
{
  struct Item* item;
  item = AP->free.first;

  if(item != 0)
  {
	LIST_RemoveMember(&AP->free,item);
	LIST_AddFront(&AP->taken,item);
  }

  return (int)item;
}