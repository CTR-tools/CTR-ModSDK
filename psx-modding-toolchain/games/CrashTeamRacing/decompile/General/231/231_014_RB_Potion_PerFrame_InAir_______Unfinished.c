#include <common.h>

void RB_GenericMine_ThTick(struct Thread*);

void DECOMP_RB_Potion_ThTick_InAir(struct Thread* t)
{
	struct GameTracker* gGT;
	struct Instance* inst;
	struct MineWeapon* mw;
	
	short posBottom[3];
	short posTop[3];
	
	gGT = sdata->gGT;
	inst = t->inst;
	mw = t->object;
	
	// adjust position, by velocity
	inst->matrix.t[0] += mw->velocity[0] * (gGT->elapsedTimeMS >> 5);
	inst->matrix.t[1] += mw->velocity[1] * (gGT->elapsedTimeMS >> 5);
	inst->matrix.t[2] += mw->velocity[2] * (gGT->elapsedTimeMS >> 5);
	
	// gravity, decrease velocity over time
	mw->velocity[1] -= ((gGT->elapsedTimeMS << 2) >> 5);
	
	// terminal velocity
	if(mw->velocity[1] < -0x60)
		mw->velocity[1] = -0x60;
	
	mw->cooldown -= gGT->elapsedTimeMS;
	
	if(mw->cooldown < 0)
		mw->cooldown = 0;
	
	posBottom[0] = inst->matrix.t[0];
	posBottom[1] = inst->matrix.t[1] - 0x40;
	posBottom[2] = inst->matrix.t[2];
	
	posTop[0] = inst->matrix.t[0];
	posTop[1] = inst->matrix.t[1] + 0x100;
	posTop[2] = inst->matrix.t[2];

	DAT_1f80012c = 0x1040;
	DAT_1f800130 = 0;
	DAT_1f80012a = 0x41;

	if (gGT->numPlyrCurrGame < 3) {
		DAT_1f80012a = 0x43;
	}

	DAT_1f800134 = gGT->level1;

	COLL_SearchTree_FindQuadblock_Touching(&posBottom, &posTop, &DAT_1f800108,0);

	RB_MakeInstanceReflective(&DAT_1f800108, inst);

	if ((DAT_1f8002ac & 4) != 0) 
	{
		RB_GenericMine_ThDestroy(t,inst,mw);
	}

	if (DAT_1f80014a == 0) 
	{
		if (DAT_1f800146 != 0) 
		{
			Rot_AxisAngle(&inst->matrix&DAT_1f800178,0);
	
				// need to rename to SPS
			if (WSD->min[0] + 0x30 < inst->matrix.t[1]) 
				return;
	
			// if no cooldown
			if (mw->cooldown == 0)
			{
				// need to rename to SPS
				inst->matrix.t[1] = WSD->min[0];
	
				// reset cooldown (3.84s)
				mw->cooldown = 0xf00;
				
				// reset velocity
				mw->velocity[0] = 0;
				mw->velocity[1] = 0;
				mw->velocity[2] = 0;
	
				mw->maxHeight = DAT_1f800124;
	
				// remove "thrown" flag 
				mw->extraFlags &= 0xfffd;
	
				ThTick_SetAndExec(t, RB_GenericMine_ThTick);
	
				return;
			}
			int temp = inst->matrix.t[1];
			
			if (mw->velocity[1] <= DAT_1f800124) {
			inst->matrix.t[1] = DAT_1f800124;
			}
			if ((inst->matrix.t[1] - temp) + 0x28 <= mw->velocity[1]) {
				return;
			}
			mw->velocity[1] = (inst->matrix.t[1] - temp) + 0x28;
			return;
		}

		// posBottom
		posBottom[2] = inst->matrix.t[0];
		posBottom[1] = inst->matrix.t[1] - 0x900;
		posBottom[0] = inst->matrix.t[2];

		COLL_SearchTree_FindQuadblock_Touching(&posBottom, &posTop, &DAT_1f800108, );

		if (DAT_1f800146 != 0) return;
	} 
	
	else 
	{
		
		if (((((*DAT_1f800150 & 0x80) != 0) && (iVar4 = *(int *)(DAT_1f800150 + 0x1c), iVar4 != 0)) &&
        (*(short *)(iVar4 + 0x3c) == 0x70)) && (*(int *)(iVar4 + 0x2c) != 0)) 
		{
			// if door is closed
			if ((sdata->doorAccessFlags & 1) == 0) 
			{
				RB_Teeth_OpenDoor();
			}
			else {
				return;
			}
		}
	}
	RB_GenericMine_ThDestroy(t, inst, mw);
	return;
}	