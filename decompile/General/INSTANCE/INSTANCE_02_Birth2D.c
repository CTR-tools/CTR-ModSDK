#include <common.h>

struct Instance* DECOMP_INSTANCE_Birth2D(
	struct Model* model, char* name, struct Thread* th)
{
	struct GameTracker* gGT = sdata->gGT;
		
	struct Instance* inst = DECOMP_INSTANCE_Birth3D(model, name, th);
			
	inst->flags |= 0x400;
		
	struct InstDrawPerPlayer* idpp = INST_GETIDPP(inst);
		
#ifndef REBUILD_PS1
	idpp[0].pushBuffer = &gGT->pushBuffer_UI;
#else
	idpp[0].pushBuffer = &gGT->pushBuffer[0];
#endif
		
	for(int i = 1; i < gGT->numPlyrCurrGame; i++)
	{
		idpp[i].pushBuffer = 0;
	}
		
	return inst;

	//attempt at 1-1 ghidra (but the above impl is probably correct)
	//struct GameTracker* gGT = sdata->gGT;
	//struct Instance* inst = (struct Instance*)DECOMP_JitPool_Add(gGT->JitPools.instance);
	//if (inst != NULL)
	//{
	//	DECOMP_INSTANCE_Birth(inst, model, name, th, 0x40f);
	//}
	//struct InstDrawPerPlayer* idpp = INST_GETIDPP(inst);
	//#ifndef REBUILD_PS1
	//idpp[0].pushBuffer = &gGT->pushBuffer_UI;
	//#else
	//idpp[0].pushBuffer = &gGT->pushBuffer[0];
	//#endif
	//for(int i = 1; i < gGT->numPlyrCurrGame; i++)
	//{
	//	idpp[i].pushBuffer = 0;
	//}
}