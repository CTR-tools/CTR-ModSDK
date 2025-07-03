#include <common.h>

// Required to make door open
// when driver hits potion, or 
// potion shatters due to full MinePool
int RB_Potion_OnShatter_TeethCallback(int unk, struct BSP* bspHitbox)
{
	struct InstDef* instDef;
	struct Instance* teethInst;

	instDef = bspHitbox->data.hitbox.instDef;
	if (instDef != NULL)
		if (teethInst = instDef->ptrInstance, teethInst != NULL)
			if (instDef->modelID == STATIC_TEETH) //tiger temple door
				instDef = DECOMP_RB_Teeth_OpenDoor(teethInst);

	return (int)instDef;
}