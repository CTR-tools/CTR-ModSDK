#include <common.h>

void Seal_CheckColl(struct Instance* sealInst, struct Thread* sealTh, int radius);

void DECOMP_RB_Armadillo_ThTick_Rolling(struct Thread* t);	

void RB_Armadillo_ThTick_Flip(struct Thread* t)
{
	struct Instance* armInst;
	struct Armadillo* armObj;
	int i;
	
	armInst = t->inst;
	armObj = (struct Armadillo*)t->object;
	
	// if animation is not over
	if(
		(armInst->animFrame+1) < 
		INSTANCE_GetNumAnimFrames(armInst, 0)
	)
	{
		// increment frame
		armInst->animFrame = armInst->animFrame+1;
		
		Seal_CheckColl(armInst,t,0x2400);
		return;
	}
	
	// === End of Flip ===
	
	armObj->velX = -armObj->velX;
	armObj->velZ = -armObj->velZ;

	// rolling animation
	armInst->animFrame = 0;
	armInst->animIndex = 1;

	SetThTick_AndExec(t, DECOMP_RB_Armadillo_ThTick_Rolling);
}

void DECOMP_RB_Armadillo_ThTick_TurnAround(struct Thread* t)
{
	struct Instance* armInst;
	struct Armadillo* armObj;
	int i;
	
	armInst = t->inst;
	armObj = (struct Armadillo*)t->object;
	
	// spin rotCurrY 180 degrees (turn around)
	armObj->rotCurr[1] = 
		RB_Hazard_InterpolateValue(
			armObj->rotCurr[1], armObj->rotDesired[1], 0x100
		);
		
	// increment frame
	armInst->animFrame = armInst->animFrame+1;
		
	ConvertRotToMatrix(&armInst->matrix, &armObj->rotCurr[0]);
	
	if(armObj->rotCurr[1] != armObj->rotDesired[1])
	{
		Seal_CheckColl(armInst,t,0x2400);
		return;
	}
	
	// === End of TurnAround ===
	
	SetThTick_AndExec(t, RB_Armadillo_ThTick_Flip);
}

void DECOMP_RB_Armadillo_ThTick_Rolling(struct Thread* t)
{
	struct Instance* armInst;
	struct Armadillo* armObj;
	int i;
	
	armInst = t->inst;
	armObj = (struct Armadillo*)t->object;
	
	// if animation is not over
	if(
		(armInst->animFrame+1) < 
		INSTANCE_GetNumAnimFrames(armInst, 1)
	)
	{
		// increment frame
		armInst->animFrame = armInst->animFrame+1;
	}
	
	// if animation is done
	else
	{
		// reset animation
		armInst->animFrame = 0;
		
		// no sound here
	}
	
	// 32ms, 30fps
	armObj->timeRolling += 0x20;
	
	armInst->matrix.t[0] += armObj->velX;
	armInst->matrix.t[2] += armObj->velZ;
	
	// if 1.333 seconds passed, (40 frames)
	// could be >= if using accurate ms clock
	if(armObj->timeRolling != 0x500)
	{
		Seal_CheckColl(armInst,t,0x2400);
		return;
	}
	
	// == End of Rolling ===
	
	// reset
	armObj->timeRolling = 0;
	armObj->rotDesired[1] = (armObj->rotCurr[1] + 0x800) & 0xfff;
	
	// rolling animation
	armInst->animFrame = 0;
	armInst->animIndex = 0;
	
	SetThTick_AndExec(t, DECOMP_RB_Armadillo_ThTick_TurnAround);
}

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
			
			DECOMP_RB_Armadillo_ThTick_Rolling,	// behavior
			0,									// debug name
			0									// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	// puts armadillos on separate cycles
	cooldownArray = (short*)sdata->gGT->level1->ptrSpawnType1->pointers[1];
	t->cooldownFrameCount = cooldownArray[inst->name[0xA] - '0'];
	
	// rolling animation
	inst->animFrame = 0;
	inst->animIndex = 1;
	
	armObj = ((struct Armadillo*)t->object);
	armObj->timeRolling = 0;
	armObj->timeAtEdge = 0;
	
	armObj->spawnPosX = inst->matrix.t[0];
	armObj->spawnPosZ = inst->matrix.t[2];
	
	armObj->velX = inst->matrix.m[0][2] >> 7;
	armObj->velZ = inst->matrix.m[2][2] >> 7;
	
	armObj->rotCurr[0] = inst->instDef->rot[0];
	armObj->rotCurr[1] = inst->instDef->rot[1];
	armObj->rotCurr[2] = inst->instDef->rot[2];
}