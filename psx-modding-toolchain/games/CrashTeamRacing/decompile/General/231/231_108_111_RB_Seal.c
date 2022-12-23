#include <common.h>

// one seal can not collide with more than one other thread,
// then quits, it was like that in the original game too,
// but one seal likely-wont collide with two threads at the same time
void Seal_CheckColl(struct Instance* sealInst, struct Thread* sealTh)
{
	struct GameTracker* gGT;
	struct Instance* hitInst;
	struct Driver* hitDriver;
	int boolHurt;
	char kartStatePrev;
	
	gGT = sdata->gGT;
	
	// check players
	hitInst = 
		(struct Instance*)INSTANCE_CollBucket_Radius(
			sealInst, sealTh, 
			gGT->threadBuckets[PLAYER].thread,
			0x4000);
	
	// if hit a player
	if(hitInst != 0)
	{
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		
		// backup
		kartStatePrev = hitDriver->kartState;
		
		// attempt to harm driver (spin out)
		boolHurt = RB_Hazard_HurtDriver(hitDriver,1,0,0);
		
		// if failed, due to mask grab or mask weapon
		if (boolHurt == 0) return;
		
		// if driver was already spinning out
		if (kartStatePrev == 3) return;
		
		// play seal sound, with echo if driver is on an echo quadblock
		OtherFX_Play_Echo(0x78,1,hitDriver->actionsFlagSet & 0x00010000);
	
		// dont check other buckets
		return;
	}
	
	// check robots
	hitInst = 
		(struct Instance*)INSTANCE_CollBucket_Radius(
			sealInst, sealTh, 
			gGT->threadBuckets[ROBOT].thread,
			0x4000);
			
	// if hit a robot
	if(hitInst != 0)
	{
		// get driver from instance
		hitDriver = (struct Driver*)hitInst->thread->object;
		
		// attempt to harm driver (spin out)
		RB_Hazard_HurtDriver(hitDriver,1,0,0);
		
		// dont check other buckets
		return;
	}
	
	// check mines
	hitInst = 
		(struct Instance*)INSTANCE_CollBucket_Radius(
			sealInst, sealTh, 
			gGT->threadBuckets[MINE].thread,
			0x4000);
			
	// if hit a mine
	if(hitInst != 0)
	{
		// all mine ThCollide functions only take one parameter,
		// all other ThCollide functions are erased due to redundancy
		hitInst->thread->funcThCollide(hitInst->thread);
		
		// dont check other bucket
		return;
	}
}

void DECOMP_RB_Seal_ThTick_Move(struct Thread* t);	

void DECOMP_RB_Seal_ThTick_TurnAround(struct Thread* t)
{
	struct Instance* sealInst;
	struct Seal* sealObj;
	
	sealInst = t->inst;
	sealObj = (struct Seal*)t->object;
	
	// if animation is not over
	if(
		(sealInst->animFrame+2) < 
		INSTANCE_GetNumAnimFrames(sealInst, 0)
	)
	{
		// increment frame
		sealInst->animFrame = sealInst->animFrame+2;
	}
	
	// if animation is done
	else
	{
		// reset animation
		sealInst->animFrame = 0;
		
		// only play sound in TurnAround
		PlaySound3D(0x77, sealInst);
	}
	
	// if rotation is finished
	if(sealObj->rotCurr[1] == sealObj->rotDesired[1])
	{
		sealObj->numFramesSpinning = 0;
		
		#if 0
		// overwrite spawn (why?)
		sealObj->rotSpawn[0] = sealObj->rotDesired[0];
		sealObj->rotSpawn[1] = sealObj->rotDesired[1];
		sealObj->rotSpawn[2] = sealObj->rotDesired[2];
		#endif
		
		ConvertRotToMatrix(&sealInst->matrix, &sealObj->rotCurr[0]);
	
		SetThTick_AndExec(t, DECOMP_RB_Seal_ThTick_Move);
	}
	
	else
	{	
		// interpolate rotCurrY to rotDesiredY
		sealObj->rotCurr[1] = 
			RB_Hazard_InterpolateValue(
				sealObj->rotCurr[1], sealObj->rotDesired[1], 0x80
			);
			
		// are these next two needed?
			
		#if 0
			
		// interpolate rotCurrX to rotSpawnX
		sealObj->rotCurr[0] = 
			RB_Hazard_InterpolateValue(
				sealObj->rotCurr[0], sealObj->rotSpawn[0], 0x14
			);
		
		// interpolate rotCurrX to rotSpawnX
		sealObj->rotCurr[2] = 
			RB_Hazard_InterpolateValue(
				sealObj->rotCurr[2], sealObj->rotSpawn[2], 0x14
			);
			
		#endif
			
		sealObj->numFramesSpinning++;
		
		ConvertRotToMatrix(&sealInst->matrix, &sealObj->rotCurr[0]);
	}
	
	Seal_CheckColl(sealInst, t);
}

