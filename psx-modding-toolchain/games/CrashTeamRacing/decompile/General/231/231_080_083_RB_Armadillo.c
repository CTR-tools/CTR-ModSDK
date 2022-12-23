#include <common.h>

#if 0
// one seal can not collide with more than one other thread,
// then quits, it was like that in the original game too,
// but one seal likely-wont collide with two threads at the same time
void Armadillo_CheckColl(struct Instance* sealInst, struct Thread* sealTh)
{

}

void DECOMP_RB_Armadillo_ThTick_Rolling(struct Thread* t);	

void DECOMP_RB_Armadillo_ThTick_TurnAround(struct Thread* t)
{

}

void DECOMP_RB_Armadillo_ThTick_Rolling(struct Thread* t)
{

}
#endif

void RB_Armadillo_ThTick_Rolling();

void DECOMP_RB_Armadillo_LInB(struct Instance* inst)
{
	struct Armadillo* armObj;
	struct InstDef* instDef;
	short* cooldownArray;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Armadillo), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			RB_Armadillo_ThTick_Rolling,// behavior
			0,							// debug name
			0							// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	t->cooldownFrameCount = cooldownArray[inst->name[0xA] - '0'];
	
	cooldownArray = (short*)sdata->gGT->level1->ptrSpawnType1->pointers[1];
	
	// rolling animation
	inst->animIndex = 1;
	
	armObj = ((struct Armadillo*)t->object);
	armObj->timeRolling = 0;
	armObj->numFramesSpinning = 0;
	armObj->distFromSpawn = 0;
	armObj->direction = 0;
	armObj->timeAtEdge = 0;
	
	CTR_MatrixToRot(&armObj->rotCurr[0], &inst->matrix, 0x11);
	armObj->rotDesired[1] = (armObj->rotCurr[1] + 0x800) & 0xfff;
	
	armObj->spawnPosX = inst->matrix.t[0];
	armObj->spawnPosZ = inst->matrix.t[2];
	
	armObj->velX = inst->matrix.m[0][2] >> 7;
	armObj->velZ = inst->matrix.m[2][2] >> 7;
}