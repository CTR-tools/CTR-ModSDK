#include <common.h>

void DECOMP_DecalGlobal_Store(struct GameTracker* gGT, struct LevTexLookup* LTL)
{
	struct Icon* currIcon;
	struct IconGroup** currGroup;
	
	if(LTL == 0) return;
	
	for(
			// array of Icon
			currIcon = &LTL->firstIcon[0];
			currIcon < &LTL->firstIcon[LTL->numIcon]; 
			currIcon++
		)
	{
		// uint, in case of negatives
		if((u_int)currIcon->global_IconArray_Index < 0x88)
			gGT->ptrIcons[currIcon->global_IconArray_Index] = currIcon;
	}
	
	for(
			// array of POINTER to iconGroup
			currGroup = &LTL->firstIconGroupPtr[0]; 
			currGroup < &LTL->firstIconGroupPtr[LTL->numIconGroup];
			currGroup++
		)
	{	
		// use '[0]' to dereference pointer
		if((u_int)currGroup[0]->groupID < 0x11)
			gGT->iconGroup[currGroup[0]->groupID] = currGroup[0];
	}
}