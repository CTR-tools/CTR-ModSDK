#include <common.h>

// Required to make door open
// when driver hits potion, or 
// potion shatters due to full MinePool
int RB_Potion_OnShatter_TeethCallback(int unk, struct BSP* bspHitbox)
{
	struct InstDef* instDef;
	struct Instance* teethInst;

	instDef = bspHitbox->data.hitbox.instDef;
	if(instDef == 0) return;
	
	teethInst = instDef->ptrInstance;
	if(teethInst == 0) return;
	
	if (CheckModelID(instDef->modelID, STATIC_TEETH) == false) return;

	RB_Teeth_OpenDoor(teethInst);
}