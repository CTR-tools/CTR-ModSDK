#include <common.h>

void DECOMP_INSTANCE_Birth(
	struct Instance* inst, struct Model* model, char* name,
	struct Thread* th, int flags)
{
	int i;
	struct GameTracker* gGT;
	
	gGT = sdata->gGT;
	
	// copy name
	for(i = 0; i < 16; i++)
	{
		inst->name[i] = name[i];
	}
	
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
	
	for(i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		inst->idpp[i].tileView = &gGT->tileView[i];
		inst->idpp[i].mh = 0;
		inst->idpp[i].unkb8[0] = 0;
	}
}