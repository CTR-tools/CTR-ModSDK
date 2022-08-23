#include <common.h>

void* DECOMP_LIST_GetNextItem(struct Item* I)
{
	return I->next;
}