#include <common.h>

struct Instance* DECOMP_INSTANCE_Birth2D(
	struct Model* model, char* name, struct Thread* th)
{
	int i;
	struct GameTracker* gGT;
	
	struct Instance* inst = 
		DECOMP_INSTANCE_Birth3D(model, name, th);
		
	gGT = sdata->gGT;
		
	inst->flags |= 0x400;
	
	struct InstDrawPerPlayer* idpp =
		INST_GETIDPP(inst);
	
	idpp[0].tileView = &gGT->tileView_UI;
	
	for(i = 1; i < gGT->numPlyrCurrGame; i++)
	{
		idpp[i].tileView = 0;
	}
	
	return inst;
}