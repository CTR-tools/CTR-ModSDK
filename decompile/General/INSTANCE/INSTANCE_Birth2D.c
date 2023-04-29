#include <common.h>

struct Instance* INSTANCE_Birth2D(
	struct Model* model, char* name, struct Thread* th)
{
	int i;
	struct GameTracker* gGT;
	
	struct Instance* inst = 
		INSTANCE_Birth3D(model, name, th);
		
	gGT = sdata->gGT;
		
	inst->flags |= 0x400;
	
	inst->idpp[0].tileView = &gGT->tileView_UI;
	
	for(i = 1; i < gGT->numPlyrCurrGame; i++)
	{
		inst->idpp[i].tileView = 0;
	}
	
	return inst;
}