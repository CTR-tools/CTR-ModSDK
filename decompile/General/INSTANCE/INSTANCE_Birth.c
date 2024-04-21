#include <common.h>

void DECOMP_INSTANCE_Birth(
	struct Instance* inst, struct Model* model, char* name,
	struct Thread* th, int flags)
{
	int i;
	struct GameTracker* gGT;
	
	gGT = sdata->gGT;
	
#ifndef REBUILD_PS1
	// copy name
	for(i = 0; i < 16; i++)
	{
		inst->name[i] = name[i];
	}
#endif
	
	inst->unk50 = 0xfe;
	inst->unk51 = 0xc;
	inst->animIndex = 0;
	inst->unk53 = 1;
	
	inst->model = model;
	
	inst->scale[0] = 0x1000;
	inst->scale[1] = 0x1000;
	inst->scale[2] = 0x1000;
	
	inst->alphaScale = 0;
	inst->colorRGBA = 0;
	inst->flags = flags;
	inst->instDef = 0;
	
	inst->animFrame = 0;
	inst->vertSplit = 0;
	inst->reflectionRGBA = 0x7f7f7f;
	
	inst->thread = th;
	inst->bitCompressed_NormalVector_AndDriverIndex = 0;
	
	struct InstDrawPerPlayer* idpp = INST_GETIDPP(inst);
	
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		idpp[i].pushBuffer = &gGT->pushBuffer[i];
		idpp[i].mh = 0;
		idpp[i].instFlags = 0;
	}
}