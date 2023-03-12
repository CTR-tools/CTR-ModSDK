#include <common.h>

void RB_Baron_ThTick(struct Thread* t)
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