void DECOMP_RB_Seal_ThTick_Move(struct Thread* t)
{
	struct Instance* sealInst;
	struct Seal* sealObj;
	int i;
	
	sealInst = t->inst;
	sealObj = (struct Seal*)t->object;
	
	// if animation is not over
	if(
		(sealInst->animFrame+2) < 
		INSTANCE_GetNumAnimFrames(sealInst, 0)
	)
	{
		// increment frame
		sealInst->animFrame = sealInst->animFrame+2;
	}
	
	// if animation is done
	else
	{
		// reset animation
		sealInst->animFrame = 0;
		
		// no sound here
	}
	
	// move seal
	for(i = 0; i < 3; i++)
	{
		// ">>5" is the same as "/0x2d"
		// 0x2d is the frame count
		
		sealInst->matrix.t[i] = 
			sealObj->spawnPos[i] - 
				((sealObj->distFromSpawn * sealObj->vel[i]) >> 5);
	}
	
	// moving towards spawn (0)
	if(sealObj->direction == 0)
	{
		// until == 0
		sealObj->distFromSpawn--;
	}
	
	// moving away from spawn (1)
	else
	{
		// until == 0x2d
		sealObj->distFromSpawn++;
	}
	
	if(sealObj->distFromSpawn != sealObj->direction*0x2d)
	{
		Seal_CheckColl(sealInst, t);
		
		return;
	}
	
	// === end of Move state ===
	
	// negate
	sealObj->direction = !sealObj->direction;
	
	// flip
	sealObj->rotDesired[1] = (sealObj->rotDesired[1] + 0x800) & 0xfff;
	
	// turn around
	SetThTick_AndExec(t, DECOMP_RB_Seal_ThTick_TurnAround);
}

void DECOMP_RB_Seal_LInB(struct Instance* inst)
{
	struct Seal* sealObj;
	struct SpawnType2* spawnType2;
	struct InstDef* instDef;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Seal), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Seal_ThTick_Move,	// behavior
			0,							// debug name
			0							// thread relative
		);
	
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	inst->scale[0] = 0x2000;
	inst->scale[1] = 0x2000;
	inst->scale[2] = 0x2000;
	
	sealObj = ((struct Seal*)t->object);
	sealObj->distFromSpawn = 0;
	sealObj->direction = 1;
	sealObj->sealID = inst->name[5] - '0';
	
	spawnType2 = &sdata->gGT->level1->ptrSpawnType2[sealObj->sealID];
	
	// spawnPos
	*(int*)&sealObj->spawnPos[0] = *(int*)&spawnType2->posCoords[0];
	sealObj->spawnPos[2] = spawnType2->posCoords[2];
	
	// endPos
	sealObj->endPos[0] = spawnType2->posCoords[3];
	sealObj->endPos[1] = spawnType2->posCoords[4];
	sealObj->endPos[2] = spawnType2->posCoords[5];
	
	// distance between points
	sealObj->vel[0] = sealObj->spawnPos[0] - sealObj->endPos[0];
	sealObj->vel[1] = sealObj->spawnPos[1] - sealObj->endPos[1];
	sealObj->vel[2] = sealObj->spawnPos[2] - sealObj->endPos[2];
	
	// rotSpawn
	instDef = inst->instDef;
	sealObj->rotSpawn[0] = instDef->rot[0];
	sealObj->rotSpawn[1] = instDef->rot[1];
	sealObj->rotSpawn[2] = instDef->rot[2];
	
	// rotCurr, also copies direction into padding
	*(int*)&sealObj->rotCurr[0] = *(int*)&sealObj->rotSpawn[0];
	*(int*)&sealObj->rotCurr[2] = *(int*)&sealObj->rotSpawn[2];
	
	ConvertRotToMatrix(&inst->matrix, &sealObj->rotCurr[0]);
	
	// dont call RB_Default_LInB(inst),
	// we know seal is never over ice
}