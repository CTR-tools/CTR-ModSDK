#include <common.h>

#if 0
void DECOMP_RB_Snowball_ThTick(struct Thread* t)
{
	
}
#endif

void RB_Snowball_ThTick();

void DECOMP_RB_Snowball_LInB(struct Instance* inst)
{
	struct Snowball* ballObj;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Snowball), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			RB_Snowball_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	ballObj = ((struct Snowball*)t->object);
	
	// snowball and barrel
	if(inst->name[0] == 's')	ballObj->snowball_ID = 0;
	else /*barrel*/				ballObj->snowball_ID = inst->name[7] - '0';
	
	ballObj->numPoints = 
		sdata->gGT->level1->ptrSpawnType2_again
			[ballObj->snowball_ID].numCoords-1;
	
	// must set, it wont default
	inst->scale[0] = 0x1000;
	inst->scale[1] = 0x1000;
	inst->scale[2] = 0x1000;
}