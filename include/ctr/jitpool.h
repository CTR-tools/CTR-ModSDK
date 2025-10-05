#pragma once

#include <ctr/list.h>

typedef struct JitPool
{
	LinkedList free;
	LinkedList taken;

	s32 maxItems;
	u32 itemSize;
	s32 poolSize;
	void* ptrPoolData;
} JitPool;

void JitPool_Clear(JitPool* AP);
void JitPool_Init(JitPool* AP, s32 maxItems, s32 itemSize);
Item* JitPool_Add(JitPool* AP);
void JitPool_Remove(JitPool* AP, Item* item);