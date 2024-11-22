#include <common.h>

void DECOMP_RB_Default_LInB(struct Instance* inst)
{
	// low ram budget, can't use a regular pointer
	register char* scratch asm("$at");
	scratch = (char*)0x1f800000;
	
	int var;
	
	// high-LOD coll (8 triangles)
	*(short*)&scratch[0x13a] = 2;
	
	*(int*)&scratch[0x13C] = 0x3000;
	*(int*)&scratch[0x140] = 0;
	*(int*)&scratch[0x144] = (int)sdata->gGT->level1->ptr_mesh_info;
	
	// Make a hitbox
	var = inst->matrix.t[0];
	*(short*)&scratch[0x108] = var;
	*(short*)&scratch[0x110] = var;
	var = inst->matrix.t[2];
	*(short*)&scratch[0x10c] = var;
	*(short*)&scratch[0x114] = var;
	var = inst->matrix.t[1];
	*(short*)&scratch[0x10a] = var - 0x180;
	*(short*)&scratch[0x112] = var + 0x80;
	
	COLL_SearchTree_FindQuadblock_Touching(
		(u_int*)&scratch[0x108], (u_int*)&scratch[0x110], (u_int*)&scratch[0x118], 0);
		
	RB_MakeInstanceReflective((struct ScratchpadStruct*)&scratch[0x118], inst);
}