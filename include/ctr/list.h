#pragma once

typedef struct Item
{
	struct Item* next;
	struct Item* prev;
} Item;

typedef struct LinkedList
{
	Item* first;
	Item* last;
	int count;
} LinkedList;

void LIST_Clear(LinkedList* list);
void LIST_AddFront(LinkedList* list, Item* item);
void LIST_AddBack(LinkedList* list, Item* item);
void* LIST_GetNextItem(Item* item);
void* LIST_GetFirstItem(LinkedList* list);
Item* LIST_RemoveMember(LinkedList* L, Item* I);
Item* LIST_RemoveFront(LinkedList* L);
Item* LIST_RemoveBack(LinkedList* L);
void LIST_Init(LinkedList* L, Item* item, int itemSize, int numItems);