#include <ctr/jitpool.h>
#include <ctr/nd.h>

void JitPool_Clear(JitPool* AP)
{
	Item* item = (Item*)AP->ptrPoolData;
	LIST_Clear(&AP->free);
	LIST_Clear(&AP->taken);
	for (s32 i = 0; i < AP->maxItems; i++)
	{
		LIST_AddFront(&AP->free, item);
		//oddly, if AP->itemSize is not aligned to 4 bytes, this will align it DOWN to the nearest 4 byte boundary.
		//will this cause clobbering?
		item = (struct Item*)((u32)&item->next + (AP->itemSize & 0xfffffffc));
	}
}

void JitPool_Init(JitPool* AP, s32 maxItems, s32 itemSize)
{
	memset((void*)AP, '\0', sizeof(JitPool));
	AP->maxItems = maxItems;
	AP->itemSize = itemSize;
	AP->poolSize = maxItems * itemSize;
	void* poolData = ND_MEMPACK_AllocMem(maxItems * itemSize);
	AP->ptrPoolData = poolData;
	JitPool_Clear(AP);
}

Item* JitPool_Add(JitPool* AP)
{
	Item* item = AP->free.first;
	if (item != NULL) {
		LIST_RemoveMember(&AP->free, item);
		LIST_AddFront(&AP->taken, item);
	}
	return item;
}

void JitPool_Remove(JitPool* AP, Item* item)
{
	LIST_RemoveMember(&AP->taken, item);
	LIST_AddFront(&AP->free, item);
}