#pragma once

#include <ctr/macros.h>

typedef struct Item
{
	struct Item* next;
	struct Item* prev;
} Item;

typedef struct LinkedList
{
	Item* first;
	Item* last;
	s32 count;
} LinkedList;

void LIST_Clear(LinkedList* list);
void LIST_AddFront(LinkedList* list, Item* item);
void LIST_AddBack(LinkedList* list, Item* item);
void* LIST_GetNextItem(Item* item);
void* LIST_GetFirstItem(LinkedList* list);
Item* LIST_RemoveMember(LinkedList* list, Item* item);
Item* LIST_RemoveFront(LinkedList* list);
Item* LIST_RemoveBack(LinkedList* list);
void LIST_Init(LinkedList* list, Item* item, s32 itemSize, s32 numItems);

//not a real ND function, just a helper macro. The value of an "Item" is the memory right after the Item struct.
#define LIST_GetItem(itemPtr) ((void*)(((Item*)itemPtr) + 1))