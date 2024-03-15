#include <common.h>

void DECOMP_VehTalkMask_PlayXA(struct INSTANCE* i, int id)
{
	struct Driver* d = sdata->gGT->drivers[0];
	
	if(d != 0)
	{
		int boolGoodGuy = 
			DECOMP_VehPickupItem_MaskBoolGoodGuy(d);
	
		if(boolGoodGuy == 0)
			id += 0x1f;
	}
	
	DECOMP_CDSYS_XAPlay(CDSYS_XA_TYPE_EXTRA, id);
}