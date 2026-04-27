#include <common.h>

struct IconGroup* DECOMP_DecalGlobal_FindInLEV(struct Level* level, char* str)
{
	struct LevTexLookup* levTexLookup = level->levTexLookup;

	if (levTexLookup == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < levTexLookup->numIconGroup; i++)
	{
		struct IconGroup* iconGroupPtr = levTexLookup->firstIconGroupPtr[i];
		if (((*(int*)(iconGroupPtr->name + 0)) == (*(int*)(str + 0))) &&
			((*(int*)(iconGroupPtr->name + 4)) == (*(int*)(str + 4))) &&
			((*(int*)(iconGroupPtr->name + 8)) == (*(int*)(str + 8))) &&
			((*(int*)(iconGroupPtr->name + 12)) == (*(int*)(str + 12))))
		{
			return iconGroupPtr;
		}
	}
}
