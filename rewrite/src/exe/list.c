#include <ctr/list.h>

void LIST_Clear(LinkedList* list)
{
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
}

void LIST_AddFront(LinkedList* list, Item* item)
{
	if (item == NULL) { return; }

	item->prev = NULL;
	Item* oldFirst = list->first;
	item->next = oldFirst;

	if (oldFirst == NULL) { list->last = item; }
	else { list->first->prev = item; }

	list->first = item;
	list->count++;
}

void LIST_AddBack(LinkedList* list, Item* item)
{
	if (item == NULL) { return; }

	item->next = NULL;
	Item* oldLast = list->last;
	item->prev = oldLast;

	if (oldLast == NULL) { list->first = item; }
	else { list->last->next = item; }

	list->last = item;
	list->count++;
}

void* LIST_GetNextItem(Item* item)
{
	return item->next;
}

void* LIST_GetFirstItem(LinkedList* list)
{
	return list->first;
}

Item* LIST_RemoveMember(LinkedList* list, Item* item)
{
	if (item == NULL || list->first == NULL) { return item; }

	if (item->prev == NULL) { list->first = item->next; }
	else { item->prev->next = item->next; }

	if (item->next == NULL) { list->last = item->prev; }
	else { item->next->prev = item->prev; }

	list->count--;
	item->next = NULL;
	item->prev = NULL;
	return item;
}

Item* LIST_RemoveFront(LinkedList* list)
{
	Item* removedItem = list->first;
	if (removedItem == NULL) { return removedItem; }

	if (removedItem->prev == NULL) { list->first = removedItem->next; }
	else { removedItem->prev->next = removedItem->next; }

	if (removedItem->next == NULL) { list->last = removedItem->prev; }
	else { removedItem->next->prev = removedItem->prev; }

	list->count--;
	removedItem->next = NULL;
	removedItem->prev = NULL;
	return removedItem;
}

Item* LIST_RemoveBack(LinkedList* list)
{
	//for some reason, LIST_RemoveBack and LIST_RemoveFront aren't mirrors of each other.
	Item* removedItem = list->last;
	if (removedItem == NULL) { return removedItem; }

	if (list->first != NULL)
	{
		if (removedItem->prev == NULL) { list->first = removedItem->next; }
		else { removedItem->prev->next = removedItem->next; }

		if (removedItem->next == NULL) { list->last = removedItem->prev; }
		else { removedItem->next->prev = removedItem->prev; }
		list->count--;
	}

	removedItem->next = NULL;
	removedItem->prev = NULL;
	return removedItem;
}

void LIST_Init(LinkedList* list, Item* item, s32 itemSize, s32 numItems)
{
	for(; numItems > 0; numItems--)
	{
		LIST_AddBack(list, item);

		item = (Item*)((s32)item + itemSize);
	}
}