#include <common.h>

void DECOMP_JitPool_Remove(struct JitPool* AP, struct Item* item)
{
  DECOMP_LIST_RemoveMember(&AP->taken,item);
  DECOMP_LIST_AddFront(&AP->free,item);
}