#include <common.h>

void DECOMP_LIST_Clear(struct LinkedList* L)
{
	L->first = 0;
	L->last = 0;
	L->count = 0;
}