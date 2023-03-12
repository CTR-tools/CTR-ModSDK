#include <common.h>

#if 0
void DECOMP_RB_Baron_ThTick(struct Thread* t)
{
	struct Instance* baronInst;
	struct Baron* baronObj;
	struct Level* level;
	struct GameTracker* gGT;
	
	baronInst = t->inst;
	baronObj = (struct Baron*)t->object;
	gGT = sdata->gGT;
	level = gGT->level1
	
// Unused, this was for the Baron (Crash 3 airplane)
// that would be on Hot Air Skyway. Sewer Speedway
// barrel has zero animation frames, so it's removed
#if 0
	// if animation is not over
	if(
		(baronInst->animFrame+1) < 
		INSTANCE_GetNumAnimFrames(baronInst, 0)
	)
	{
		// increment frame
		baronInst->animFrame = baronInst->animFrame+1;
	}
	
	// if animation is done
	else
	{
		// reset animation
		baronInst->animFrame = 0;
	}
#endif

	if(level1->numSpawnType2_PosRot == 0) return;

	
}
#endif

void RB_Baron_ThTick();

void DECOMP_RB_Baron_LInB(struct Instance* inst)
{
	struct Baron* baronObj;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Baron), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			RB_Baron_ThTick,	// behavior
			0,						// debug name
			0						// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	inst->scale[0] = 0x1000;
	inst->scale[1] = 0x1000;
	inst->scale[2] = 0x1000;
	
	#if 0
	// Removed, Baron Plane would spawn two
	// planes, one starts at pointIndex=1,
	// the other one at pointIndex=NumPoints/2
	#endif
	
	baronObj = ((struct Baron*)t->object);
	baronObj->otherInst = 0;
	baronObj->pointIndex = 1;
	baronObj->soundID_flags = 0;
}