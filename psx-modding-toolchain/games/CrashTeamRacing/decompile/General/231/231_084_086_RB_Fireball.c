#include <common.h>

void Seal_CheckColl(struct Instance* sealInst, struct Thread* sealTh, int radius);

void DECOMP_RB_Fireball_ThTick(struct Thread* t)
{
	struct Instance* fireInst;
	struct Fireball* fireObj;
	int velY;

	struct GameTracker* gGT;
	int elapsedTimeMS;
	
	gGT = sdata->gGT;
	elapsedTimeMS = gGT->elapsedTimeMS;
	
	fireInst = t->inst;
	fireObj = t->object;
	
	// if fireball isn't below the lava
	if(fireInst->matrix.t[1] >= (fireInst->instDef->pos[1] - 0x440))
	{
		// move based on velocity
		velY = fireObj->velY;
		fireInst->matrix.t[1] += velY * (elapsedTimeMS>>5);
		
		// reduce velocity (gravity)
		fireObj->velY = velY - ((elapsedTimeMS * 10) >> 5)
		
		// terminal velocity
		if(velY < -200)
		{
			velY = -200;
		}
		
		// [particle]
		
		Seal_CheckColl(fireInst, t, 0x10000);
	}
	
	// [other generic stuff]
}