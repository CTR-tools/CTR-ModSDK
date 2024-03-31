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
	
#ifndef REBUILD_PS1
	idpp[0].pushBuffer = &gGT->pushBuffer_UI;
#else
	idpp[0].pushBuffer = &gGT->pushBuffer[0];
#endif
	
	for(i = 1; i < gGT->numPlyrCurrGame; i++)
	{
		idpp[i].pushBuffer = 0;
	}
	
	return inst;
}