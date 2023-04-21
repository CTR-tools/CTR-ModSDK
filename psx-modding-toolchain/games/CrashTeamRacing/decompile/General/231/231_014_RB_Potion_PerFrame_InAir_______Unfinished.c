#include <common.h>

void RB_GenericMine_ThTick(struct Thread*);

void DECOMP_RB_Potion_ThTick_InAir(struct Thread* t)
{
	struct GameTracker* gGT;
	struct Instance* inst;
	struct MineWeapon* mw;
	
	short posBottom[3];
	short posTop[3];
	
	#define SPS \
	((struct ScratchpadStruct*)0x1f800108)
	
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

	SPS->Union.Input2.searchFlags = 0x1040;
	SPS->Union.Input2.unk28 = 0;
	SPS->Union.Input2.unk22 = 0x41;

	if (gGT->numPlyrCurrGame < 3) {
		SPS->Union.Input2.unk22 = 0x43;
	}

	DAT_1f800134 = gGT->level1;

	COLL_SearchTree_FindQuadblock_Touching(&posBottom, &posTop, SPS,0);

	RB_MakeInstanceReflective(SPS, inst);

	// 1f800108+1A4
	if ((DAT_1f8002ac & 4) != 0) 
	{
		RB_GenericMine_ThDestroy(t,inst,mw);
	}

	// did not hit VisData hitbox
	if (SPS->boolDidTouchHitbox == 0) 
	{
		if (SPS->boolDidTouchQuadblock != 0) 
		{
			Rot_AxisAngle(&inst->matrix&SPS->unk40[0x30],0);
	
			// if very high above quadblock hitbox, quit
			if (SPS->Union.ThBuckOnCollide.min[1] + 0x30 < inst->matrix.t[1]) 
				return;
	
			// if no cooldown
			if (mw->cooldown == 0)
			{
				// set potion position to quadblock hitbox minY
				inst->matrix.t[1] = SPS->Union.ThBuckOnCollide.min[1];
	
				// reset cooldown (3.84s)
				mw->cooldown = 0xf00;
				
				// reset velocity
				mw->velocity[0] = 0;
				mw->velocity[1] = 0;
				mw->velocity[2] = 0;
	
				mw->maxHeight = inst->matrix.t[1];
	
				// remove "thrown" flag 
				mw->extraFlags &= 0xfffd;
	
				ThTick_SetAndExec(t, RB_GenericMine_ThTick);
	
				return;
			}
			
			// backup posY
			int temp = inst->matrix.t[1];
			
			// === Maybe this isn't Hitbox Min ===
			// === Maybe overwritten as impact position ===
			
			// move potion upward if it drops below quadblock
			if (inst->matrix.t[1] <= SPS->Union.ThBuckOnCollide.min[1]) 
			{
				inst->matrix.t[1] = SPS->Union.ThBuckOnCollide.min[1];
			}
			
			// if distance to move back to quadblock < velocity
			if ((inst->matrix.t[1] - temp) + 0x28 <= mw->velocity[1]) {
				return;
			}
			
			// increase velocity
			mw->velocity[1] = (inst->matrix.t[1] - temp) + 0x28;
			return;
		}

		// if did not touch quadblock in range [-0x40, 0x100],
		// check again with range [-0x900, 0x100]

		// posBottom
		posBottom[2] = inst->matrix.t[0];
		posBottom[1] = inst->matrix.t[1] - 0x900;
		posBottom[0] = inst->matrix.t[2];

		COLL_SearchTree_FindQuadblock_Touching(&posBottom, &posTop, &DAT_1f800108, );

		// quadblock exists far below potion, dont destroy
		if (SPS->boolDidTouchQuadblock != 0) return;
	} 
	
	// hit VisData hitbox
	else 
	{
		
		if (
			(
				(
					// visData->flags hitbox
					((*DAT_1f800150 & 0x80) != 0) && 
					(
						// hitbox contains instDef
						iVar4 = *(int *)(DAT_1f800150 + 0x1c), 
						iVar4 != 0
					)
				) &&
        
				// instDef->modelID == TEETH
				(*(short *)(iVar4 + 0x3c) == 0x70)
			) && 
			
			// instDef->instance exists
			(*(int *)(iVar4 + 0x2c) != 0)
		   ) 
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
	
	// hit TEETH door,
	// or no quadblock exists within 0x900 units of Y axis
	RB_GenericMine_ThDestroy(t, inst, mw);
	
	return;
}	