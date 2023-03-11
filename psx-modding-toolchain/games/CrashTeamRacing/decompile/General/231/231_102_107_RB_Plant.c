#include <common.h>

// budget: 2584

enum PlantAnim
{
	PlantAnim_Rest,
	PlantAnim_TransitionRestHungry,
	PlantAnim_Hungry,
	PlantAnim_Grab,
	PlantAnim_Chew
};

void DECOMP_RB_Plant_ThTick_Hungry(struct Thread* t)
{
	
}

void DECOMP_RB_Plant_ThTick_Rest(struct Thread* t)
{
	struct Instance* plantInst;
	struct Plant* plantObj;
	
	plantInst = t->inst;
	plantObj = (struct Plant*)t->object;	
	
	if(plantInst->animIndex == PlantAnim_Rest)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			INSTANCE_GetNumAnimFrames(plantInst, 0)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
		}
		
		// if animation is done
		else
		{
			// reset animation
			plantInst->animFrame = 0;
			
			// After 3 cycles, transition to hungry
			plantObj->cycleCount++;
			if(plantObj->cycleCount == 3)
			{
				plantObj->cycleCount = 0;
				plantInst->animIndex = PlantAnim_TransitionRestHungry;
			}
		}
	}
	
	else if(plantInst->animIndex == PlantAnim_TransitionRestHungry)
	{
		// if animation is not over
		if(
			(plantInst->animFrame+1) < 
			INSTANCE_GetNumAnimFrames(plantInst, 1)
		)
		{
			// increment frame
			plantInst->animFrame = plantInst->animFrame+1;
		}
		
		// animation is done
		else
		{
			#if 0
			plantInst->animFrame = 0;
			plantInst->animIndex = PlantAnim_Hungry;	
			ThTick_SetAndExec(t, DECOMP_RB_Plant_ThTick_Hungry);
			#else
			plantInst->animFrame = 0;
			plantInst->animIndex = PlantAnim_Rest;
			#endif
		}
	}
}

void DECOMP_RB_Plant_LInB(struct Instance* inst)
{
	struct Plant* plantObj;
	struct SpawnType1* ptrSpawnType1;
	short* metaArray;
	int plantID;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Plant), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Plant_ThTick_Rest,	// behavior
			0,								// debug name
			0								// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	inst->scale[0] = 0x2800;
	inst->scale[1] = 0x2800;
	inst->scale[2] = 0x2800;
	inst->animFrame = 0;
	inst->animIndex = PlantAnim_Rest;
	
	plantObj = ((struct Plant*)t->object);
	plantObj->cycleCount = 0;
	plantObj->boolEating = 0;
	
	ptrSpawnType1 = sdata->gGT->level1->ptrSpawnType1;
	if(ptrSpawnType1->count > 0)
	{
		// puts plants on separate cycles
		metaArray = (short*)ptrSpawnType1->pointers[1];
		
		plantID = inst->name[6] - '0';
		t->cooldownFrameCount = metaArray[plantID*2+0];
		plantObj->LeftOrRight = metaArray[plantID*2+1];
	}
	
#if 0
      DAT_800b8bf0._2_2_ = 0x40;
      DAT_800b8bec._0_2_ = 0xffc0;
      DAT_800b8bec._2_2_ = 0xffc0;
      DAT_800b8bf4._0_2_ = 0x80;
      DAT_800b8bf4._2_2_ = 0x1e0;
      DAT_800b8bf0._0_2_ = 0;
#endif

}