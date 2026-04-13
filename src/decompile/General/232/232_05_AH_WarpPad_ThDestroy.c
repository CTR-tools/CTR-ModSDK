#include <common.h>

void DECOMP_AH_WarpPad_ThDestroy(struct Thread* t)
{
	int i;
	struct Instance** instArr;
	struct WarpPad* warppadObj;
	
	warppadObj = t->object;
	
	// array of instances in warppad object
	instArr = &warppadObj->inst[0];
	
	for(i = 0; i < WPIS_NUM_INSTANCES; i++)
	{
		if(instArr[i] != 0)
		{
			DECOMP_INSTANCE_Death(instArr[i]);
			instArr[i] = 0;
		}
	}	
}