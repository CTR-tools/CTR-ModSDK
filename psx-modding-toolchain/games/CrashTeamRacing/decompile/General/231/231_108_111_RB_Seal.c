#include <common.h>

#if 0
void RB_Seal_ThTick_TurnAround(struct Thread* t)
{
	
}

void RB_Seal_ThTick_Move(struct Thread* t)
{
	
}
#endif

void RB_Seal_ThTick_Move();

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
			
			RB_Seal_ThTick_Move,	// behavior
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
	
	// rotCurr
	instDef = inst->instDef;
	sealObj->rotCurr[0] = instDef->rot[0];
	sealObj->rotCurr[1] = instDef->rot[1];
	sealObj->rotCurr[2] = instDef->rot[2];
	
	// rotSpawn, also copies direction into padding
	*(int*)&sealObj->rotSpawn[0] = *(int*)&sealObj->rotCurr[0];
	*(int*)&sealObj->rotSpawn[2] = *(int*)&sealObj->rotCurr[2];
	
	ConvertRotToMatrix(&inst->matrix, &sealObj->rotSpawn[0]);
	
	// dont call RB_Default_LInB(inst),
	// we know seal is never over ice
}