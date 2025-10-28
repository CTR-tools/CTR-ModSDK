#include <common.h>

void DECOMP_DecalGlobal_Store(struct GameTracker* gGT, struct IconHeader* ICH)
{
	struct Icon* currIcon;
	struct IconGroup** currGroup;
	
	if(ICH == 0) return;
	
	for(
			// array of Icon
			currIcon = &ICH->firstIcon[0];
			currIcon < &ICH->firstIcon[ICH->numIcon]; 
			currIcon++
		)
	{
		// uint, in case of negatives
		if((u_int)currIcon->global_IconArray_Index < 0x88)
			gGT->ptrIcons[currIcon->global_IconArray_Index] = currIcon;
	}
	
	for(
			// array of POINTER to iconGroup
			currGroup = &ICH->firstIconGroupPtr[0]; 
			currGroup < &ICH->firstIconGroupPtr[ICH->numIconGroup];
			currGroup++
		)
	{	
		// use '[0]' to dereference pointer
		if((u_int)currGroup[0]->groupID < 0x11)
			gGT->iconGroup[currGroup[0]->groupID] = currGroup[0];
	}
}